// -------------------------------------------------------
// NAME : Isaac Cooper User ID: ijcooper
// DUE DATE : 11/20/024
// PROGRAM ASSIGNMENT #5
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

int c; //Number of cannabals
int m; //Number of Missionaries
int b; //Number of boat crossing
MissionaryThread * missionaryThread;
CannibalThread * cannibalThread;
BoatThread * boatThread;

int main(int argc , char * argv[])
{
    c = atoi(argv[2]);
    m = atoi(argv[3]);
    b = atoi(argv[4]);

    //Handle case if any of the input arguements are zero
    if((c == 0) || (m == 0) || (b == 0))
    {
        c = 8;
        m = 8;
        b = 5;
    }

    //char outputBuffer[1000];

    //Print boat thread info
    // sprintf(outputBuffer , "*****BOAT thread starts\n");
    // write(1 , outputBuffer ,strlen(outputBuffer));
    // memset(outputBuffer, 0 , sizeof(outputBuffer));
    printf( "*****BOAT thread starts, missionaries %d , cannibals %d , iterations %d \n " , m , c , b);

    //Start the boat thread
    boatThread = new BoatThread(b);
    boatThread->Begin();

    //Start the missionary threads
    for(int i = 0 ; i < m ; i++)
    {
        //Print cannibal thread info
        // sprintf(outputBuffer , "Missionary %d starts\n" , i+1);
        // write(1 , outputBuffer , strlen(outputBuffer));
        // memset(outputBuffer , 0 , sizeof(outputBuffer));

        printf("Missionary %d starts\n" , i+1);

        missionaryThread = new MissionaryThread(i+1);
        missionaryThread->Begin();
    }
    

    //Start the cannibal threads
    for(int j = 0 ; j < c ; j++)
    {
        //Print cannibal thread info
        // sprintf(outputBuffer , "Cannibal %d starts\n" , j+1);
        // write(1 , outputBuffer , strlen(outputBuffer));
        // memset(outputBuffer , 0 , sizeof(outputBuffer));

        printf("Cannibal %d starts\n" , j+1);

        cannibalThread = new CannibalThread(j+1);
        cannibalThread->Begin();
    }
    printf( "*****BOAT thread starts, missionaries %d , cannibals %d , iterations %d \n " , m , c , b);

    //Start the boat thread
    boatThread = new BoatThread(b);
    boatThread->Begin();

}