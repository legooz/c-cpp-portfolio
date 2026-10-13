#pragma once

class Prisoner 
{

private:
    int prisonerNum;
    Prisoner* nextPrisoner;

public:
    Prisoner();
    Prisoner(int x);
    Prisoner* createCircle(int prisonersAmount);
    int generateGame(int prisonersAmount, int wordsAmount);
};