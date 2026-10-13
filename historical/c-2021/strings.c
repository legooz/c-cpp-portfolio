
/* In this whole file, no call to any function 
   
   in string.h nor ctypes.h may be made.

   NO strlen, strchr, strrchr, etc.

*/

#include <stdio.h>

/* Returns the length of the string str */
int string_len(char str[]) {
    int x = 0;
    for(int i = 0; str[i] != '\0'; i++){
        x++;
    }
    
  return x; // TODO: STUB
}


/* Returns a boolean indicating if str is a palindrome.

   If str is a palindrome, returns a non-zero value, typically 1.
   
   If str is not a palindrome, returns zero.

   A string is a palindrome if it reads the 
   same forwards and backwards.

   Calls string_len().

   May not use any temporary array or string.

*/
int string_is_palindrome(char str[]) {
    int x = 1;
    int j = string_len(str) - 1;
    for(int i = 0; i < string_len(str) / 2; i++){
        if(str[i] != str[j]){
            x = 0;
        }
        j--;
    }
    
  return x; 
}


/* Returns the first index (from the left) where the
   character c figures in the string str.

   If the character c does not figure in str, returns -1.

   Does not call any other function.

*/
int string_character_index(char str[], char c) {
    for(int i = 0; str[i] != '\0'; i++){
        if(c == str[i]){
            return i;
        }
    }
   return -1; // TODO: STUB
}


/* Returns the last index (first from the right) where the
   character c figures in the string str.

   If the character c does not figure in str, returns -1.

   Calls string_len().
*/
int string_character_index_reverse(char str[], char c) {
    for(int i = string_len(str) - 1; i != 0; i--){
        if(c == str[i]){
            return i;
        }
    }
   return -1; // TODO: STUB
}


/* Returns a boolean indicating if strings str1 and str2 have
   characters in common.

   If one of the characters of str2 is found in str1, returns a
   non-zero value, typically 1.

   Otherwise, if none of the characters of str2 can be found in str1, 
   returns zero.

   Calls string_character_index() for each of the characters in str2.

*/
int string_common_characters(char str1[], char str2[]) {
    for(int i = 0; str1[i] != '\0'; i++){
        for(int j = 0; str2[j] != '\0'; j++){
            if(str1[i] == str2[j]){
                return 1;
            }
        }
    }
  return 0; 
}


/* Returns a boolean indicating if the string str contains
   at least one upper-case letter.

   If the string str contains at least one upper-case letter in the
   English alphabet ('A' through 'Z'), returns a non-zero value,
   typically 1.

   Otherwise, returns zero.

   Does not call any other function.
   
*/
int string_contains_uppercase(char str[]) {
    for(int i = 0; str[i] != 0; i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            return 1;
        }
    }
   return 0; // TODO: STUB
}


/* Returns a boolean indicating if the string str contains
   at least one lower-case letter.

   If the string str contains at least one lower-case letter in the
   English alphabet ('a' through 'z'), returns a non-zero value,
   typically 1.

   Otherwise, returns zero.

   Does not call any other function.
   
*/
int string_contains_lowercase(char str[]) {
    for(int i = 0; str[i] != 0; i++){
        if(str[i] >= 'a' && str[i] <= 'z'){
            return 1;
        }
    }
  return 0; // TODO: STUB
}


/* Returns a boolean indicating if the string str contains
   at least one digit.

   If the string str contains at least one digit ('0' through '9'),
   returns a non-zero value, typically 1.

   Otherwise, returns zero.

   Does not call any other function.
   
*/
int string_contains_digit(char str[]) {
    for(int i = 0; str[i] != 0; i++){
        if(str[i] >= '0' && str[i] <= '9'){
            return 1;
        }
    }
   return 0; // TODO: STUB
}


/* Returns a boolean indicating if the string str is a valid password.

   A password is valid if it contains 

   * at least one upper-case character and
   * at least one lower-case character and
   * at least one digit and
   * at least one special character.

   A special character is one of the characters

   '+', '=', '-', '*', '/', '%', '^', '&', '~', '#', '{', '[', '|',
   '\\', '@', ']', '$', '!', ':', ';', ',', ',', '.', '<', '>', '(' or
   ')'.

   Calls the functions string_contains_uppercase(),
   string_contains_lowercase(), string_contains_digit() and 
   string_common_characters().

   FYI: The instructor's solution is 7 lines long, including the
   function's declaration header and final closing curly brace.

*/
int string_is_valid_password(char str[]) {
    if(string_contains_lowercase(str) && string_contains_digit(str) && string_common_characters(str,"'+', '=', '-', '*', '/', '%', '^', '&', '~', '#', '{', '[', '|', '\\', '@', ']', '$', '!', ':', ';', ',', ',', '.', '<', '>', '(' ')'")){
        return 1;
    }
   return 0; // TODO: STUB
 }


/* A main() to test the functions defined above.

   No modification is needed here.

*/
int main(int argc, char **argv) {
  const int BUF_LEN = 128;
  char str[BUF_LEN];
  char c;
  int i;

  /* Get the user to enter a string */
  printf("Please enter a string, finishing the entry by pressing Enter.\n");
  for (i=0; i<BUF_LEN-1; i++) {
    scanf("%c", &c);
    if (c == '\n') {
      break;
    }
    str[i] = c;
  } 
  str[i] = '\0';

  /* Get the user to enter a character */
  printf("Please enter a character: ");
  do {
    scanf("%c", &c);
  } while (c == '\0');

  /* Print the string and the character */
  printf("The string you entered is \"%s\" and the character you entered is \'%c\'.\n", str, c);
  
  /* Exercise the functions above */
  printf("The length of the string \"%s\" is %d.\n", str, string_len(str));
  printf("The string \"%s\" is a palindrome: %s.\n", str, ((string_is_palindrome(str)) ? "yes" : "no"));
  printf("The character \'%c\' can be found in the string \"%s\" the first time (first from the left) at index %d.\n", c, str, string_character_index(str, c));
  printf("The character \'%c\' can be found in the string \"%s\" the last time  (first from the right) at index %d.\n", c, str, string_character_index_reverse(str, c));
  printf("The string \"%s\" and the string \"Hello world\" have common characters: %s.\n", str, ((string_common_characters(str, "Hello world")) ? "yes" : "no"));
  printf("The string \"%s\" contains upper-case letters: %s.\n", str, ((string_contains_uppercase(str)) ? "yes" : "no"));
  printf("The string \"%s\" contains lower-case letters: %s.\n", str, ((string_contains_lowercase(str)) ? "yes" : "no"));
  printf("The string \"%s\" contains digits: %s.\n", str, ((string_contains_digit(str)) ? "yes" : "no"));
  printf("The string \"%s\" is a valid password: %s.\n", str, ((string_is_valid_password(str)) ? "yes" : "no"));
  
  return 0;
}