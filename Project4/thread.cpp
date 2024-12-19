// -------------------------------------------------------
// NAME : Isaac Cooper User ID: ijcooper
// DUE DATE : 11/6/2024
// PROGRAM ASSIGNMENT #4
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
#include "thread.h"
#include <time.h>

int emptypots = 0;
int awakeMother = 0;
int feedingNumber = 1; 
int exitflag = 0;

//Initialize semaphores
Semaphore *MotherSem = new Semaphore("M",0);
Semaphore *BabySem = new Semaphore("B",0);
Semaphore *Mutex = new Semaphore("Mutex" , 1);

// -------------------------------------------------------
// FUNCTION BabyEagleThread  : 
// Defines the constuctor and internal variables for Baby Eagle threads
// PARAMETER USAGE :
// int t - the number of servings
// int m - the number of pots
// int* potVector - array representing the pots 
// int eagleNum - represents each of the eagles
// --------------------------------------------------------
BabyEagleThread::BabyEagleThread(int eagleNum , int *potVector , int m , int t)
                :eagleNum(eagleNum) , potVector(potVector), m(m) , t(t)
{

}


void BabyEagleThread::ThreadFunc()
{
    Thread::ThreadFunc();

    while(1)
    {
        Delay();

        ready_to_eat(potVector,eagleNum,m,t);

        //Random delay
        int n = random_delay();

        for (int j = 0 ; j < n ; j++)
        {
            Delay();
        }

        //Search for a full pot and eat
        int i = 0;
        for(i = 0 ; i < m ; i++)
        {
            //found a full pot to consume
            if(potVector[i] == 1)
            {
                //Eat from pot i 
                potVector[i] = 0;
                char outputBuffer[1000];
                sprintf(outputBuffer , "\tBaby Eagle %d is eating using feeding pot %d.\n\n", eagleNum , i);
                write(1 , outputBuffer , strlen(outputBuffer));
                memset(outputBuffer , 0 , sizeof(outputBuffer));
                break;
            }
        }
        //Call finish eating 
        finish_eating(eagleNum,t);
    }

}
// -------------------------------------------------------
// FUNCTION MotherEagleThread  : 
// Defines the constuctor and internal variables for Baby Eagle threads
// PARAMETER USAGE :
// int t - the number of servings
// int m - the number of pots
// int n = the number of baby eagles
// int* potVector - array representing the pots 
// --------------------------------------------------------
MotherEagleThread::MotherEagleThread(int t , int *potVector , int m , int n)
                  :t(t) , potVector(potVector) , m(m) , n(n)
                
{

}

void MotherEagleThread::ThreadFunc()
{
    Thread::ThreadFunc();
    while (feedingNumber <= t)
    {
        //Mother goes to sleep
        int awake = goto_sleep();
        
        Delay();

        //Prepare the food
        food_ready(potVector, m, n,t);

        Delay();
        

        if(exitflag == 1)
        {
            char outputBuffer[1000];
            sprintf(outputBuffer , "Mother eagle retires after serving %d feedings. Game ends!!!\n\n" , t);
            write(1 , outputBuffer , strlen(outputBuffer));
            Exit();
        }

        Delay(); 
    }
}
// -------------------------------------------------------
// FUNCTION ready_to_eat : 
// Outputs that the baby eagle is ready to eat, and notifies 
// the mother eagle thread if all of the pots are empty
// --------------------------------------------------------
int ready_to_eat(int potVector[], int threadNum, int m , int t)
{
    if( t+1 == feedingNumber)
        {
            BabySem->Wait();
        }

    char outputBuffer[1000];
    sprintf(outputBuffer , "\tBaby Eagle %d is ready to eat.\n\n" , threadNum);
    write(1 , outputBuffer , strlen(outputBuffer));
    memset(outputBuffer , 0 , sizeof(outputBuffer));
    
    //Check pot vector for empty pots
    Mutex->Wait(); 
    emptypots = 0;
    for(int i = 0 ; i < m ; i++)
    {
        //found an empty pot
        if(potVector[i] == 0)
        {
            emptypots++;
        }
    }
    //All the pots are empty
    if (emptypots == m)
    {
                //Signal Mother eagle to wake up if she has not already been woken by another thread
                sprintf(outputBuffer , "\tBaby Eagle %d sees all feeding pots are empty and wakes up the mother.\n\n" , threadNum);
                write(1 , outputBuffer , strlen(outputBuffer));
                memset(outputBuffer , 0 , sizeof(outputBuffer));
                MotherSem->Signal();
                sprintf(outputBuffer , "\tMother Eagle is awoke by baby eagle %d and starts preparing food.\n\n" , threadNum);
                write(1 , outputBuffer , strlen(outputBuffer));
                memset(outputBuffer , 0 , sizeof(outputBuffer));
                BabySem->Wait(); 
    }
    Mutex->Signal();
    return 1;
}
// -------------------------------------------------------
// FUNCTION finish_eating : 
// Outputs that the baby eagle thread has consumed the food in 
// a pot within the potVector
// --------------------------------------------------------
void finish_eating(int threadNum, int t )
{
    //Ensure that baby eagle threads are blocked for final output
    if( t+1 == feedingNumber)
        {
            BabySem->Wait();
        }

    char outputBuffer[1000];
    sprintf(outputBuffer , "\tBaby Eagle %d finishes eating.\n\n" , threadNum);
    write(1 , outputBuffer , strlen(outputBuffer));
    memset(outputBuffer , 0 , sizeof(outputBuffer));


}
// -------------------------------------------------------
// FUNCTION goto_sleep : 
// Ensures that the mother eagle thread waits until she is woken up by one 
// of the baby eagles that has recognized that all of the pots are empty
// --------------------------------------------------------
int goto_sleep()
{
    char outputBuffer[1000];
    sprintf(outputBuffer , "Mother Eagle takes a nap.\n\n" );
    write(1 , outputBuffer , strlen(outputBuffer));
    memset(outputBuffer , 0 , sizeof(outputBuffer));

    MotherSem->Wait();
    emptypots = 0;
    return 1;

}
// -------------------------------------------------------
// FUNCTION food_ready : 
// Resupplies the pot Vector with food and signals the baby eagle threads
// that are in the waiting state
// PotVector[element] = 0 represents an empty pot
// PotVector[element] = 1 represents a full pot 
// --------------------------------------------------------
void food_ready(int potVector[], int m, int n, int t )
{
    
    char outputBuffer[1000];
    //Fill all the pots
    for(int i = 0 ; i < m ; i++)
    {
        potVector[i] = 1;
    }

    sprintf(outputBuffer , "Mother Eagle says \"Feeding  (%d)\" .\n\n" , feedingNumber);
    write(1 , outputBuffer , strlen(outputBuffer));
    memset(outputBuffer , 0 , sizeof(outputBuffer));
    
        BabySem->Signal();
        if(feedingNumber == t)
        {
            MotherSem->Wait();
            exitflag = 1;
        }
         feedingNumber++; 
}

// -------------------------------------------------------
// FUNCTION random_delay : 
// Helper function used to generate a random delay for threads
// to produced various interleavings
// --------------------------------------------------------
int random_delay()
{
    int N = 100;
    int value = rand() % (N+1);

    return value;
}