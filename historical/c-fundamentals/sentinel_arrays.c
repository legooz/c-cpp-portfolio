
#include <stdio.h>


int main(int argc, char **argv) {
  const int MAX_NUMBER_OF_ELEMENTS = 10;
  double values[MAX_NUMBER_OF_ELEMENTS];
  int i;
  double elem;
  int k;

  /* Store up to ten nonnegative values; a negative value marks the end. */
  printf("Please enter up to %d positive or zero values. Enter a negative value to stop entering values.\n", MAX_NUMBER_OF_ELEMENTS);
  for (i=0; i<MAX_NUMBER_OF_ELEMENTS; i++) {
    printf("Please enter a positive or zero value, enter a negative value when done: ");
    scanf("%lf", &values[i]);
    if (values[i] < 0.0) {
      break;
    }
  }

  /* Print values up to the negative sentinel or the array capacity. */
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

  /* Find the first matching value before the sentinel; use -1 when absent. */
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
