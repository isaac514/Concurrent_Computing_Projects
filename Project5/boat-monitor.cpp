#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>
#include <time.h>
#include "ThreadClass.h"
#include "boat-monitor.h"
#include "thread.h"


boat_monitor::boat_monitor(char * Name ): Monitor(Name , HOARE)
{
    MissionaryCount = 0;
    CannibalCount = 0;
    crossingCounter = 1;

    //Set up the condition variables

    //First waiting queue for missionaries
    CV[0] = new Condition("CV1");
    //First waiting queue for cannibals
    CV[1] = new Condition("CV2");
    //Waiting queue for the boat
    CV[2] = new Condition("CV3");

    //Second waiting queue for missionaries
    CV[3] = new Condition("CV4");
    //Second waiting queue for cannibals
    CV[4] = new Condition("CV5");


        //Intitalize the boat to be empty and passenger number array
        for(int j = 0 ; j < 3 ; j++)
        {
            boat[j].key = EMPTY;
            boat[j].value = 0;
        }
        
}

void boat_monitor::CannibalArrives(int c)
{
    MonitorBegin();

    //If boat is waiting and a full boat can be made signal the boat
    if((MissionaryCount >= 3 || CannibalCount >= 3) && boatWaiting == 1)
    {
        boatWaiting = 0;
        CV[2]->Signal();
    }

    //Wait until signaled, update waiting counter
    CannibalCount++;

    CV[1]->Wait();

    CannibalCount--;

    //View contents of the boat
    //Cannibal Arrives
    // sprintf(outputBuffer , "Cannibal %d arrives\n" , c );
    // write(1 , outputBuffer , strlen(outputBuffer));
    // memset(outputBuffer , 0 ,sizeof(outputBuffer));

    printf("Cannibal %d arrives\n" , c ); 
    

    //Find an empty seat
    for( int b = 0 ; b < 3 ; b++)
    {
        if(boat[b].key == EMPTY)
        {
            fullCounter++;
            boat[b].key = CANNIBAL;
            boat[b].value = c;
    
            // sprintf(outputBuffer , "\tCannibal %d takes a seat\n" , c );
            // write(1 , outputBuffer , strlen(outputBuffer));
            // memset(outputBuffer , 0 ,sizeof(outputBuffer));

            printf("\tCannibal %d takes a seat\n" , c );
            if(fullCounter < 3)
            {
                CV[1]->Signal();
            }
            if(fullCounter == 3)
            {
                CV[2]->Signal();
            }
            break;
        }
    }
    
    MonitorEnd();
}

void boat_monitor::MissionaryArrives(int m)
{
    MonitorBegin();

    //If boat is waiting and a full boat can be made signal the boat
    if((MissionaryCount >= 3 || CannibalCount >= 3) && boatWaiting == 1)
    {
        boatWaiting = 0;
        CV[2]->Signal();
    }

    //Wait until signaled, and update waiting counter
    MissionaryCount++;

    CV[0]->Wait();

    MissionaryCount--;

    //Missionary Arrives
    // sprintf(outputBuffer , "Missionary %d arrives\n" , m );
    // write(1 , outputBuffer , strlen(outputBuffer));
    // memset(outputBuffer , 0 ,sizeof(outputBuffer));

    printf("Missionary %d arrives\n" , m );


    //Find empty seat
    for(int b = 0 ; b < 3 ; b++)
    {
        if(boat[b].key == EMPTY)
        {
           //Reset counter variables   
            boat[b].key = MISSIONARY;
            boat[b].value = m;
            fullCounter++;

            // sprintf(outputBuffer , "\tMissionary %d takes a seat\n" , m );
            // write(1 , outputBuffer , strlen(outputBuffer));
            // memset(outputBuffer , 0 ,sizeof(outputBuffer));

            printf("\tMissionary %d takes a seat\n" , m );
            if(fullCounter < 3)
            {
                CV[0]->Signal();
            }
            if(fullCounter == 3)
            {
                CV[2]->Signal();
            }
            break;
        }
    }
    MonitorEnd();

}

void boat_monitor::boatDone(int CrossingLimit)
{
    MonitorBegin();

    char passengers[3];
    int values[3];
    //Output passenger list
    for(int i = 0 ; i < 3 ; i++)
    {
        if(boat[i].key == CANNIBAL)
        {
            passengers[i] = 'c';
            values[i] = boat[i].value;
        }
        if(boat[i].key == MISSIONARY)
        {
            passengers[i] = 'm';
            values[i] = boat[i].value;
        }
    }
    // sprintf(outputBuffer , "***** Boat load (%d): Passenger list (%c%d, %c%d, %c%d)\n" , crossingCounter, passengers[0] , values[0] , passengers[1] , values[1] , passengers[2], values[2]);
    // write(1 , outputBuffer , strlen(outputBuffer));
    // memset(outputBuffer , 0 ,sizeof(outputBuffer));

    printf("***** Boat load (%d): Passenger list (%c%d, %c%d, %c%d)\n" , crossingCounter, passengers[0] , values[0] , passengers[1] , values[1] , passengers[2], values[2]);

    //drop passengers off
    for( int i = 0 ; i < 3 ; i++)
    {
        boat[i].key = EMPTY;
        boat[i].value = 0;
    }
    
    //Print trip complete
    // sprintf(outputBuffer , "***** Boat load (%d): Completed\n" , crossingCounter);
    // write(1 , outputBuffer , strlen(outputBuffer));
    // memset(outputBuffer , 0 ,sizeof(outputBuffer));

    printf("***** Boat load (%d): Completed\n" , crossingCounter);


    fullCounter = 0;
    crossingCounter++;


    //Check if it is the last crossing
    if(crossingCounter-1 == CrossingLimit)
    {
        // sprintf(outputBuffer , "MONITOR: %d crosses have been made.\nMONITOR: This river cross is closed indefinitely for renovation.\n" , CrossingLimit);
        // write(1 , outputBuffer , strlen(outputBuffer));
        // memset(outputBuffer , 0 ,sizeof(outputBuffer));

        printf("MONITOR: %d crosses have been made.\nMONITOR: This river cross is closed indefinitely for renovation.\n" , CrossingLimit);
        Exit();
    }
    MonitorEnd();
}

