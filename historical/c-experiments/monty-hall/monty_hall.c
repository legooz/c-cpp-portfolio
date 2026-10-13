/******************************************************************************
* Monty Hall Simulation
* 9-8-2022
* 
* Purpose: Finding the probability of winning a game show based on the options given.
* 
* Answer: Always switch doors. Statistically based on vaiable change, when one of the non-grand-prize winning door is shown
* it completely changes the probability of the choices. The probability of the 1st door chosen was 1/3 to get it correct.
* After the reveal, it changes the probability. The first choice was a 33% chance of being correct. However, after the reveal
* two doors remain. Your first choice (33.33% correct) or the option to switch. After the game show host reveals
* one of the non-grand-prize winning doors the variable change creates a 2/3 probability of the door not chosen by the player.
* It may seem like it should be a 50/50 chance when two doors are remaining, but it is not, because the sequence of 
* choices and the probability of the first pick. The revealed doors probability is basically added into 
* the option-to-switch door creating a 66.67% chance of winning. The classic Monty Hall Scenario.
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main()
{
    int userCorrectChoice = 0;
    int userCorrectChoiceSwitch = 0;
    int randDoorshow = 0;
    int randCashdoor = 0;
    int userPickdoor = 0;
    int randDoorswitch = 0;
    srand ( time(NULL) );
   
    //stay choice loop
    for(int i = 0; i < 1000; i++){
        
    randCashdoor = (rand() % 3) + 1;  

    userPickdoor = (rand() % 3) + 1;
    
    randDoorshow = (rand() % 3) + 1;
    
    //printf("randCashdoor : %d userPickdoor : %d randDoorswitch : %d\n", randCashdoor, userPickdoor, randDoorswitch);
    
    while(userPickdoor != randDoorshow && randDoorshow != randCashdoor){
        randDoorshow = (rand() % 3) + 1;
    } 
    
    //printf("Behind door %d is a box of rice-a-roni.\n(((Stay))) with your first pick door %d? \nor switch to remaining door?\n", randDoorswitch, userPickdoor);
    
    if(userPickdoor == randCashdoor){
        userCorrectChoice++;
    }
        //printf("randCashdoor : %d userPickdoor : %d randDoorswitch : %d\n", randCashdoor, userPickdoor, randDoorswitch);
        //printf("Staying with first door total correct: %d\n", userCorrectChoice);
    }
    
    
    /*
    * Switch choice loop
    * Switch choice loop
    */

    for(int i = 0; i < 1000; i++){
    
        randCashdoor = (rand() % 3) + 1; 
            
        userPickdoor = (rand() % 3) + 1;
        
        randDoorshow = (rand() % 3) + 1;
        
        randDoorswitch = (rand() % 3) + 1;
        
        //switch door choice 
        //printf("Chose door : %d\n", userPickdoor);
        
        while(randDoorshow ==  userPickdoor || randDoorshow == randCashdoor){
            randDoorshow = (rand() % 3) + 1;
        } 
        //printf("Show door : %d\n", randDoorshow);
        
        while(randDoorswitch == randDoorshow || randDoorswitch == userPickdoor){
            randDoorswitch = (rand() % 3) + 1;
        }
        //printf("Switch door : %d answer : %d\n", randDoorswitch, randCashdoor);
        
        if(randDoorswitch == randCashdoor){
            userCorrectChoiceSwitch++;
        }
           // printf("randCashdoor : %d userPickdoor : %d randDoorswitch : %d\n", randCashdoor, userPickdoor, randDoorswitch);
    }
    
    printf("Staying with first choice amount correct: %d out of 1000\n", userCorrectChoice);
    printf("Switching from first choice amount correct: %d out of 1000\n", userCorrectChoiceSwitch);
        
    
    
    
    return 0;
}
