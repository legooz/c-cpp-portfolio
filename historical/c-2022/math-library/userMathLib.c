#include <stdio.h>




/*****************************************************************
* Name: babylonian
* Description: This function computes the Babylonian alogrithms square root.
* Inputs: an double value representing the value of the delcared variables.
* Returned value: a double value representing the square root of the input.
* Preconditions: -
*****************************************************************/
    double babylonian(double n)
    {   

    double answer;
    double r;

    answer = n / 2.0;

        for(int i = 0; i < 1000; i++)
        {

            r = n / answer;
            answer = (answer + r) / 2.0;

        }        

        return answer;
    }

/*****************************************************************
* Name: absoluteValue
* Description: This function computes the absolute value of an integer.
* Inputs: an integer value representing the value of the initailized variables in main.c.
* Returned value: a int value representing the absolute value of an integer.
* Preconditions: -
*****************************************************************/    

    int absoluteValue(int n)
    {
        
        if(n < 0)
        {
            n = n * -1;
        }

        return n;
    }