void boat_monitor::boatReady()
{
    MonitorBegin();

    //Wait until signaled for a possible boat load
    if ((MissionaryCount + CannibalCount) < 3) 
    {
        // sprintf(outputBuffer , "Missionary %d , Cannibal %d\n" , MissionaryCount , CannibalCount);
        // write(1 , outputBuffer , strlen(outputBuffer));
        // memset(outputBuffer , 0 ,sizeof(outputBuffer));

        printf("Missionary %d , Cannibal %d\n" , MissionaryCount , CannibalCount);
        boatWaiting = 1;
        CV[2]->Wait();
    }
    
        // sprintf(outputBuffer , "Missionary %d , Cannibal %d\n" , MissionaryCount , CannibalCount);
        // write(1 , outputBuffer , strlen(outputBuffer));
        // memset(outputBuffer , 0 ,sizeof(outputBuffer));

         printf("Missionary %d , Cannibal %d\n" , MissionaryCount , CannibalCount);
        
        //Can make any combination of threads
        if(MissionaryCount >= 3 && CannibalCount >= 3)
        {
            srand(time(0));
            int value = rand() % 2;
            if(value == 0)
            {
                CV[0]->Signal();
                CV[2]->Wait();
            }
            else
            {
                CV[1]->Signal();
                CV[2]->Wait();
            }
        }
        else if(MissionaryCount >= 3)
        {
            CV[0]->Signal();
            CV[2]->Wait();
        }
        else
        {
            CV[1]->Signal();
            CV[2]->Wait(); 
        }

    //Boat properly consturcted
    // sprintf(outputBuffer , "***** The boat is ready\n");
    // write(1 , outputBuffer , strlen(outputBuffer));
    // memset(outputBuffer , 0 ,sizeof(outputBuffer));

    printf("***** The boat is ready\n");
    
    int tempOutputArr[3];
    
    int mCount = 0;
    int cCount = 0;
    for(int i = 0 ; i < 3 ; i++)
    {
        if(boat[i].key == CANNIBAL)
        {
            cCount++;
            tempOutputArr[i] = boat[i].value;
        }
        if(boat[i].key == MISSIONARY)
        {
            mCount++;
            tempOutputArr[i] = boat[i].value;
        } 
    }

    //Three missionarys
    if(mCount == 3)
    {
        // sprintf(outputBuffer , "MONITOR(%d): three missionaries (%d, %d, %d) are selected\n" , crossingCounter ,tempOutputArr[0] , tempOutputArr[1], tempOutputArr[2]);
        // write(1 , outputBuffer , strlen(outputBuffer));
        // memset(outputBuffer , 0 ,sizeof(outputBuffer));

        printf("MONITOR(%d): three missionaries (%d, %d, %d) are selected\n" , crossingCounter ,tempOutputArr[0] , tempOutputArr[1], tempOutputArr[2]);
    }
    //Three cannibals
    else if(cCount == 3)
    {
        // sprintf(outputBuffer , "MONITOR(%d): three cannibals (%d, %d, %d) are selected\n" , crossingCounter ,tempOutputArr[0] , tempOutputArr[1], tempOutputArr[2]);
        // write(1 , outputBuffer , strlen(outputBuffer));
        // memset(outputBuffer , 0 ,sizeof(outputBuffer));

        printf("MONITOR(%d): three cannibals (%d, %d, %d) are selected\n" , crossingCounter ,tempOutputArr[0] , tempOutputArr[1], tempOutputArr[2]);
    }
    //one canibal two missionaries
    else
    {
        int missionaryIndex1 = 0;
        int missionaryIndex2 = 0;
        int cannibalIndex = 0;

        //Find index for cannibal
        for(int i = 0 ; i < 3 ; i++)
        {
            if(boat[i].key == CANNIBAL)
            {
                cannibalIndex = i;
                break;
            }
        }
        if(cannibalIndex == 0)
        {
            missionaryIndex1 = 1;
            missionaryIndex2 = 2;
        }
        else if(cannibalIndex == 1)
        {
            missionaryIndex1 = 0;
            missionaryIndex2 = 2;
        }
        else
        {
            missionaryIndex1 = 0;
            missionaryIndex2 = 1;
        }

        // sprintf(outputBuffer , "MONITOR(%d): one cannibal (%d) and two missionaries (%d, %d) are selected\n" , crossingCounter ,boat[cannibalIndex].value , boat[missionaryIndex1].value, boat[missionaryIndex2].value);
        // write(1 , outputBuffer , strlen(outputBuffer));
        // memset(outputBuffer , 0 ,sizeof(outputBuffer));

        printf("MONITOR(%d): one cannibal (%d) and two missionaries (%d, %d) are selected\n" , crossingCounter ,boat[cannibalIndex].value , boat[missionaryIndex1].value, boat[missionaryIndex2].value);
    }

    MonitorEnd();
}


