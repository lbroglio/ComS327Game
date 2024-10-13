#include<curses.h>
#include<climits>
#include"../Characters/gameCharacter.h"
#include"../Screen/screen.h"
#include"../PokemonData/PokemonData.h"
#include"../Characters/playerMovement.h"



typedef enum {
    FIGHT,
    BAG,
    RUN,
    POKEMON
}battleMove_t;


/**
 * @brief Calculates what the damage modfier should be based on the type of the moves used vs. the types of the defending pokemon
 * 
 * @param attackTypeID 
 * @param defendingPokemon 
 * @return The calculated type modifier 
 */
float getTypeModifer(int attackTypeID, Pokemon defendingPokemon){
    float typeMod = 1;
    std::vector<int> dTypes = defendingPokemon.getTypeIDs();
    int dataSize = dTypes.size();

    for(int i=0; i < dataSize; i++){
        typeMod *= pokeData->typeModGraph[attackTypeID - 1][dTypes[i] - 1];
    }

    return typeMod;
}


/**
 * @brief Calculates and performs the damage for a fight move (attack made by a pokemon)
 * 
 * @param attacker Pointer to the attacking pokemon
 * @param defender Pointer to the defending pokemon
 * @param attackUsed What attack the attacker is using
 * @param turnIndicator Int even if its the players turn odd if its the enemies
 * @return Indicator for whether or not the defender fainted. 1 if it has fainted. 0 if it hasn't
 */
int fight(Pokemon* attacker, Pokemon* defender, Move attackUsed, int turnIndicator){
    int hitNum = rand() % 100;

    if(hitNum < attackUsed.accuracy()){
        float crit = rand() % 100 < 6 ? 1.5 : 1;
        float typeMod = getTypeModifer(attackUsed.type_id(), *defender);
        float stab = 1;

        int numTypes = attacker->getTypeIDs().size();
        if(attacker->getTypeIDs()[0] == attackUsed.type_id() ){
            stab = 1.5;
        }
        else if(numTypes == 2){
            if(attacker->getTypeIDs()[1] == attackUsed.type_id()){
                stab =  1.5;
            }
        }

        float  power;

        if(attackUsed.power() == INT_MAX){
            power = 20;
        }
        else{
            power = static_cast<float>(attackUsed.power());
        }

        float random = (rand() % 5) + 3;
        float levelCalc = ((2 * attacker->getLevel()) / 5.0) + 2;
        float numerator = levelCalc * power * (static_cast<float>(attacker->getattack()) / static_cast<float>(defender->getDefense()));

        //mvprintw(0,0,"CRIT: %f, TYPEMOD: %f, STAB: %f, RANDOM: %f, NUMERATOR: %f, POWER %d",crit,typeMod,stab,random,numerator,attackUsed.power());
        
        int damageDealt = static_cast<int>(((numerator / 50 ) + 2) * crit * random * typeMod * stab);

        int faintI = defender->damage(damageDealt);

        if(turnIndicator % 2 == 0){
            mvprintw(8,5,"Your %s used %s and dealt %d damage to opponent %s. Press any key to advance", attacker->getName().c_str(),attackUsed.identifier().c_str(),damageDealt,defender->getName().c_str());
        }
       else{
            mvprintw(8,5,"Opponent's %s used %s and dealt %d damage to your %s. Press any key to advance", attacker->getName().c_str(),attackUsed.identifier().c_str(),damageDealt,defender->getName().c_str());
        }
        
        if(typeMod > 1){
            mvprintw(9,5, "It's super effective!");
        }
        else if(typeMod < 1){
            mvprintw(9,5, "It's not  very effective!");
        }

       if(faintI == 1){
            mvprintw(10,5,"%s fainted.",defender->getName().c_str());
       }

       return faintI;
    }

    if(turnIndicator % 2 == 0){
        mvprintw(8,5,"Your %s used %s. It missed. Press any key to advance", attacker->getName().c_str(),attackUsed.identifier().c_str());
    }
    else{
        mvprintw(8,5,"Opponent's %s used %s. It missed. Press any key to advance", attacker->getName().c_str(),attackUsed.identifier().c_str());
    }
    
    return 0;


}

/**
 * @brief Handles the interface and diaplay for the player when they choose fight on there turn
 * 
 * @param playerPoke The player's pokemom
 * @param opponentPoke The opponent's pokemon
 * @return The indicator for if the defender fainted 1 if it did 0 if it didn't. 
 */
