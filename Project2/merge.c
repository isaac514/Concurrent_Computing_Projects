#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <math.h>
/* ----------------------------------------------------------- */
/* NAME : Isaac Cooper User ID: ijcooper */
/* DUE DATE : 10/08/2024 */
/* PROGRAM ASSIGNMENT #2 */
/* FILE NAME : merge.c (your unix file name) */
/* PROGRAM PURPOSE : merge two sorted arrays */
/* Use shared memory to contruct a sorted array that is the product of two arrays  */
/* ----------------------------------------------------------- */


/* ----------------------------------------------------------- */
/* FUNCTION : modifiedBinarySearchX */
/* the purpose of this function */
/* PARAMETER USAGE : nt arrX[] , int arrY[], int value, int left, int right, int index */
/* ----------------------------------------------------------- */
int modifiedBinarySearchX(int arrX[] , int arrY[], int value, int left, int right, int index)
{
    char searchOutputBuffer[1000];
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        if(value < arrY[mid])
        {
            if(arrY[mid-1]< value && value < arrY[mid])
            {
                sprintf(searchOutputBuffer , "$$$ M-PROC(%d): x[%d] = %d is found between y[%d] = %d and y[%d] = %d\n..........\n",getpid() , index , value ,  mid-1, arrY[mid-1] , mid , arrY[mid]);
                write(1 , searchOutputBuffer , strlen(searchOutputBuffer));
                memset(searchOutputBuffer , 0 , sizeof(searchOutputBuffer));

                return  index + mid;
            }
            if (arrY[mid] < value && value < arrY[mid+1])
            {
                sprintf(searchOutputBuffer , "$$$ M-PROC(%d): x[%d] = %d is found between y[%d] = %d and y[%d] = %d\n..........\n",getpid() , index , value , mid, arrY[mid] , mid+1 , arrY[mid+1] );
                write(1 , searchOutputBuffer , strlen(searchOutputBuffer));
                memset(searchOutputBuffer , 0 , sizeof(searchOutputBuffer));

                return index + mid +1;
            }
            right = mid - 1;
        }
        else
        {
            if(arrY[mid-1] < value && value < arrY[mid])
            {
                sprintf(searchOutputBuffer , "$$$ M-PROC(%d): x[%d] = %d is found between y[%d] = %d and y[%d] = %d\n..........\n",getpid() , index , value ,  mid-1, arrY[mid-1] , mid , arrY[mid]);
                write(1 , searchOutputBuffer , strlen(searchOutputBuffer));
                memset(searchOutputBuffer , 0 , sizeof(searchOutputBuffer));

                return index + mid;
            }
            if (arrY[mid] < value && value < arrY[mid+1])
            {
                sprintf(searchOutputBuffer , "$$$ M-PROC(%d): x[%d] = %d is found between y[%d] = %d and y[%d] = %d\n..........\n",getpid() , index , value , mid, arrY[mid] , mid+1 , arrY[mid+1] );
                write(1 , searchOutputBuffer , strlen(searchOutputBuffer));
                memset(searchOutputBuffer , 0 , sizeof(searchOutputBuffer));
                
                return index + mid +1;
            }
            left = mid+1;
        }
    }
}
/* ----------------------------------------------------------- */
/* FUNCTION : modifiedBinarySearchX */
/* Perform modified binary search as described in the specification */
/* PARAMETER USAGE : nt arrX[] , int arrY[], int value, int left, int right, int index */
/* ----------------------------------------------------------- */
int modifiedBinarySearchY(int arrX[] , int arrY[], int value, int left, int right, int index)
{
    char searchOutputBuffer[1000];
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        if(value < arrX[mid])
        {
            if(arrX[mid-1] < value && value < arrX[mid])
            {
                sprintf(searchOutputBuffer , "$$$ M-PROC(%d): y[%d] = %d is found between x[%d] = %d and x[%d] = %d\n..........\n", getpid() , index , value ,  mid-1, arrX[mid-1] , mid , arrX[mid]);
                write(1 , searchOutputBuffer , strlen(searchOutputBuffer));
                memset(searchOutputBuffer , 0 , sizeof(searchOutputBuffer));
                
                return index + mid;
            }
            if (arrX[mid] < value && value < arrX[mid+1])
            {
                sprintf(searchOutputBuffer , "$$$ M-PROC(%d): y[%d] = %d is found between x[%d] = %d and x[%d] = %d\n..........\n", getpid() , index , value ,  mid , arrX[mid] , mid+1 , arrX[mid+1]);
                write(1 , searchOutputBuffer , strlen(searchOutputBuffer));
                memset(searchOutputBuffer , 0 , sizeof(searchOutputBuffer)); 
                
                return index + mid +1;
            }
            right = mid - 1;
        }
        else
        {
            if(arrX[mid-1]< value && value < arrX[mid])
            {
                sprintf(searchOutputBuffer , "$$$ M-PROC(%d): y[%d] = %d is found between x[%d] = %d and x[%d] = %d\n..........\n", getpid() , index , value ,  mid-1, arrX[mid-1] , mid , arrX[mid]);
                write(1 , searchOutputBuffer , strlen(searchOutputBuffer));
                memset(searchOutputBuffer , 0 , sizeof(searchOutputBuffer));

                return index + mid;
            }
            if (arrX[mid] < value && value < arrX[mid+1])
            {
                sprintf(searchOutputBuffer , "$$$ M-PROC(%d): y[%d] = %d is found between x[%d] = %d and x[%d] = %d\n..........\n", getpid() , index , value ,  mid , arrX[mid] , mid+1 , arrX[mid+1]);
                write(1 , searchOutputBuffer , strlen(searchOutputBuffer));
                memset(searchOutputBuffer , 0 , sizeof(searchOutputBuffer)); 

                return index + mid + 1;
            }
            left = mid+1;
        }
    }
}

