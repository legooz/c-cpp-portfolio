
#include <stdio.h>


int main(int argc, char **argv) {
  int n, k, l, r, t, d, i;
  char str[65];

  /* Make the user enter a non-negative integer */
  printf("Please enter a non-negative integer: ");
  scanf("%d", &n);
  while (n < 0) {
    printf("Sorry, your input is incorrect.\n");
    printf("Please enter a non-negative integer: ");
    scanf("%d", &n);
  }
    i = 0;
    d = 0;
  /* Convert the integer to reversed binary: e.g. 6 gets converted to 011 */
  if (n == 0) {
    /* Special case for n = 0 */
    str[0] = '0';
    str[1] = '\0';
  } else {
    /* Common case */
    k = n;
    
    while(k > 0){
        if(k % 2 == 0){
            str[i] = '0';
        } else {
            str[i] = '1';
        }
        k = k / 2;
        i++;
        str[i] = '\0';
    }
  }
    
    
  /* The conversion made the string come out reversed, so reverse the string again. 

     DO NOT USE A COPY OF THE STRING. DO NOT USE ANY LIBRARY FUNCTION
     (no strlen or other !)

  */
  
  /* TODO */
char temp;

  for(t = 0; t < i / 2; ++t){
      temp = str[t];
      str[t] = str[i  - 1 - t];
      str[i  - 1 - t] = temp;
  }
  
  /* Display the number and the string */
  printf("The decimal number %d is %s in binary.\n", n, str);
  
  return 0;
}