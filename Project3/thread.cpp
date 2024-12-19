// -------------------------------------------------------
// NAME : Isaac Cooper User ID: ijcooper
// DUE DATE : 10/14/2024
// PROGRAM ASSIGNMENT #3
// FILE NAME : thread.cpp 
// PROGRAM PURPOSE :
// Provides the definiton of the threads to compute the prefix sum. 
// Updates the output array appropriately as thread either copy information or 
// add two elements together
// ----------------------------------------------------
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>
#include "ThreadClass.h"
#include "thread.h"

// -------------------------------------------------------
// FUNCTION PrefixSumThread : 
// Defines the constuctor and internal variables for threads
// PARAMETER USAGE :
// int ** arrayB (the output array to be continuosly updated)
// int i (outer index for each run)
// int j (inner index for each thread)
// --------------------------------------------------------
PrefixSumThread::PrefixSumThread(int ** ArrayB, int i , int j)
                :B(ArrayB) , i(i) , j(j)  
{

}

// -------------------------------------------------------
// FUNCTION PrefixSumThread : 
// Implementation of the partial work done by each thread
// making up the algoritm to compute the prefix sum for a given input array
// 
// --------------------------------------------------------
void PrefixSumThread::ThreadFunc()
{
    char outputBuffer[1000];

    Thread::ThreadFunc();

    sprintf(outputBuffer , "..........\n    Thread %d Created\n" , j);
    write(1 , outputBuffer ,strlen(outputBuffer));
    memset(outputBuffer , 0 ,sizeof(outputBuffer));

    //Computations for each Thread
    int temp = pow(2 , i - 1);
    index = j - temp;

    if(index < 0)
    {
        sprintf(outputBuffer , "..........\n    Thread %d copies x[%d]\n" , j , j);
        write(1 , outputBuffer , strlen(outputBuffer));
        memset(outputBuffer , 0 ,sizeof(outputBuffer));

        //Copy value
        B[i][j] = B[i-1][j];
    }
    else
    {
        sprintf(outputBuffer , "..........\n    Thread %d computes x[%d] + x[%d]\n", j , j , index);
        write(1 , outputBuffer , strlen(outputBuffer));
        memset(outputBuffer , 0 ,sizeof(outputBuffer));

        //Compute new value
        B[i][j] = B[i-1][j] + B[i-1][index];
    }
    //Thread exits
    sprintf(outputBuffer , "..........\n    Thread %d exits\n" , j);
    write(1 , outputBuffer , strlen(outputBuffer));
    memset(outputBuffer , 0 , sizeof(outputBuffer));
    sleep(2);

    //Exit
    Exit();

    //Project compiled with make noVisual -f Makefile 
}