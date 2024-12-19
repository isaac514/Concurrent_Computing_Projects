
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

#define MAX_STRING_LENGTH 256

/* ----------------------------------------------------------- */
/* NAME : Isaac Cooper ijcooper: xxxxxxxx */
/* DUE DATE : 10/08/2024 */
/* PROGRAM ASSIGNMENT # 2*/
/* FILE NAME : main.c (your unix file name) */
/* PROGRAM PURPOSE : */
/* Parse input file and run qsort and merge*/
/* ----------------------------------------------------------- */

int main(int argc , char** argv)
{
   if(argc < 0 )
   {
        write(1 ,"Invalid number of program arguments" , 36 );
        return -1;
   }
    
    
    int shmID1;
    int shmID2;
    int shmID3;
    int shmID4;
    key_t key1;
    key_t key2;
    key_t key3;
    key_t key4;
    int k , m , n;
    char buf2[1000];
    char* sizeptrArr[6];
    char outputBuffer[1000];
    pid_t pidq;
    pid_t pidm;
    int bufferIndex=0;
    int arrptr = 0;
    int exitcounter2 = 0;
   

        //Parse the the input file
        memset(buf2 , 0 , sizeof(buf2));

        //Read size amount of bytes into buf2 
        read(0 , buf2 , sizeof(buf2) );


        //Read Each individual line into array of character pointers 
        while(1)
        {
            int smallInd = 0;
        
            if(exitcounter2 == 6)
            {
                break;
            }
            if(buf2[bufferIndex] != '\n')
            {
                sizeptrArr[arrptr] = malloc(MAX_STRING_LENGTH * sizeof(char));
                while(buf2[bufferIndex] != '\n')
                {
                    sizeptrArr[arrptr][smallInd] = buf2[bufferIndex];
                    bufferIndex++;
                     smallInd++;
                }
            }
            if(buf2[bufferIndex] == '\n')
            {
                smallInd = 0;
                arrptr++;
                bufferIndex++;
                exitcounter2++;
            }
        }

        //Indexes 0, 2, 4 have the values need to determine array sizes
        k = atoi(sizeptrArr[0]);
        m = atoi(sizeptrArr[2]);
        n = atoi(sizeptrArr[4]);

        //Intialize the arrays arrA[], arrX[], arrY[]
        int arrA[k];
        int arrX[m];
        int arrY[n];

        //Intitalize the pointer arrays to hold string pointers to be converted to ints
        char* ptr1Arr[k];
        char* ptr2Arr[m]; 
        char* ptr3Arr[n]; 

        //Indexes 1, 3, 5 have the strings containing the array values to be parsed
        //Separately parse these strings to construct input arrays

        //Parse array A
        bufferIndex = 0;
        arrptr = 0;

        //Get correct exit condition based on whether size is even or odd
        while(1)
        {
            int smallInd = 0;

            if(sizeptrArr[1][bufferIndex] != ' ')
            {
                ptr1Arr[arrptr] = malloc(MAX_STRING_LENGTH * sizeof(char));
                while((sizeptrArr[1][bufferIndex] != ' ') && (sizeptrArr[1][bufferIndex] != 0) )
                {
                    ptr1Arr[arrptr][smallInd] = sizeptrArr[1][bufferIndex];
                    bufferIndex++;
                    smallInd++;
                }
                arrptr++;
            }
            //Move over spaces
            else
            {
                bufferIndex++;
            }
            //We have inserted at the last index and need to exit
            if(arrptr == k)
            {
                break;
            }
        }

        //Parse array X
        bufferIndex = 0;
        arrptr = 0;

        while(1)
        {
            int smallInd = 0;

            if(sizeptrArr[3][bufferIndex] != ' ')
            {
                ptr2Arr[arrptr] = malloc(MAX_STRING_LENGTH * sizeof(char));
                while((sizeptrArr[3][bufferIndex] != ' ') && (sizeptrArr[3][bufferIndex] != 0))
                {
                    ptr2Arr[arrptr][smallInd] = sizeptrArr[3][bufferIndex];
                    bufferIndex++;
                    smallInd++;
                }
                arrptr++;
            }
            else
            {
                bufferIndex++;
            }
            //We have inserted at the the index and need to exit
            if(arrptr == m)
            {
                break;
            }
        }

        //Parse array Z
        bufferIndex = 0;
        arrptr = 0;
        while(1)
        {
            int smallInd = 0;

            if(arrptr >= n)
            {
                break;
            }

            if(sizeptrArr[5][bufferIndex] != ' ')
            {
                ptr3Arr[arrptr] = malloc(MAX_STRING_LENGTH * sizeof(char));
                while((sizeptrArr[5][bufferIndex] != ' ') && (sizeptrArr[5][bufferIndex] != 0))
                {
                    ptr3Arr[arrptr][smallInd] = sizeptrArr[5][bufferIndex];
                    bufferIndex++;
                    smallInd++;
                }
                arrptr++;
            }
            else
            {
                bufferIndex++;
            }
            //We have inserted at the the index and need to exit
            if(arrptr == n)
            {
                break;
            }
        }

        //Set default value for arrays
        memset(arrA , 0 , sizeof(arrA));
        memset(arrX , 0 , sizeof(arrX));
        memset(arrY , 0 , sizeof(arrY));

        memset(outputBuffer, 0 , sizeof(outputBuffer));

        
        //Print main process information 
        //Convert contents of pointer arrays into integers

        write(1 , "Quicksort and Binary Merge with multiple processes:\n" ,53); 

        //Array A
        sprintf(outputBuffer , "Input array for qsort has %d elements: \n" , k);
        write(1 , outputBuffer , strlen(outputBuffer));
        memset(outputBuffer , 0 , sizeof(outputBuffer));
        for(int a = 0 ; a < k ; a++)
        {
            arrA[a] = atoi(ptr1Arr[a]);
            char tempBuffer[20];

            sprintf(tempBuffer , "%d  ", arrA[a]);
            strcat(outputBuffer, tempBuffer);
        }
        write(1 , outputBuffer , strlen(outputBuffer)); 

        //Array X
        sprintf(outputBuffer , "\nInput array x[] for merge has %d elements:\n" , m);
        write(1 , outputBuffer , strlen(outputBuffer));
        memset(outputBuffer , 0 , sizeof(outputBuffer));
        for(int b = 0 ; b < m ; b++)
        { 
           arrX[b] = atoi(ptr2Arr[b]);
           char tempBuffer[20];
           sprintf(tempBuffer , "%d  ", arrX[b]); 
           strcat(outputBuffer, tempBuffer);
        }
        write(1 , outputBuffer , strlen(outputBuffer));

        //Array Y
        sprintf(outputBuffer , "\nInput array y[] for merge has %d elements:\n" , n);
        write(1 , outputBuffer , strlen(outputBuffer)); 
        memset(outputBuffer , 0 , sizeof(outputBuffer));
        for(int c = 0 ; c < n ; c++)
        {
            arrY[c] = atoi(ptr3Arr[c]);
            char tempBuffer[20];
            sprintf(tempBuffer , "%d  ", arrY[c]); 
            strcat(outputBuffer , tempBuffer);
        }
        write(1 , outputBuffer , strlen(outputBuffer));

//Intialize size for arrays with the shared memory segment
struct Data1 
        {
            int k;
            int arrA[];
        }; struct Data1 *structPtr1;

struct Data2
        {
            int m;
            int arrX[];
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

    //Create shared memory segment for qsort
    key1 = ftok("./", 'h');

    shmID1 = shmget(key1, sizeof(struct Data1), IPC_CREAT | 0666 );

    //Attach shared memory segment to parent process
    structPtr1 = (struct Data1 *) shmat(shmID1 , NULL , 0);
    
    if(structPtr1 < 0)
    {
        write(1 , "shmat() failed\n" , 16);
        exit(1);
    }

    //Create shared memory segments for merge (inputs arrays) (output array)

    //Array X
    key2 = ftok("./", 'x');

    shmID2 = shmget(key2, sizeof(struct Data2), IPC_CREAT | 0666 );

    //Attach shared memory segment to parent process
    structPtr2 = (struct Data2 *) shmat(shmID2 , NULL , 0);
    
    if(structPtr2 < 0)
    {
        write(1 , "shmat() failed\n" , 16);
        exit(1);
    }

    //Array Y
    key3 = ftok("./", 'y');

    shmID3 = shmget(key3, sizeof(struct Data3), IPC_CREAT | 0666 );

    //Attach shared memory segment to parent process
    structPtr3 = (struct Data3 *) shmat(shmID3 , NULL , 0);
    
    if(structPtr3 < 0)
    {
        write(1 , "shmat() failed\n" , 16);
        exit(1);
    }

    //Output Array
    key4 = ftok("./", 'z');

    shmID4 = shmget(key4, sizeof(struct Data4), IPC_CREAT | 0666 );

    //Attach shared memory segment to parent process
    structPtr4 = (struct Data4 *) shmat(shmID4 , NULL , 0);
    
    if(structPtr4 < 0)
    {
        write(1 , "shmat() failed\n" , 16);
        exit(1);
    }

    //Set array sizes
    structPtr1->arrA[k];
    structPtr2->arrX[m];
    structPtr3->arrY[n];
    structPtr4->arrV[m+n];

    structPtr1-> k = k;
    structPtr2-> m = m;
    structPtr3-> n = n;
    structPtr4-> v = m+n;

    //Print shared memory information
    memset(outputBuffer , 0 , sizeof(outputBuffer));

    sprintf(outputBuffer , "\n*** MAIN: qsort shared memory key = %d\n" , key1);
    write(1 , outputBuffer , strlen(outputBuffer));
    write(1 , "*** MAIN: qsort shared memory created\n",39);
    write(1 , "*** MAIN: qsort shared memory attached and is ready to use\n" , 60);

    memset(outputBuffer , 0 , sizeof(outputBuffer)); 

    sprintf(outputBuffer , "*** MAIN: merge shared memory key for array X = %d\n" , key2);
    write(1 , outputBuffer , strlen(outputBuffer));
    write(1 , "*** MAIN: merge shared memory created\n",39);
    write(1 , "*** MAIN: merge shared memory attached and is ready to use\n", 60);

    memset(outputBuffer , 0 , sizeof(outputBuffer)); 

    sprintf(outputBuffer , "*** MAIN: merge shared memory key for array Y = %d\n" , key3);
    write(1 , outputBuffer , strlen(outputBuffer));
    write(1 , "*** MAIN: merge shared memory created\n",39);
    write(1 , "*** MAIN: merge shared memory attached and is ready to use\n", 60);

    memset(outputBuffer , 0 , sizeof(outputBuffer)); 

    sprintf(outputBuffer , "*** MAIN: merge shared memory key for output array = %d\n" , key4);
    write(1 , outputBuffer , strlen(outputBuffer));
    write(1 , "*** MAIN: merge shared memory created\n",39);
    write(1 , "*** MAIN: merge shared memory attached and is ready to use\n", 60);

    memset(outputBuffer , 0 , sizeof(outputBuffer));


    //Array A
    for(int i = 0 ; i < k ; i++)
    {
        structPtr1->arrA[i]=arrA[i];
    }

    //Array X
    for(int i = 0 ; i < m ; i++)
    {
        structPtr2->arrX[i]=arrX[i];
    }

    //Array Y
    for(int i = 0 ; i < n ; i++)
    {
        structPtr3->arrY[i]=arrY[i];
    }

    

    //Set up intital argument arrays for execvp
    char arg3[10];
    sprintf(arg3 ,"%d" , k-1);
    char *argv1[] = {"qsort", "0" , arg3, NULL };
    char *argv2[] = {"merge", NULL};    
    

    //Create child processes and attach shared memory segments to them
    pidq = fork();

    //Parent process will create another child process for 
    if(pidq > 0)
    {
        write(1 , "*** MAIN about to spawn the process for merge\n",47);
        pidm = fork();
        if(pidm == 0)
        {
            //Run merge on the arrX and arrY
            execvp("merge",argv2);
        }
    }
    else
    {
        write(1 , "*** MAIN about to spawn the process for qsort\n" ,46 );

        //qsort starting information
        sprintf(outputBuffer , "### Q-PROC(%d): entering with a[%d..%d]\n" ,getpid(), 0 , k-1);
        write(1 , outputBuffer ,strlen(outputBuffer));
        memset(outputBuffer , 0 , sizeof(outputBuffer));

        //Run qsort
        execvp("qsort",argv1); 
    }
        
    

    //Wait for both child processes to terminate
    wait(NULL);
    wait(NULL);

    sprintf(outputBuffer ,"*** MAIN: sorted array by qsort:\n ");

    for(int a = 0 ; a < k ; a++)
        {
            char tempBuffer[20];

            sprintf(tempBuffer , "%d  ", structPtr1->arrA[a]);
            strcat(outputBuffer, tempBuffer);
        }
    write(1 , outputBuffer ,strlen(outputBuffer));
    memset(outputBuffer , 0 , sizeof(outputBuffer));

    sprintf(outputBuffer , "*** MAIN: merged array:\n");

    for(int b = 0 ; b < m+n ; b++)
    {
        char tempBuffer[20];

        sprintf(tempBuffer , "%d  ", structPtr4->arrV[b]);
        strcat(outputBuffer , tempBuffer);
    }
    write(1 , outputBuffer , strlen(outputBuffer));
    memset(outputBuffer , 0 , sizeof(outputBuffer));

    //Clean up
    //Detach shared memory segments
    shmdt(structPtr1);
    shmdt(structPtr2);
    shmdt(structPtr3);
    shmdt(structPtr4);
    write(1 , "*** MAIN: shared memory successfully detached\n",47);

    //Remove shared memory segment
    shmctl(shmID1 , IPC_RMID , NULL);
    shmctl(shmID2 , IPC_RMID , NULL);
    shmctl(shmID3 , IPC_RMID , NULL);
    shmctl(shmID4 , IPC_RMID , NULL);
    write(1 , "*** MAIN: shared memory successfully removed\n",46);

    return 1;
    }

    

    //gcc -Wall -pedantic -g -o main main.c 
