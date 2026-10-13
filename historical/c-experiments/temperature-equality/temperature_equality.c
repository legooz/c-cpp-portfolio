/******************************************************************************
* Temperature Equality Search
* 9-8-2022
* 
* Purpose: by brute force using a loop to find the tempature at which celsius and fahrenheit are 
* equivilant between integers -100 and 100.
****************************************************************************/


#include <stdio.h>

int main (){
  float fahrenheit;
  float celsius;

    for (fahrenheit = -100; fahrenheit < 100; fahrenheit++)
    {
        celsius = (((fahrenheit - 32.0) * 5) / 9.0);
        
        if (fahrenheit == celsius)
        {
            printf ("fahrenheit %f : celsius %f\n", fahrenheit, celsius);
        }
    }

  return 0;
}
