#include<curses.h>
#include"../Characters/gameCharacter.h"
#include"../Screen/screen.h"

void trainerBattle(GameCharacter player, GameCharacter enemyTrainer,mapTile_t* map){
    //Defeat Trainer
    map->mapInfo.defTrainers[map->mapInfo.numDef] = enemyTrainer.getID();
    map->mapInfo.numDef += 1;

    //Display Message
    setInterfaceScreen();
    attron(COLOR_PAIR(COLOR_SOFT_BLACK));
    mvprintw(3,5,"You are in a trainer battle. Press esc to exit");
    mvprintw(5,5,"Your Pokemon: ");

    int i;

    std::vector<Pokemon> pokeList = player.getHeldPokemon();
    int numPoke = pokeList.size();
    int pokeTracker =0;

    for(i =6; pokeTracker < numPoke; i++){
        std::string toPrint = " " + pokeList[pokeTracker].getDisplayString();
        mvprintw(i,5,toPrint.c_str());
        pokeTracker++;
    }

    mvprintw(i+2,5,"Opponent's Pokemon: ");

    pokeList = enemyTrainer.getHeldPokemon();
    numPoke = pokeList.size();
    pokeTracker =0;

    for(i = i + 3; pokeTracker < numPoke; i++){
        std::string toPrint = " " + pokeList[pokeTracker].getDisplayString();
        mvprintw(i,5,toPrint.c_str());
        pokeTracker++;
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