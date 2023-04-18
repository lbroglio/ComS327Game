#include<curses.h>
#include"../Characters/gameCharacter.h"
#include"../Screen/screen.h"


typedef enum {
    FIGHT,
    BAG,
    RUN,
    POKEMON
}battleMove_t;


int getTypeModifer(std::string attackType, std::string defendType){
    return 0;
}


void playerFight(Pokemon* playerPoke){

}

void fight(Pokemon* attacker, Pokemon* defender, Move attackUsed){
    int hitNum = rand() % 100;

    if(hitNum < attackUsed.accuracy()){
        //float crit = rand() % 100 < 6 ? 1.5 : 1;
        
    }
}


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
    mvprintw(3,5,"You are in a pokemon battle!");

    mvprintw(5,5,"Your Pokemon: %s", playerPoke.getDisplayString().c_str());
    mvprintw(6,5,"Opponent Pokemon: %s", trainerPoke.getDisplayString().c_str());


    int turnIndicator = 0;


    if(playerPoke.getSpeed() < trainerPoke.getSpeed()){
        turnIndicator += 1;
    }

    int battleResolved = 0;
    while(battleResolved == 0){
        if(turnIndicator % 2 == 0){
            int chosenMove = playerBattleInterface();
            switch (chosenMove)
            {
            case FIGHT:
                //IMPLEMENT ACTION LOGIC
                mvprintw(8,5,"Your x used x and dealt x damage to opponent x. Press any key to advance");
                clearInterfaceSection(8,1);
                getch();
                turnIndicator++;
                break;
            case BAG:
                //IMPLEMENT ACTION LOGIC
                mvprintw(8,5,"Your x used x on your x. Press any key to advance");
                clearInterfaceSection(8,1);
                getch();
                turnIndicator++;
                break;
            case RUN:
                mvprintw(8,5,"You cannot run from a trainer battle.");
                clearInterfaceSection(8,1);
                break;
            case POKEMON:
                //IMPLEMENT ACTION LOGIC
                mvprintw(8,5,"Your swapped in x. Press any key to advance");
                clearInterfaceSection(8,1);
                getch();
                turnIndicator++;
                break;
            }
        }
        else{
            mvprintw(8,5,"Opp turn. Press any key to advance");
            getch();
            clearInterfaceSection(8,1);
            turnIndicator++;
        }

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