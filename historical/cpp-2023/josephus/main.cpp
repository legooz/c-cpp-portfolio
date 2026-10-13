#include <stdio.h>
#include <iostream>
#include <string>
#include "Prisoner.h"
using namespace std;


int main()
{
	
	
	int numOfPrisoners = 0;
	cout << "Enter amount of Prisoners you would like : " << endl;
	cin >> numOfPrisoners;
	
	int amountWords = 0;
	cout << "How many words are in the rhyme?" << endl;
	cin >> amountWords;

	Prisoner createCircle(numOfPrisoners);
	int lastAlive = createCircle.generateGame(numOfPrisoners, amountWords);
	cout << "With " << numOfPrisoners << " prisoners and " << amountWords << " words, I'd like to be number " << lastAlive << "." << endl;

	return 0;	
}
