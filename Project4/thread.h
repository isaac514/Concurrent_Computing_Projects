// -------------------------------------------------------
// NAME : Isaac Cooper User ID: ijcooper
// DUE DATE : 11/4/024
// PROGRAM ASSIGNMENT #4
// FILE NAME : thread.h
// PROGRAM PURPOSE :
// Provides the definiton for threads for thread mentor
// ----------------------------------------------------
#include <iostream>
#include "ThreadClass.h"

// -------------------------------------------------------
// FUNCTION BabyEagleThread  : 
// Defines the constuctor and internal variables for Baby Eagle threads
// PARAMETER USAGE :
// int t - the number of servings
// int m - the number of pots
// int* potVector - array representing the pots 
// int eagleNum - represents each of the eagles
// --------------------------------------------------------
class BabyEagleThread : public Thread
{
public:
    //Constructor
    BabyEagleThread(int eaglenum , int *potVector, int m, int t);
private:
    void ThreadFunc();
    int eagleNum;
    int *potVector;
    int t;
    int m;
    
};
// -------------------------------------------------------
// FUNCTION MotherEagleThread  : 
// Defines the constuctor and internal variables for Baby Eagle threads
// PARAMETER USAGE :
// int t - the number of servings
// int m - the number of pots
// int n = the number of baby eagles
// int* potVector - array representing the pots 
// --------------------------------------------------------
class MotherEagleThread : public Thread
{
public:
    MotherEagleThread(int t , int *potVector, int m, int n);
private:
void ThreadFunc();
int t;
int m;
int n;
int *potVector;
int counter;
};

int ready_to_eat(int potVector[] , int threadNum , int m , int t );
void finish_eating(int threadNum , int t);
int goto_sleep();
void food_ready(int potVector[], int m, int n, int t);
int random_delay();




