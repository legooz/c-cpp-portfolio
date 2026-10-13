
#include <stdio.h>

int main(int argc, char **argv) {
  const int BUF_LEN = 128;
  char haystack[BUF_LEN];
  char needle[BUF_LEN];
  char c;
  int i, j, substring, found;
  int needle_len, haystack_len;

  /* Get the user to enter two strings */
  printf("Please enter a string, finishing the entry by pressing Enter.\n");  
  for (i=0; i<BUF_LEN-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    needle[i] = c;
  } 
  needle[i] = '\0';

  printf("Please enter another string, finishing the entry by pressing Enter.\n");
  for (i=0; i<BUF_LEN-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    haystack[i] = c;
  } 
  haystack[i] = '\0';
  
  /* Print the string once */
  printf("The strings you entered are \"%s\" and \"%s\".\n", needle, haystack);

  /* Determine if needle is contained in the haystack

     Set the variable substring to 1 if the needle is in the haystack.

     Set the variable substring to 0 if the needle is not in the
     haystack.

     DO NOT DECLARE ANY OTHER VARIABLES; USE ONLY THE ONES ALREADY
     DECLARED.

     Examples:

     needle = "adam" is contained in haystack = "Madame Bovary"

     needle = "" is contained in haystack = "Hello World"

     needle = "or" is contained in haystack = "Hello World"

     needle = "orange" is not contained in haystack = "Goranje"

     needle = "banana" is contained in haystack = "banana"
     
     Needles longer than the haystack can never be contained in the
     haystack.

     CHECK, DOUBLE-CHECK, TIPLE-CHECK AND QUADRUPLE-CHECK THAT YOU
     NEVER ACCESS ANY CHARACTER OUT OF THE ALLOWABLE RANGE IN ANY OF
     THE TWO STRINGS!

     You will want to start by computing the lengths of the needle and
     of the haystack.
     
  */
    
    substring = 0;
    
    // compute lengths
    for(i = 0; haystack[i] != 0; i++){
        haystack_len = i + 1;
    }
    
    for(i = 0; needle[i] != 0; i++){
        needle_len = i + 1;
    }
    
    if(needle_len > haystack_len){
        substring = 0;
    }

    for(int i = 0; needle[i] != '\0'; i++){
        printf("%c", needle[i]);
        for(int j = 0; haystack[j] != '\0'; j++){
            printf("%c", haystack[j]);
            if(needle[i] - '0' == haystack[j] - '0'){
                substring = 1;
            }
        }
    }

  /* Print the answer */
  if (substring) {
    printf("\"%s\" is contained as a substring in \"%s\".\n", needle, haystack); 
  } else {
    printf("\"%s\" is not contained as a substring in \"%s\".\n", needle, haystack); 
  }
  
  return 0;
}