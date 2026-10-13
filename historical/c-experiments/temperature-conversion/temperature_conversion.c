/******************************************
* CSCE A201
* Fahrenheit to Celsius Conversion
* 9 - 8 - 2022
* Purpose: Convert a Fahrenheit Temp to Celsius
******************************************/

#include "stdio.h"

int main(){
	// the input should've been float
	float celsius;
	int fahrenheit;

	printf("Enter a temperature in Fahrenheit.\n");

	scanf("%d", &fahrenheit);

	/*
	 * When dividing integers you will not get the exact decimal number. Instead it will round the number.
	 * Thus, creating an inaccuracy in the mathematics. Instead of integers, a programmer should use a float.
	 * Which will permit the program to get the ratio of the division in decimal form.
	 *
	 * 	To elaborate, the main issue was the in the program was the division between
	 * 	an integer and a float (5 * (fahrenheit - 32.0)) / 9.0) to be exact.
	 *  The integer is unable to store floating point variables. Instead, the integer
	 * 	will round to a whole number which was creating inaccurate results.
	 *  The order of operations is incorrect multiplication should be utilized before the division. Although,
	 *  I dont think it was creating an issue arithmetically.
	 */

	celsius = (((fahrenheit - 32.0) * 5) / 9.0);

	printf("%d in Fahrenheit is %.2f in Celsius.\n", fahrenheit, celsius);

	return 0;
}
