#include <iostream>
using namespace std;


void numOfCoins(int changeToDispense, int &Quarters, int &Dimes, int &Nickles, int &Pennies)
{
	int NewChange = changeToDispense;

	if (NewChange >= 25)
	{
		Quarters = NewChange / 25;
		NewChange -= Quarters * 25;
	}

	if (NewChange >= 10)
	{
		Dimes = NewChange / 10;
		NewChange -= Dimes * 10;
	}

	if (NewChange >= 5)
	{
		Nickles = NewChange / 5;
		NewChange -= Nickles * 5;
	}

	Pennies = NewChange;
	
}

void resetCoins(int changeToDispense, int& Quarters, int& Dimes, int& Nickles, int& Pennies)
{
	changeToDispense = 0;
	Quarters = 0;
	Dimes = 0;
	Nickles = 0;
	Pennies = 0;
}

int main()
{
	int changeToDispense = 0;
	int Quarters = 0;
	int Dimes = 0;
	int Nickles = 0;
	int Pennies = 0;





	changeToDispense = 58;
	numOfCoins(changeToDispense, Quarters, Dimes, Nickles, Pennies);
	cout << "Test Case 1 : " << endl;
	cout << "Change to dispense : " << changeToDispense << " cents." << endl;
	cout << "Amount of Quarters: " << Quarters << endl;
	cout << "Amount of Dimes: " << Dimes << endl;
	cout << "Amount of Nickles: " << Nickles << endl;
	cout << "Amount of Pennies: " << Pennies << endl;
	cout << changeToDispense << " was entered and the change dispensed adds up to "
		<< Quarters * 25 + Dimes * 10 + Nickles * 5 + Pennies << endl;

	resetCoins(changeToDispense, Quarters, Dimes, Nickles, Pennies);


	changeToDispense = 9;
	numOfCoins(changeToDispense, Quarters, Dimes, Nickles, Pennies);
	cout << "Test Case 2 : " << endl;
	cout << "Change to dispense : " << changeToDispense << " cents." << endl;
	cout << "Amount of Quarters: " << Quarters << endl;
	cout << "Amount of Dimes: " << Dimes << endl;
	cout << "Amount of Nickles: " << Nickles << endl;
	cout << "Amount of Pennies: " << Pennies << endl;
	cout << changeToDispense << " was entered and the change dispensed adds up to "
		<< Quarters * 25 + Dimes * 10 + Nickles * 5 + Pennies << endl;

	resetCoins(changeToDispense, Quarters, Dimes, Nickles, Pennies);


	cout << "Try it yourself. Enter an integer 1 - 99 to represent change $" << endl;

	cin >> changeToDispense;

	while (changeToDispense > 99 || changeToDispense < 1)
	{
		cout << "Try it yourself. Enter an integer 1 - 99 to represent change $" << endl;

		cin >> changeToDispense;
	}

	numOfCoins(changeToDispense, Quarters, Dimes, Nickles, Pennies);

	cout << "Change to dispense : " << changeToDispense << " cents." << endl;
	cout << "Amount of Quarters: " << Quarters << endl;
	cout << "Amount of Dimes: " << Dimes << endl;
	cout << "Amount of Nickles: " << Nickles << endl;
	cout << "Amount of Pennies: " << Pennies << endl;
	cout << changeToDispense << " was entered and the change dispensed adds up to "
		<< Quarters * 25 + Dimes * 10 + Nickles * 5 + Pennies << endl;


	resetCoins(changeToDispense, Quarters, Dimes, Nickles, Pennies);




	return 0;
}