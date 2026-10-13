#include <stdio.h>
#include <iostream>
#include "CheckedArray.h"

using namespace std;

int main()
{
	CheckedArray<int> arrayOfInts(25);


	try {

		for (int i = 0; i < 100; i++) 
		{
			arrayOfInts[i] = i  * 100;
		}

	}
	catch (ArrayOutOfRange& e)
	{
		cout << "WARNING! Index is out of range @ " << e.getIndex();

	}





	return 0;
}