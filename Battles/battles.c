#include<curses.h>
#include"../Characters/gameCharacter.h"

void trainerBattle(character_t enemyTrainer,nMapInfo_t* mapInfo){
    //Defeat Trainer
    mapInfo->defTrainers[mapInfo->numDef] = enemyTrainer.id;
    mapInfo->numDef += 1;

    //Display Message
    move(0,0);
    clrtoeol();

    printw("You are in a trainer battle. Press esc to exit");
    char action;

    while(action != 27){
        action =  getch();
    }
}