int playerFight(Pokemon* playerPoke,Pokemon* opponentPoke){

    mvprintw(10,6,"Use spacebar to choose what move your pokemon will take.");
    
    std::vector<Move> moves = playerPoke->getMoves();
    int numMoves = moves.size();

    for(int i = 0; i < numMoves; i++){
        mvprintw(11+i,7,"Move: %s, Type: %s",moves[i].identifier().c_str(),pokeData->typeNameMap[moves[i].type_id()].c_str());
    }

    int actionSelected = 0;
    int i =0;
    while(actionSelected == 0){
        mvprintw(11+i,5,"*");
        //Wait for player input
        int action = getch();
        
        mvprintw(11+i,5," ");

        if(action == KEY_UP && i > 0){
            i -= 1;
        }
        else if(action == KEY_DOWN && i < numMoves - 1){
            i += 1;
        }
        else if(action == ' '){
            actionSelected = 1;
        }
        
    }

    clearInterfaceSection(10,5);
    return fight(playerPoke,opponentPoke,moves[i],0);
}


void trainerBattle(Player* player, GameCharacter enemyTrainer,mapTile_t* map){
    //Get the starting  Pokemon for each
    Pokemon playerPoke = player->usePokemon();
    Pokemon trainerPoke = enemyTrainer.usePokemon();
    int totalXP = 0;



    //Display Message
    setInterfaceScreen();
    attron(COLOR_PAIR(COLOR_SOFT_BLACK));
   


    int turnIndicator = 0;


    if(playerPoke.getSpeed() < trainerPoke.getSpeed()){
        turnIndicator += 1;
    }

    int battleResolved = 0;
    while(battleResolved == 0){
        mvprintw(3,5,"You are in a pokemon battle!");
        mvprintw(5,5,"Your Pokemon: %s", playerPoke.getDisplayString().c_str());
        mvprintw(6,5,"Opponent Pokemon: %s", trainerPoke.getDisplayString().c_str());
        int faintIndicator = 0;
        if(turnIndicator % 2 == 0){
            int chosenMove = playerBattleInterface();
            switch (chosenMove)
            {
            case FIGHT:
                faintIndicator = playerFight(&playerPoke,&trainerPoke);
                getch();
                clearInterfaceSection(8,3);
                turnIndicator++;
                break;
            case BAG:{
                player->addPokemon(playerPoke);
                int itemUsed = inventoryInterface(player);

                if(itemUsed == 1){
                    mvprintw(8,5,"You cannot use a pokeball during a trainer battle.");
                }
                else if(itemUsed != -1){
                    getch();
                    clearInterfaceSection(8,1);
                }
                else{
                    
                }

                playerPoke = player->usePokemon(player->getHeldPokemon().size() - 1);
                break;
            }
            case RUN:
                mvprintw(8,5,"You cannot run from a trainer battle. Press any key to advance");
                getch();
                turnIndicator++;
                clearInterfaceSection(8,1);
                break;
            case POKEMON:{
                int swapped = pokemonInterface(player);
                if(swapped != -1){
                    clearInterfaceSection(8,1);
                    getch();
                    turnIndicator++;

                    player->addPokemon(playerPoke);

                    playerPoke = player->usePokemon(swapped);
                }
                break;
            }
            }
        }
        else{
            int numMoves = trainerPoke.getMoves().size();
            int randMove = rand() % numMoves; 
            faintIndicator = fight(&trainerPoke,&playerPoke,trainerPoke.getMoves()[randMove],turnIndicator);
            getch();
            clearInterfaceSection(8,3);
            turnIndicator++;
        }

        if(faintIndicator == 1){
            if(turnIndicator % 2 == 0){
                player->addPokemon(playerPoke);
                int viablePokemon = 0;

                int numPoke = player->getHeldPokemon().size();
                for(int i = 0; i < numPoke; i++){
                    if(player->getHeldPokemon()[i].pokemonFainted() == 0){
                        viablePokemon += 1;
                    }
                }
               
                if(viablePokemon > 0){
                    mvprintw(8,5, "Your %s fainted", playerPoke.getName().c_str());
                    int swapped = -1;
                    while(swapped == -1){
                        swapped = pokemonInterface(player);
                    }
                   playerPoke = player->usePokemon(swapped);
                }
                else{
                    battleResolved = 2;
                }
            }
            else{
                totalXP += trainerPoke.getLevel() * 5;

                enemyTrainer.addPokemon(trainerPoke);
                trainerPoke = enemyTrainer.usePokemon();

                if(trainerPoke.getName() == "invalid"){
                    battleResolved = 1;
                }
            }
            turnIndicator++;
        }



    }
    
    //Clear Message
    endInterfaceScreen(map);

    if(battleResolved == 2){
        player->defeat();
    }
    else{
        //Defeat Trainer
        map->mapInfo.defTrainers[map->mapInfo.numDef] = enemyTrainer.getID();
        map->mapInfo.numDef += 1;

        player->addPokemon(playerPoke);

        //Distribute the earned xp between the player's team
        int numPoke = player->getHeldPokemon().size();
        
        for(int i = 0; i < numPoke; i++){
            Pokemon tmp = player->usePokemon();

            int levelFlag = tmp.addXP(totalXP / numPoke);
            player->addPokemon(tmp);

            if(levelFlag == 1){
                clear();
                mvprintw(8,5,"Your %s leveled up. Press any key to advance",tmp.getName().c_str());
                getch();
            }

        }
    }

}

