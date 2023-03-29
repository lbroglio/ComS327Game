#include<curses.h>
#include"../Characters/gameCharacter.h"

void trainerBattle(GameCharacter enemyTrainer,mapTile_t* map){
    //Defeat Trainer
    map->mapInfo.defTrainers[map->mapInfo.numDef] = enemyTrainer.getID();
    map->mapInfo.numDef += 1;

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

void trainerBattle(int trainerID,mapTile_t* map){
    //Defeat Trainer
    map->mapInfo.defTrainers[map->mapInfo.numDef] = trainerID;
    map->mapInfo.numDef += 1;

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