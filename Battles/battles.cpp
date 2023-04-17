#include<curses.h>
#include"../Characters/gameCharacter.h"
#include"../Screen/screen.h"

void trainerBattle(GameCharacter* player, GameCharacter enemyTrainer,mapTile_t* map){
    //Defeat Trainer
    map->mapInfo.defTrainers[map->mapInfo.numDef] = enemyTrainer.getID();
    map->mapInfo.numDef += 1;

    //Get the starting  Pokemon for each
    Pokemon playerPoke = player->usePokemon();
    Pokemon trainerPoke = enemyTrainer.usePokemon();

    //Display Message
    setInterfaceScreen();
    attron(COLOR_PAIR(COLOR_SOFT_BLACK));
    mvprintw(3,5,"You are in a trainer battle!");

    mvprintw(5,5,"Your Pokemon: %s", playerPoke.getDisplayString().c_str());
    mvprintw(7,5,"Opponent Pokemon: %s", trainerPoke.getDisplayString().c_str());


    int turnIndicator = 0;

    if(playerPoke.getSpeed() < trainerPoke.getSpeed()){
        turnIndicator += 1;
    }

    if(turnIndicator % 2 == 0){
        
    }
    else{

    }



    
    char action;

    while(action != 27){
        action =  getch();
    }

    //Clear Message
    endInterfaceScreen(map);

}

/*
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
*/