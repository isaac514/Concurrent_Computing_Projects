/* ----------------------------------------------------------- */
/* NAME : Isaac Cooper User ID: ijcooper */
/* DUE DATE : 9/16/2024 */
/* PROGRAM ASSIGNMENT #1 */
/* FILE NAME : prog1.c */
/* PROGRAM PURPOSE : Run various programs concurrently with the use of fork() , exit(), wait()*/
/* Program contain 3 methods that perform specfied action dependent on program arguments. The main function calls these functions and uses fork() to ensure */
/* that child proccess are created that run concurrent in the order specfied by the assignment description */
/* ----------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <string.h>

//To compile
//gcc prog1.c -lm -o prog1

/* ----------------------------------------------------------- */
/* FUNCTION: fibCalc() */
/* Calculate the nth fibonacci number recursively */
/* PARAMETER USAGE : */
/* int n = nth term in the fibonacci sequence to be calculated */
/* ----------------------------------------------------------- */
int fibCalc(int n ) 
{
    //Return 0 for case fibCalc(0)
    if(n == 0)
    {
        return 0;
    }

    //Recursive definiton of nth fibonacci number
    else if (n > 2)
    {
        return fibCalc(n-1) + fibCalc(n-2); 
    }

    //Return 1 for cases fibCalc(2) and fibCalc(1)   
    else
    {
        return 1;
    }    
}

/* ----------------------------------------------------------- */
/* FUNCTION: fibCalcOutput */
/* Helper function to print the output calculation from fibCalc() */
/* PARAMETER USAGE : */
/* int n = nth term in the fibonacci sequence to be calculated  */
/* FUNCTION CALLED : */
/* fibCalc() */
/* ----------------------------------------------------------- */
void fibCalcOutput(int n )
{
    int fibOutput = 0;
    fibOutput =fibCalc(n);
    char outputBuffer[1000];

    sprintf(outputBuffer , "    Fibonacci Process Started\n");
    write(1 , outputBuffer , strlen(outputBuffer));

    sprintf(outputBuffer , "    Input Number %d \n" , n );
    write(1 , outputBuffer , strlen(outputBuffer));

    //Print Process information
    sprintf(outputBuffer, "    Fibonacci Number f(%d) is %d \n" , n , fibOutput);
    write(1 , outputBuffer , strlen(outputBuffer));

    sprintf(outputBuffer , "    Fibonacci Process Exits\n\n");
    write(1 , outputBuffer , strlen(outputBuffer));
    exit(0);
}

/* ----------------------------------------------------------- */
/* FUNCTION: calcEllipseArea */
/* Estimate the area of an ellipse by random point generation */
/* PARAMETER USAGE : */
/* int a = Semi-Major Axis, int b = Semi-Minor Axis, int s = Number of random point to be generated */
/* ----------------------------------------------------------- */
void calcEllipseArea(int a , int b , int s)
{
    double x = 0;
    double y = 0;
    int t = 0;
    double ratio = 0;
    double estArea = 0;
    double actualArea = 0;
   char outputBuffer[1000]; 

    //Print process infomation
    sprintf(outputBuffer , "        Ellipse Area Process Started\n");
    write(1 , outputBuffer , strlen(outputBuffer));

    sprintf(outputBuffer, "        Total random Number Pairs %d \n" , s);
    write(1 , outputBuffer , strlen(outputBuffer));

    sprintf(outputBuffer, "        Semi-Major Axis Length %d \n" , a);
    write(1 , outputBuffer , strlen(outputBuffer));

    sprintf(outputBuffer, "        Semi-Minor Axis Length %d \n" , b);
    write(1 , outputBuffer , strlen(outputBuffer));
    
    //Reset the seed rand() function 
    srand(time(NULL));

    //Iterate s times generating random points 
    for ( int i = 0 ; i < s ; i++)
    {
        //Generate point x and y 
        x = (((double) rand()) / RAND_MAX) * a;
        y = (((double) rand()) / RAND_MAX) * b ;

        //Check to see if points are within the ellipse
        if( (((x*x) / (a*a) ) + ((y*y) / (b*b)) ) <= 1 ) 
        {
            t++;
        }
    }
    sprintf(outputBuffer , "        Total Hits %d \n" , t);
    write(1 , outputBuffer , strlen(outputBuffer));

    ratio = t / (double)s;

    //After loop finishes, calculate actual area and estimated area
    estArea = (ratio * ((double)a * (double)b)) * 4;
    actualArea = ((acos(-1.0)) * (double)a * (double)b);

    sprintf(outputBuffer,"        Estimated Area %f \n" , estArea);
    write(1 , outputBuffer , strlen(outputBuffer));

    sprintf(outputBuffer , "        Actual Area %f \n" , actualArea); 
    write(1 , outputBuffer , strlen(outputBuffer));

    //Process complete
    sprintf(outputBuffer , "        Ellipse Area Process Exits\n\n");
    write(1 , outputBuffer ,strlen(outputBuffer));

    exit(0);
}

