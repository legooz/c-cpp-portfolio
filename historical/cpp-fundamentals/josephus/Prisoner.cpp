#include "Prisoner.h"
#include <iostream>

using namespace std;


Prisoner::Prisoner(int x)
{

    prisonerNum = x;
	nextPrisoner = nullptr;

}

Prisoner* Prisoner::createCircle(int prisonersAmount) {

    Prisoner* firstPrisoner = new Prisoner(1);
    Prisoner* previousPrisoner = firstPrisoner;


    for (int i = 2; i <= prisonersAmount; i++) {
        Prisoner* currentPrisoner = new Prisoner(i);
        previousPrisoner->nextPrisoner = currentPrisoner;
        previousPrisoner = currentPrisoner;
    }


    previousPrisoner->nextPrisoner = firstPrisoner;
    
    
    return firstPrisoner;
}


int Prisoner::generateGame(int prisonersAmount, int wordAmount) {
    
    Prisoner* firstPrisoner = createCircle(prisonersAmount);
    Prisoner* previousPrisoner = firstPrisoner;
    Prisoner* currentPrisoner = firstPrisoner;
    Prisoner* exePrisoner = firstPrisoner;

    for (int i = 0; i < prisonersAmount - 1; i++) {

        for (int j = 0; j < wordAmount - 1; j++) {

            previousPrisoner = currentPrisoner;
            
            currentPrisoner = currentPrisoner->nextPrisoner;

        }

        exePrisoner = currentPrisoner;

        
        previousPrisoner->nextPrisoner = currentPrisoner->nextPrisoner;
        
        
        currentPrisoner = previousPrisoner->nextPrisoner;

    }

    delete exePrisoner;

    return currentPrisoner->prisonerNum;

}