/******************************************
* Math Library Demo
* Description: This program utilizes .h files and .c files to create multiple files, with
*  a small math library. It calls onto the math library to utilize it's functions to
* achieve the results.
******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userMathLib.h"


int main()
{
    int testInt = 0;
    double testDouble = 0;
    int absResult = 0;
    double bblResult = 0;

    printf("Enter an integer to test the Absolute Value Function:\n");
    scanf("%d", &testInt);

    printf("Enter an integer to test the Babylonian Function:\n");
    scanf("%lf", &testDouble);


    //absolute value function call from .h file
    absResult = absoluteValue(testInt);
    printf("\nAbsolute Value Function Result: %d\n", absoluteValue(testInt));

    //babylonian function call from .h file
    bblResult = babylonian(testDouble);
    printf("\nBabylonian Function Result:%.2lf\n", bblResult);

    return 0;
}