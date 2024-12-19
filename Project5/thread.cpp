// -------------------------------------------------------
// NAME : Isaac Cooper User ID: ijcooper
// DUE DATE : 11/20/2024
// PROGRAM ASSIGNMENT #5
// FILE NAME : thread.cpp 
// PROGRAM PURPOSE :
// Provides the definition for baby eagle and mother eagle threads 
// 
//
// ----------------------------------------------------
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>
#include "ThreadClass.h"
#include "boat-monitor.h"
#include "thread.h"
#include <time.h>


static boat_monitor boatMon("boat_monitor");

MissionaryThread::MissionaryThread(int misNum)
                :missionaryNum(misNum)
{

}
void MissionaryThread::ThreadFunc()
{
    Thread::ThreadFunc();

    while(1)
    {
        Delay();
        boatMon.MissionaryArrives(missionaryNum);
        
    }
}

CannibalThread::CannibalThread(int canNum)
              :cannibalNum(canNum)
{

}

void CannibalThread::ThreadFunc()
{
    Thread::ThreadFunc();

    while(1)
    {
        Delay();
        boatMon.CannibalArrives(cannibalNum);
        
    }
}

BoatThread::BoatThread(int TotalCrossings)
          :TotalCrossings(TotalCrossings)
{

}

void BoatThread::ThreadFunc()
{
    Thread::ThreadFunc();
    while(1)
    {
        Delay();
        boatMon.boatReady();
        Delay();
        boatMon.boatDone(TotalCrossings);
        
    }
}