void wildBattle(Player* player, Pokemon encounteredPokemon,mapTile_t* map){
    //Get the starting  Pokemon for each
    Pokemon playerPoke = player->usePokemon();


    //Display Message
    setInterfaceScreen();
    attron(COLOR_PAIR(COLOR_SOFT_BLACK));
   


    int turnIndicator = 0;


    if(playerPoke.getSpeed() < encounteredPokemon.getSpeed()){
        turnIndicator += 1;
    }

    int battleResolved = 0;
    while(battleResolved == 0){
        mvprintw(3,5,"You are in a pokemon battle!");
        mvprintw(5,5,"Your Pokemon: %s", playerPoke.getDisplayString().c_str());
        mvprintw(6,5,"Opponent Pokemon: %s", encounteredPokemon.getDisplayString().c_str());
        int faintIndicator = 0;
        if(turnIndicator % 2 == 0){
            int chosenMove = playerBattleInterface();
            switch (chosenMove)
            {
            case FIGHT:
                faintIndicator = playerFight(&playerPoke,&encounteredPokemon);
                getch();
                clearInterfaceSection(8,3);
                turnIndicator++;
                break;
            case BAG:{
                player->addPokemon(playerPoke);
                int itemUsed = inventoryInterface(player);
                int numPoke = player->getHeldPokemon().size();

                if(itemUsed == 1 && numPoke < 6){
                    player->addPokemon(encounteredPokemon);
                    mvprintw(8,5,"You caught a wild %s. Press any key to continue",encounteredPokemon.getName().c_str());
                    getch();
                    battleResolved = 1; 
                    player->usePokeball();
                }
                else if(itemUsed == 1){
                    mvprintw(8,5,"The wild %s escaped. Press any key to continue",encounteredPokemon.getName().c_str());
                    getch();
                    playerPoke = player->usePokemon(player->getHeldPokemon().size() - 1);
                    player->usePokeball();
                }
                else if(itemUsed != -1){
                    getch();
                    clearInterfaceSection(8,1);
                    turnIndicator++;
                    playerPoke = player->usePokemon(player->getHeldPokemon().size() - 1);
                    
                }
                else{
                    playerPoke = player->usePokemon(player->getHeldPokemon().size() - 1);
                }
                break;
            }
            case RUN:{
                int randSelect = rand() % 10;

                if(randSelect < 4){
                    mvprintw(8,5,"You got away. Press any key to advance");
                    battleResolved = 1;
                }
                else{
                    mvprintw(8,5,"You could not get away. Press any key to advance");
                    turnIndicator++;
                }
                getch();
                clearInterfaceSection(8,1);
                break;
            }
            case POKEMON:{
                int swapped = pokemonInterface(player);
                if(swapped != -1){
                    clearInterfaceSection(8,1);
                    getch();
                    turnIndicator++;

                    player->addPokemon(playerPoke);

                    playerPoke = player->usePokemon(swapped);
                }
                break;
            }
            }
        }
        else{
            int numMoves = encounteredPokemon.getMoves().size();
            int randMove = rand() % numMoves; 
            faintIndicator = fight(&encounteredPokemon,&playerPoke,encounteredPokemon.getMoves()[randMove],turnIndicator);
            getch();
            clearInterfaceSection(8,3);
            turnIndicator++;
        }

        if(faintIndicator == 1){
            if(turnIndicator % 2 == 0){
                player->addPokemon(playerPoke);
                int viablePokemon = 0;

                int numPoke = player->getHeldPokemon().size();
                for(int i = 0; i < numPoke; i++){
                    if(player->getHeldPokemon()[i].pokemonFainted() == 0){
                        viablePokemon += 1;
                    }
                }
               
                if(viablePokemon > 0){
                    mvprintw(8,5, "Your %s fainted", playerPoke.getName().c_str());
                    int swapped = -1;
                    while(swapped == -1){
                        swapped = pokemonInterface(player);
                    }
                   playerPoke = player->usePokemon(swapped);
                }
                else{
                    battleResolved = 2;
                }
            }
            else{
                battleResolved = 1;
            }
            turnIndicator++;
        }



    }
    
    //Clear Message
    endInterfaceScreen(map);

    if(battleResolved == 2){
        player->defeat();
    }
    else{
        player->addPokemon(playerPoke);
        int totalXP = encounteredPokemon.getLevel() * 5;
        int numPoke = player->getHeldPokemon().size();

        for(int i = 0; i < numPoke; i++){
            Pokemon tmp = player->usePokemon();

            int levelFlag = tmp.addXP(totalXP / numPoke);
            player->addPokemon(tmp);

            if(levelFlag == 1){
                clear();
                mvprintw(8,5,"Your %s leveled up. Press any key to advance",tmp.getName().c_str());
                getch();
            }
        }
    }
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