int main(int argc , char** argv)
{
   struct Data2
        {
            int m;
            int arrX[]
        }; struct Data2 *structPtr2;

    struct Data3
            {
                int n;
                int arrY[];
            }; struct Data3 *structPtr3;

    struct Data4
            {
                int v;
                int arrV[];
            }; struct Data4 *structPtr4; 

    //Attach all shared memory segments
    int shmID2;
    int shmID3;
    int shmID4;
    char outputBuffer[1000];

    pid_t c1pid;
    pid_t c2pid;
    key_t key2;
    key_t key3;
    key_t key4;

    //Array X
    key2 = ftok("./", 'x');

    shmID2 = shmget(key2, sizeof(struct Data2), 0666 );

    //Attach shared memory segment to parent process
    structPtr2 = (struct Data2 *) shmat(shmID2 , NULL , 0);
    
    if(structPtr2 < 0)
    {
        write(1 , "shmat() failed\n" , 16);
        exit(1);
    }

    //Array Y
    key3 = ftok("./", 'y');

    shmID3 = shmget(key3, sizeof(struct Data3), 0666 );

    //Attach shared memory segment to parent process
    structPtr3 = (struct Data3 *) shmat(shmID3 , NULL , 0);
    
    if(structPtr3 < 0)
    {
        write(1 , "shmat() failed\n" , 16);
        exit(1);
    }

    //Output Array
    key4 = ftok("./", 'z');

    shmID4 = shmget(key4, sizeof(struct Data4),  0666 );

    //Attach shared memory segment to parent process
    structPtr4 = (struct Data4 *) shmat(shmID4 , NULL , 0);
    
    if(structPtr4 < 0)
    {
        write(1 , "shmat() failed\n" , 16);
        exit(1);
    }


    //Get array sizes
    int m = structPtr2->m;
    int n = structPtr3->n;

    for(int i = 0 ; i < m ; i++)
    {
        c1pid = fork();

        //Child process does one array comparsion
        if (c1pid == 0)
        {
            sprintf(outputBuffer , "$$$  M-PROC (%d): handling x[%d] = %d \n ..........\n" , getpid() , i , structPtr2->arrX[i]);
            write(1,outputBuffer, strlen(outputBuffer));
            memset(outputBuffer , 0 , sizeof(outputBuffer));
            
            if (structPtr2->arrX[i] < structPtr3->arrY[0])
            {
                //Insert at position i
                structPtr4->arrV[i] = structPtr2->arrX[i];

                sprintf(outputBuffer, "$$$  M-PROC (%d): about to write x[%d] = %d into position %d of the output array\n..........\n",getpid() , i, structPtr2->arrX[i], i);
                write(1 , outputBuffer , strlen(outputBuffer));
                memset(outputBuffer , 0 , sizeof(outputBuffer));

                //Exit and detach
                exit(0);
                shmdt(structPtr2);
                shmdt(structPtr3);
            }
            else if (structPtr2->arrX[i] > structPtr3->arrY[n-1])
            {
                //Insert at postion i+n
                structPtr4->arrV[i+n] = structPtr2->arrX[i];

                sprintf(outputBuffer, "$$$  M-PROC (%d): about to write x[%d] = %d into position %d of the output array\n..........\n",getpid() , i, structPtr2->arrX[i], i+n);
                write(1 , outputBuffer , strlen(outputBuffer));
                memset(outputBuffer , 0 , sizeof(outputBuffer)); 

                //Exit and detach
                exit(0);
                shmdt(structPtr2);
                shmdt(structPtr3);
            }
            else
            {
                int left = 0;
                int right = n-1;
                int index = modifiedBinarySearchX(structPtr2->arrX , structPtr3->arrY , structPtr2->arrX[i], left , right,i);
                structPtr4->arrV[index] = structPtr2->arrX[i];

                sprintf(outputBuffer, "$$$  M-PROC (%d): about to write x[%d] = %d into position %d of the output array\n..........\n",getpid() , i, structPtr2->arrX[i], index);
                write(1 , outputBuffer , strlen(outputBuffer));
                memset(outputBuffer , 0 , sizeof(outputBuffer)); 

                //Exit and detach
                exit(0);
                shmdt(structPtr2);
                shmdt(structPtr3); 
            }
        }
    }

    for(int j = 0 ; j < n ; j++)
    {
        c2pid = fork();

        if(c2pid == 0)
        {
            if(structPtr3->arrY[j] < structPtr2->arrX[0])
            {
                //Insert at position i
                structPtr4->arrV[j] = structPtr3->arrY[j];

                sprintf(outputBuffer, "$$$  M-PROC (%d): about to write y[%d] = %d into position %d of the output array\n..........\n",getpid() , j, structPtr3->arrY[j], j);
                write(1 , outputBuffer , strlen(outputBuffer));
                memset(outputBuffer , 0 , sizeof(outputBuffer)); 

                //Exit and detach
                exit(0);
                shmdt(structPtr2);
                shmdt(structPtr3);  
            }
            else if(structPtr3->arrY[j] > structPtr2->arrX[m-1])
            {
                //Insert at postion i+m 
                structPtr4->arrV[j+m] = structPtr3->arrY[j];

                sprintf(outputBuffer, "$$$  M-PROC (%d): about to write y[%d] = %d into position %d of the output array\n..........\n",getpid() , j, structPtr3->arrY[j], j+m);
                write(1 , outputBuffer , strlen(outputBuffer));
                memset(outputBuffer , 0 , sizeof(outputBuffer));  

                //Exit and detach
                exit(0);
                shmdt(structPtr2);
                shmdt(structPtr3); 
            }
            else
            {
                int left = 0;
                int right = m-1;
                int index = modifiedBinarySearchY(structPtr2->arrX , structPtr3->arrY , structPtr3->arrY[j], left , right,j);
                structPtr4->arrV[index] = structPtr3->arrY[j];

                sprintf(outputBuffer, "$$$  M-PROC (%d): about to write y[%d] = %d into position %d of the output array\n..........\n",getpid() , j, structPtr3->arrY[j], index);
                write(1 , outputBuffer , strlen(outputBuffer));
                memset(outputBuffer , 0 , sizeof(outputBuffer)); 


                //Exit and detach
                exit(0);
                shmdt(structPtr2);
                shmdt(structPtr3); 
            }
        }

    }
    
    //gcc -Wall -pedantic -g -o merge merge.c 

    }


