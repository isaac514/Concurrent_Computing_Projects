// -------------------------------------------------------
// NAME : Isaac Cooper User ID: ijcooper
// DUE DATE : 10/13/024
// PROGRAM ASSIGNMENT #3
// FILE NAME : thread.h
// PROGRAM PURPOSE :
// Provides the definiton for threads for thread mentor
// ----------------------------------------------------
#include <iostream>
#include "ThreadClass.h"

// -------------------------------------------------------
// FUNCTION PrefixSumThread : 
// Defines the constuctor and internal variables for threads
// PARAMETER USAGE :
// int ** arrayB (the output array to be continuosly updated)
// int i (outer index for each run)
// int j (inner index for each thread)
// --------------------------------------------------------
class PrefixSumThread : public Thread
{
public:
    //Constructor
    PrefixSumThread(int ** ArrayB, int i , int j );
private:
    void ThreadFunc();
    int i;
    int index;
    int j;
    int **B; 
};

//Project compiled with make noVisual -f Makefile 




