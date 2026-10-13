
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

  /* Historical substring-search attempt. The nested loops detect any shared
     character, not a contiguous substring. Empty inputs also leave length
     variables uninitialized. This incomplete behavior is preserved. */
    
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