/* ----------------------------------------------------------- */
/* FUNCTION: histogramOutput */
/* Helper function for pinball function for printing output */
/* PARAMETER USAGE : */
/* double perc = percentage of balls in each bin */
/* FUNCTION CALLED : */
/* pinballCalc() */
/* ----------------------------------------------------------- */
void histogramOutput(double perc)
{
    char outputBuffer[1000];
    double ratio = 0.6;
    double barLength;
    

    //Calculate the barLength as a double
    barLength = perc / ratio;

    for ( int i = 0 ; i < (int)barLength ; i++ )
    {
        sprintf(outputBuffer , "*");
        write(1 , outputBuffer ,strlen(outputBuffer));
    }
    sprintf(outputBuffer , "\n");
    write(1 , outputBuffer , strlen(outputBuffer));
}

/* ----------------------------------------------------------- */
/* FUNCTION: pinballCalc */
/* Simulate a pinball game by generating */
/* PARAMETER USAGE : */
/* int x = Number of buckets for balls to fall into, int y = Number of balls to be dropped   */
/* ----------------------------------------------------------- */
void pinballCalc(int x , int y) 
{
    double pos;
    int direction;
    int bucketArray[x];
    int pass = x-1;
    int upperbound = 1;

    //Intialize bucketArray to zero
    memset(bucketArray , 0 , sizeof(bucketArray));

    //Reset the seed rand() function 
    srand(time(NULL));

    //Simulate dropping balls y amount of times
    for (int i = 0 ; i < y ; i++)
    {        
        //Intialize starting postion on outmost loop iteration
        pos = ((double)x - 1) / 2;

        //Each ball will under x-1 decision for if it bounces left or right
        for (int j = 0 ; j < pass ;j++)
        {
            //Constrain random number generation to 1s and Os to simulate balls going right or left
            direction = rand() % (upperbound + 1);

            //Case for left bounce
            if(direction == 0)
            {
                pos -= 0.5;

            }

            //Case for right bounce
            else
            {
                pos += 0.5;
            }
        }
        //Ending postion has been generated
        //Increment the value at bucket[pos] by 1 to indicate frequency
        bucketArray[(int)pos] += 1;
    }

    //Calculate the percentages for each of the balls in the buckets
    //Relative to the total amount of balls dropped
    char outputBuffer[1000];
    sprintf(outputBuffer , "Simple Pinball Process Started \nNumber of Bins %d \nNumber of balls dropping %d \n", x , y);
    write(1 , outputBuffer , strlen(outputBuffer));

    //Reset the output buffer
    memset(outputBuffer , 0 , sizeof(outputBuffer));
    
    //Test output for bucketArray
    for ( int k = 0 ; k < x ; k++)
    {
        //Printing information for each bin
        sprintf(outputBuffer , "%3d -( %7d) - (%5.2f%%) | ", k+1 , (int)bucketArray[k] , ((float)bucketArray[k]/(float)y) * 100 );
        write(1 , outputBuffer , strlen(outputBuffer));
        
        //Call histogram function for remaining output
        histogramOutput(((float)bucketArray[k]/(float)y) * 100);

    }
    sprintf(outputBuffer , "Simple pinball process exits\n");
    write(1 , outputBuffer ,strlen(outputBuffer));
    exit(0);
}


int main(int argc , char** argv)
{

//Error checking for correct number of command line args
if (argc < 7)
{
    write(1 , "Invalid number of program arguments" , 36);
    return -1;
}

//Program arguments ./prog1 n a b s x y
//                      0   1 2 3 4 5 6

//Parsing program arguments
int n, a, b, s, x, y;
pid_t p1, p2, p3;

n = atoi(argv[1]);
a = atoi(argv[2]);
b = atoi(argv[3]);
s = atoi(argv[4]);
x = atoi(argv[5]);
y = atoi(argv[6]);

char mainProccesBuffer[1000];


        //Main process information
        sprintf(mainProccesBuffer ,"Main Process Started\nFibonacci Input             = %d\nTotal random Number Pairs   = %d\nSemi-Major Axis Length      = %d\nSemi-Minor Axis Length      = %d\nNumber of bins              = %d\nNumber of Ball Droppings    = %d\n\n" , n , s , a , b , x , y );
        write(1 , mainProccesBuffer , strlen(mainProccesBuffer));

        //Process Control flow
        p1 = fork();
        if (p1 > 0 )
        {
            p2 = fork();

            if(p2 > 0)
            {
                p3 = fork();
                if (p3 == 0) 
                {
                    //Child process  for pinballCalc
                    write(1 ,"Pinball Process Created\n", 25 );
                    pinballCalc(x , y);
                }
            }
            else
            {
                //Child process for calcEllipseArea
                write(1 ,"Ellipse Area Process Created\n", 30);  
                calcEllipseArea(a , b , s);
            }
        }
        else
        {
            
            //Child process for fibCalc
            write(1 ,"Fibonacci Process Created\n", 27 ); 
            fibCalcOutput(n);
        }

        //Parent waits three times for the three child processes
        write(1 , "Main Process Waits\n" , 20);
        for(int j = 0 ; j < 3 ; j ++)
        {
            wait(NULL);
        }

    //Main process exits
    write(1 , "Main Process Exits" , 19 );
    exit(0);
}
    

