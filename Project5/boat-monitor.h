// -------------------------------------------------------
// NAME : Isaac Cooper User ID: ijcooper
// DUE DATE : 11/20/024
// PROGRAM ASSIGNMENT #5
// FILE NAME : thread.h
// PROGRAM PURPOSE :
// Provides the definiton for boat monitor
// ----------------------------------------------------
#include <iostream>
#include "ThreadClass.h"

enum passengers {CANNIBAL , MISSIONARY , EMPTY};

struct Pairs
        {
            enum passengers key;
            int value;
        };

class boat_monitor : public Monitor
{
    public:
        boat_monitor(char * Name);
        void boatReady();
        void boatDone(int totalCrossings);
        void CannibalArrives(int c);
        void MissionaryArrives(int m);
    private:
        Condition *CV[5];
        struct Pairs boat[3];
        int tripInProgress = 0;
        int fullCounter = 0;
        int crossingCounter = 0;
        int MissionaryCount = 0;
        int CannibalCount = 0;
        int boatWaiting = 0;


};







