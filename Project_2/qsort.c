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
/* FILE NAME : qsort.c (your unix file name) */
/* PROGRAM PURPOSE :sort an array using quicksort and execvp */
/* A couple of lines describing your program briefly */
/* When tested recent, fails on second call execution of execvp, memory not being properly attached */
/* I am not sure why this is happen because when I first tested it, it worked fine  */
/* ----------------------------------------------------------- */



/* ----------------------------------------------------------- */
/* FUNCTION : getIndex */
/* the purpose of this function */
/* PARAMETER USAGE : int* arr , int left, int right */
/* a list of all parameters and their meaning */
/* ----------------------------------------------------------- */
int getIndex(int *arr , int left , int right)
{
    char outputBuffer[1000];

    int pivot = arr[right];

    sprintf(outputBuffer ,"### Q-PROC(%d): pivot element is a[%d] = %d\n..........\n" , getpid() , right , pivot);
    write(1 , outputBuffer ,strlen(outputBuffer));
    memset(outputBuffer , 0 , sizeof(outputBuffer));

    int a = left - 1;

    for(int b = left; b <= right - 1 ; b++ )
    {
        if(arr[b] < pivot)
        {
            a++;
            int temp1 = arr[a];
            arr[a] = arr[b];
            arr[b] = temp1;
        }
    }
    int temp2 = arr[a+1];
    arr[a+1] = arr[right];
    arr[right] = temp2 ;
    return a+1;
}


int main(int argc , char** argv)
{
    struct Data1 
        {
            int k;
            int arrA[];
        }; struct Data1 *structPtr1;
    
    int shmID1;
    key_t  key1;

    char outputBuffer[1000];


    //Create shared memory segment
    key1 = ftok("./", 'h');

    shmID1 = shmget(key1, sizeof(struct Data1), 0666 );

    //Attach shared memory segment at beginning of proccess
    structPtr1 = (struct Data1 *) shmat(shmID1 , NULL , 0);
    
    int left =atoi(argv[1]);
    int right = atoi(argv[2]);

    //while left is not equal to right perform quicksort on the 
    //subsections of the array 

    if(left < right)
    {
    char* leftstring = argv[1];
    char* rightstring = argv[2];
    char ind1[10];
    char ind2[10];

    int M = getIndex(structPtr1->arrA, left , right);

    sprintf(ind1, "%d", M-1);
    sprintf(ind2, "%d", M+1);

    //Print array subsection


    //Once all subsections of the array are sorted detached the shared memory segment 
    //shmdt(structPtr1);

    char *argv1[] = {"qsort", leftstring , ind1, NULL};
    char *argv2[] = {"qsort",ind2, rightstring, NULL};

    //Run quicksort on array subsections
    int c1pid = fork();
        if(c1pid == 0)
        {
            //Print process information
            sprintf(outputBuffer , "### Q-PROC(%d): entering with a[%d..%d]\n..........\n",getpid() , atoi(argv[1]) , M-1);
            for(int a = atoi(argv[1]) ; a <= M-1 ; a++)
            {
                char tempBuffer[20];

                sprintf(tempBuffer , "%d  ", structPtr1->arrA[a]);
                strcat(outputBuffer, tempBuffer);
            }
            write(1 , outputBuffer , strlen(outputBuffer));
            memset(outputBuffer , 0 ,sizeof(outputBuffer));
            execvp("./qsort" , argv1);


            //Subsection sorted
            sprintf(outputBuffer , "### Q-PROC(%d): section a[%d..%d] sorted\n" , getpid() , atoi(argv[1]) , M-1);
            for(int i = atoi(argv[1]) ; i <= M-1 ; i++)
            {
                char tempBuffer[20];

                sprintf(tempBuffer , "%d  ", structPtr1->arrA[i]);
                strcat(outputBuffer, tempBuffer);
            } 
            write(1 , outputBuffer , strlen(outputBuffer));
            memset(outputBuffer , 0 , sizeof(outputBuffer));

            sprintf(outputBuffer , "### Q-PROC(%d): exits\n" , getpid());
            write(1, outputBuffer , strlen(outputBuffer));
            memset(outputBuffer , 0 , sizeof(outputBuffer));
            
        }
        else
        {
            int c2pid = fork();
            if(c2pid == 0)
            {
                //Print proccess information
                sprintf(outputBuffer , "### Q-PROC(%d): entering with a[%d..%d]\n..........\n",getpid() , M+1 , atoi(argv[2]));
                for(int a = atoi(argv[2]) ; a <= M-1 ; a++)
                {
                    char tempBuffer[20];

                    sprintf(tempBuffer , "%d  ", structPtr1->arrA[a]);
                    strcat(outputBuffer, tempBuffer);
                }
                write(1 , outputBuffer ,strlen(outputBuffer));
                memset(outputBuffer , 0 ,sizeof(outputBuffer)); 
                execvp("./qsort" , argv2);

                //Subsection sorted
                sprintf(outputBuffer , "### Q-PROC(%d): section a[%d..%d] sorted\n" , getpid() , M+1 , atoi(argv[2]));
                for(int j = M+1 ; j <= atoi(argv[2]) ; j++)
                {
                    char tempBuffer[20];

                    sprintf(tempBuffer , "%d  ", structPtr1->arrA[j]);
                    strcat(outputBuffer, tempBuffer);
                } 
                write(1 , outputBuffer , strlen(outputBuffer));
                memset(outputBuffer , 0 , sizeof(outputBuffer));

                sprintf(outputBuffer , "### Q-PROC(%d): exits\n" , getpid());
                write(1, outputBuffer , strlen(outputBuffer));
                memset(outputBuffer , 0 , sizeof(outputBuffer));
            }
        } 
    }
    else
    {
        exit(0);
    }
    
}