// -------------------------------------------------------
// NAME : Isaac Cooper User ID: ijcooper
// DUE DATE : 10/13/024
// PROGRAM ASSIGNMENT #3
// FILE NAME : thread-main.cpp
// PROGRAM PURPOSE :
// Parsing the input file and runs threads defined by thread.cpp and thread.h
// to compute the prefix sum of a given array
// ----------------------------------------------------
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>
#include "thread.h"


#define MAX_STRING_LENGTH 256
int  ** arrB;

int main(int argc, char * argv[])
{
    int exitCounter = 0;
    int largeIndex = 0;
    int arrXIndex = 0;
    int BufferIndex = 0;
    char inputBuffer[1000];
    char outputBuffer[1000];
    char * inputptrArr[2];
    PrefixSumThread *prefixSumThread;

    //Read file into buffer
    read(0 , inputBuffer , sizeof(inputBuffer));

    while(1)
    {
        int smallIndex = 0;

        if(exitCounter == 2)
        {
            //Have read all contents
            break;
        }
        if(inputBuffer[BufferIndex] != '\n')
        {
            inputptrArr[largeIndex] = (char *)malloc(MAX_STRING_LENGTH *sizeof(char));
            while(inputBuffer[BufferIndex] != '\n')
            {
                inputptrArr[largeIndex][smallIndex] = inputBuffer[BufferIndex];
                BufferIndex++;
                smallIndex++;
            } 
        }
        if(inputBuffer[BufferIndex] == '\n')
        {
            smallIndex = 0;
            largeIndex++;
            BufferIndex++;
            exitCounter++;
        }
    }

    //Initialize n, k, and arrX[]
    int n = atoi(inputptrArr[0]);
    int arrX[n];
    int k = log2(n);
    BufferIndex = 0;

    memset(arrX , 0 ,sizeof(arrX));


    //Populate arrX
    while(1)
    {
        int smallIndex = 0;
        char * numberptr = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));

        if(inputptrArr[1][BufferIndex] != ' ')
        {
            while((inputptrArr[1][BufferIndex] != ' ')  && (inputptrArr[1][BufferIndex] != 0))
            {
                numberptr[smallIndex] = inputptrArr[1][BufferIndex];
                BufferIndex++;
                smallIndex++;
            }  
        }
        if((inputptrArr[1][BufferIndex] == ' ') || (inputptrArr[1][BufferIndex] == 0)) 
        {
            arrX[arrXIndex] = atoi(numberptr);
            free(numberptr);
            arrXIndex++;  
            BufferIndex++;
        }
        if(arrXIndex == n)
        {
            break;
        } 
    }

    //Free inputBuffer[0] and [1] after contents are read into arrays
    free(inputptrArr[0]);
    free(inputptrArr[1]);

    //Initialize arrB[][] 
    arrB = new int*[k+1];

    for (int i = 0 ; i < (k+1) ; i++)
    {
        arrB[i] = new int[n];
    }

    //Populate the first row of arrB
    for(int c = 0 ; c < n ; c++)
    {
        arrB[0][c] = arrX[c];
    }

    //Print input information
    write(1 , "Concurrent Prefix Sum Computation\n" , 35);

    sprintf(outputBuffer , "Number of input data = %d\n",n);
    write(1 , outputBuffer ,strlen(outputBuffer));
    memset(outputBuffer , 0 ,sizeof(outputBuffer));

    write(1 , "Input array: \n", 15);

   for(int a = 0 ; a < n ; a++)
   {
        char tempBuffer[20];
        sprintf(tempBuffer , "%d  ",arrX[a]);
        strcat(outputBuffer , tempBuffer);
   } 
   strcat(outputBuffer , "\n");
    write(1 , outputBuffer , strlen(outputBuffer));
    memset(outputBuffer , 0 ,sizeof(outputBuffer));

    //PrePrefix Sum algorthim
    for(int i = 1 ; i <= k ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            //Start the prefixSum Thread
            prefixSumThread = new PrefixSumThread(arrB,i,j);
            prefixSumThread->Begin();
        }
        for(int k = 0 ; k < n ; k++ )
        {
            prefixSumThread->Join();
        }
        
        //Report results after run i
        sprintf(outputBuffer , "Result after run %d\n" , i);
        write(1 , outputBuffer ,strlen(outputBuffer));
        memset(outputBuffer , 0 ,sizeof(outputBuffer));
        for(int a = 0 ; a < n ; a++)
        {
            char tempBuffer[20];
            sprintf(tempBuffer , "%d  ",arrB[i][a]);
            strcat(outputBuffer , tempBuffer);
        }
        strcat(outputBuffer , "\n");
        write(1 , outputBuffer , strlen(outputBuffer));
        memset(outputBuffer , 0 ,sizeof(outputBuffer));

    }
    //Print final result after run k
    sprintf(outputBuffer , "\n\n Final Result after run %d\n" , k);
    write(1 , outputBuffer , strlen(outputBuffer));
    memset(outputBuffer , 0 ,sizeof(outputBuffer));

    for( int b = 0 ; b < n ; b++)
    {
        char tempBuffer[20];
        sprintf(tempBuffer ,"  %d", arrB[k][b]);
        strcat(outputBuffer , tempBuffer);
    }

    write(1 , outputBuffer , sizeof(outputBuffer));
    memset(outputBuffer , 0, sizeof(outputBuffer));

    //Clean up 
    //free arrB
    for(int i = 0 ; i < (k+1) ; i++)
    {
        delete[] arrB[i];
    }
    delete[] arrB;
    arrB = NULL;

    Exit();
    return 0;
    
    //Project compiled with make noVisual -f Makefile  
}
