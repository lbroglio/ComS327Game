#include<curses.h>
#include"../Characters/gameCharacter.h"

void trainerBattle(GameCharacter enemyTrainer,mapTile_t* map){
    //Defeat Trainer
    map->mapInfo->defTrainers[mapInfo->numDef] = enemyTrainer.id;
    map->mapInfo->numDef += 1;

    //Display Message
    move(0,0);
    clrtoeol();
    printw("You are in a trainer battle. Press esc to exit");

    char action;

    while(action != 27){
        action =  getch();
    }

    //Clear Message
    move(0,0);
    clrtoeol();
    refresh();

}