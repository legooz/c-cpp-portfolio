
#include <stdio.h>

int main(int argc, char **argv) {
  const int BUF_LEN = 128;
  char str[BUF_LEN];
  int i;
  char c;
  int is_binary;
  int d, n;

  /* Get the user to enter a string */
  printf("Please enter a string made of 0s and 1s, finishing the entry by pressing Enter.\n");
  for (i=0; i<BUF_LEN-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    str[i] = c;
  } 
  str[i] = '\0';

  /* Check if the user string contains nothing but 0s and 1s */
  is_binary = 1;

  /* TODO */
  int biLength = 0;
    for(i = 0; str[i] != '\0'; i++){
        biLength++;
        if(str[i] != '0' && str[i] != '1'){
            is_binary = 0;
            
        }
    }
  
  /* Proceed only of the string contains only 0s and 1s */
  if (is_binary) {
    /* Convert the string of 0s and 1s to an integer number n */
    n = 0;

    /* TODO */
    

    
    
    for(i = 0; str[i] != '\0'; i++){
        if(str[i] == '0'){
            d = 0;
        } else {
            d = 1;
        }
        n = n * 10 + d;
    }
    
    int r = 0;
    int b = 1;
    int f = 0;
    
    while (n > 0) {  
        r = n % 10;
        f = f + r * b;  
        n = n / 10; 
        b = b * 2;  
    }  
    
    n = f;

    printf("The binary number %s is %d in decimal.\n", str, n);
  } else {
    printf("The string you entered, \"%s\", contains characters other than 0 and 1.\n", str);
  }

  return 0;
}