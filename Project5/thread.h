// -------------------------------------------------------
// NAME : Isaac Cooper User ID: ijcooper
// DUE DATE : 11/20/024
// PROGRAM ASSIGNMENT #5
// FILE NAME : thread.h
// PROGRAM PURPOSE :
// Provides the definiton for threads for thread mentor
// ----------------------------------------------------
#include <iostream>
#include "ThreadClass.h"

// -------------------------------------------------------
// FUNCTION MissionaryThread  : 
// Defines the constuctor and internal variables for Missionary threads
// PARAMETER USAGE :
// --------------------------------------------------------
class MissionaryThread : public Thread
{
public:
    //Constructor
    MissionaryThread(int missionaryNum);
private:
    void ThreadFunc();
    int missionaryNum;
    
};
// -------------------------------------------------------
// FUNCTION CannibalThread  : 
// Defines the constuctor and internal variables for Cannibal threads
// PARAMETER USAGE :
// --------------------------------------------------------
class CannibalThread : public Thread
{
public:
    CannibalThread(int cannibalNum);
private:
void ThreadFunc();
int cannibalNum;
};

// -------------------------------------------------------
// FUNCTION CannibalThread  : 
// Defines the constuctor and internal variables for Cannibal threads
// PARAMETER USAGE :
// --------------------------------------------------------
class BoatThread : public Thread
{
public:
    BoatThread(int TotalCrossings);
private:
void ThreadFunc();
int crossingCounter;
int TotalCrossings;
};
