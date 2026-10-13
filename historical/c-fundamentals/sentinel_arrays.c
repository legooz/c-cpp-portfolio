
#include <stdio.h>


int main(int argc, char **argv) {
  const int MAX_NUMBER_OF_ELEMENTS = 10;
  double values[MAX_NUMBER_OF_ELEMENTS];
  int i;
  double elem;
  int k;

  /* Arrays with a maximum size that do not get used up completely 
     are called 

     OVERSIZED ARRAYS.

     A technique to indicate how many elements are real-world values
     inside the array is based on values which never occur in real life.

     Examples:

     * Students' points in assignments: there is never a negative number of points
     
     * There is never a negative distance between 2 cities
     
     * The selling price of a product is never negative

     * If a computer gets used to store birthdates of people using these computers,
       nobody is born before 1900.

     * Temperatures in Kelvin/Rankine are always positive or zero, never negative.

     In these cases, one can use a value that does not exist (which is
     impossible in real life) as a marker to say: this array is over.

     For example, we have an array with a maximum of 7 elements, but
     only 3 valid temperatures in Kelvin

     0    1    2    3    4    5    6
     273  300  199  -1   ?    ?    ?
                    ^
                    |---  Marker to tell: real values are over

     Such a marker is called a

     SENTINEL VALUE

     in Computer Science.

  */
  printf("Please enter up to %d positive or zero values. Enter a negative value to stop entering values.\n", MAX_NUMBER_OF_ELEMENTS);
  for (i=0; i<MAX_NUMBER_OF_ELEMENTS; i++) {
    printf("Please enter a positive or zero value, enter a negative value when done: ");
    scanf("%lf", &values[i]);
    if (values[i] < 0.0) {
      break;
    }
  }

  /* TODO #1:  Print all the real-world values in the array (the positive or zero ones).

               Print one value per line. 

	       DO NOT PRINT THE SENTINEL VALUE!!!!

	       CAUTION: There are 2 cases possible

	       a) All the values in the array are real-world
	       values. YOU ARE NEVER GOING TO ENCOUNTER THE SENTINEL!

	       b) There is a sentinel value. You need to stop short of
	       it.
  
	       CAUTION: NEVER EVER ACCESS AN ARRAY ELEMENT BEYOND THE ARRAY!

	       DO NOT USE break !!!
  */
  for (i=0; (i < MAX_NUMBER_OF_ELEMENTS) && (values[i] >= 0.0); i++) {
    printf("%lf\n", values[i]);
  }

  /* Have the user enter a positive or zero value */
  printf("Please enter a positive or zero value: ");
  scanf("%lf", &elem);
  while (!(elem >= 0.0)) {
    printf("Sorry. The value you entered, %lf, is not positive or zero.\n", elem);
    printf("Please enter a positive or zero value: ");
    scanf("%lf", &elem);
  }

  /* TODO #2: Determine the least index k of an element in the array -
              BEFORE THE SENTINEL OF COURSE - that is equal to elem.

	      If there is no real-world value in the array equal to 
	      elem, set k to a negative value, typically -1.

	      If there is a real-world value in the array equal to
	      elem, set k to the index of the box containing that
	      element.

	      If there is more than 1 element in the array containing 
	      elem, set k to the least index possible.

  */
  k = -1;
  for (i=0; (i < MAX_NUMBER_OF_ELEMENTS) && (values[i] >= 0.0); i++) {
    if (values[i] == elem) {
      k = i;
      break;
    }
  }
  
  if (k >= 0) {
    printf("The value %lf figures in the %d-th place of the list of values you entered.\n", elem, k+1); 
  } else {
    printf("The value %lf does not figure in the list of values you entered.\n", elem); 
  }

  return 0;
}
