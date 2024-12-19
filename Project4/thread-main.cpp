// -------------------------------------------------------
// NAME : Isaac Cooper User ID: ijcooper
// DUE DATE : 11/6/024
// PROGRAM ASSIGNMENT #4
// FILE NAME : thread-main.cpp
// PROGRAM PURPOSE :
// Handle input arguments and run threads
// ----------------------------------------------------
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>
#include <time.h>
#include "thread.h"

int m; //Number of feeding pots
int n; //Number of baby eagles
int t; //Number of feedings
int * potsVector; // value of 0 means empty value of 1 means full
MotherEagleThread *motherEagleThread;
BabyEagleThread *babyEagleThread;
int main(int argc, char * argv[])
{
    //Input arguments
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    t = atoi(argv[3]);

    potsVector = new int[m];
    

    //Initialize pots vector
    for(int i = 0 ; i < m ; i++)
    {
        potsVector[i] = 0;
    }

    char outputBuffer[1000];
     sprintf(outputBuffer , "MAIN: There are %d baby eagles, %d feading pots, and %d feedings.\nMAIN: Game starts!!!!!\n......\n" , n , m, t);
     write(1 , outputBuffer ,strlen(outputBuffer));
     memset(outputBuffer , 0 , sizeof(outputBuffer));

    //Start the threads
    //Start Mother eagle thread
    motherEagleThread = new MotherEagleThread(t,potsVector,m,n);
    sprintf(outputBuffer , "Mother Eagle Started\n");
     write(1 , outputBuffer ,strlen(outputBuffer));
     memset(outputBuffer , 0 , sizeof(outputBuffer));
     
    motherEagleThread->Begin();

    //Start the baby eagle threads
    for (int k = 1 ; k <= n ; k++)
    {
        babyEagleThread = new BabyEagleThread(k,potsVector,m,t);

        sprintf(outputBuffer , "\tBaby Eagle %d started\n\n" , k);
        write(1 , outputBuffer ,strlen(outputBuffer));
        memset(outputBuffer , 0 , sizeof(outputBuffer)); 

        babyEagleThread->Begin();
    }
    motherEagleThread->Join();
    return 1;
}
//Project compiled with make noVisual -f Makefile  