/******************************************
* CSCE A201
* Lars Goozen
* Assignment 1
* Problem 2
* 9 - 8 - 2022
* Description: This program determines the binary numbers of a decimal number.
******************************************/
#include <stdio.h>

int main(){
	int i = 0;
	int firstBinary = 0; //starts from left
	int secBinary = 0;
	int thrBinary = 0;
	int forthBinary = 0;

	//Cycle numbers 0 - 15
	for(i = 0; i <= 15; i++){
		int tempNum = i;
		firstBinary = 0; //starts from left
		secBinary = 0;
		thrBinary = 0;
		forthBinary = 0;

		while(tempNum >= 8){
			firstBinary = 1;
			tempNum = tempNum - 8;
		}

		while(tempNum >= 4){
			secBinary = 1;
			tempNum = tempNum - 4;
		}

		while(tempNum >= 2){
			thrBinary = 1;
			tempNum = tempNum - 2;
		}
		while(tempNum == 1){
			forthBinary = 1;
			tempNum = tempNum - 1;
		}

		printf("%d ", i);
		printf("%d %d %d %d\n", firstBinary, secBinary, thrBinary, forthBinary);
	}


	return 0;
}
