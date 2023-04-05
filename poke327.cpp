#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<curses.h>
#include<iostream>
#include"./Screen/screen.h"
#include"./Map/map.h"
#include"./Map/biome.h"
#include"./Map/worldGeneration.h"
#include"./Map/mapGeneration.h"
#include"./Data-Structures/priorityQueue.h"
#include"./Characters/gameCharacter.h"
#include"./Characters/playerMovement.h"
#include"./Characters/NPCMapInfo.h"
#include"./PokemonData/PokemonData.h"

//Declare World Map as Global
 WorldMap worldMap = WorldMap();

int main(int argc, char* argv[]){
    //If the user didn't give a command line argument
    if(argc == 1){
        throw "No Command line argument supplied";
    }

    //Prints the correct array based on command line arg
    if(argv[1] == std::string("pokemon")){
        //Prints the pokemon array
        printDataVector(worldMap.pokeData->pokemon,1092);
    }
    else if(argv[1] == std::string("moves")){
        //Prints the moves array
        printDataVector(worldMap.pokeData->moves,844);
    }
    else if(argv[1] == std::string("pokemon_moves")){
        //Prints the pokemon_moves array
        printDataVector(worldMap.pokeData->pokemon_moves,528238);
    }
    else if(argv[1] == std::string("pokemon_species")){
        //Prints the pokemon_species array
        printDataVector(worldMap.pokeData->pokemon_species,898);
    }
    else if(argv[1] == std::string("experience")){
        //Prints the experience array
        printDataVector(worldMap.pokeData->experience,601);
    }
    else if(argv[1] == std::string("type_names")){
        //Prints the type _names array
        printDataVector(worldMap.pokeData->type_names,19);
    }
    else if(argv[1] == std::string("pokemon_stats")){
        //Prints the pokemon_stats array
        printDataVector(worldMap.pokeData->pokemon_stats,6552);
    }
    else if(argv[1] == std::string("stats")){
        //Prints the stats array
        printDataVector(worldMap.pokeData->stats,8);
    }
    else if(argv[1] == std::string("pokemon_types")){
        //Prints the pokemon_types array
        printDataVector(worldMap.pokeData->pokemon_types,1675);
    }
    else if(argv[1] == std::string("all")){
        //Prints the pokemon array
        printDataVector(worldMap.pokeData->pokemon,1092);
        //Prints the moves array
        printDataVector(worldMap.pokeData->moves,844);
        //Prints the pokemon_moves array
        printDataVector(worldMap.pokeData->pokemon_moves,528238);
        //Prints the pokemon_species array
        printDataVector(worldMap.pokeData->pokemon_species,898);
        //Prints the experience array
        printDataVector(worldMap.pokeData->experience,601);
        //Prints the type _names array
        printDataVector(worldMap.pokeData->type_names,19);
        //Prints the pokemon_stats array
        printDataVector(worldMap.pokeData->pokemon_stats,6552);
        //Prints the stats array
        printDataVector(worldMap.pokeData->stats,8);
        //Prints the pokemon_types array
        printDataVector(worldMap.pokeData->pokemon_types,1675);
    }
    else{
        throw "Invalid command line argument";
    }
    
    
    
    return 0;
    //Program ends before reaching here for the purposes of assigment 1.07
    int numNPCs;
    terminalInit();

    int currWorldRow = 200;
    int currWorldCol = 200;

    mapTile_t* map = (*(worldMap.worldArr + currWorldRow)) + currWorldCol;


    if(argc == 2){
        numNPCs = atoi(argv[1]);
    }
    else{
        numNPCs = (rand() %  4) + 9;
    }

    map->eventManager = new Queue(numNPCs + 1);
    map->eventManager->addWithPriority(worldMap.player,1);

    map->mapInfo = spawnNPCS(map,numNPCs);
    map->mapInfo.charLocations[worldMap.player->getRowNum()][worldMap.player->getColNum()] = *worldMap.player;

    map->mapInfo.playerLocation.rowNum = -1;
    map->mapInfo.playerLocation.colNum = -1;


    int exitCom = 0;
    while(exitCom == 0){
        //printMapWithChars(&map,map.mapInfo);
        //Remove the NPC which moves this turn from the queue
        int time; 
        IDable* temp = (map->eventManager->extractMinWithPri(&time));
        GameCharacter* toMove = dynamic_cast<GameCharacter*>(temp);
        


        int moveCost;
        moveCost = moveGameChar(toMove,time,worldMap.player,map);
        
        if(toMove->type == '@'){
            *worldMap.player = *(dynamic_cast<Player*>(toMove));
        }

        if(moveCost == -1){
            exitCom = 1;
        }
        else if(moveCost == -3){
            map->savedTime = time;
            map->mapInfo.charLocations[worldMap.player->getRowNum()][worldMap.player->getColNum()] = GameCharacter();

            if(worldMap.player->getRowNum() == 0){
                currWorldRow -= 1;
                worldMap.player->setRowNum(19);
                worldMap.player->setColNum(map->topEntLoc);
            }
            else if(worldMap.player->getRowNum() == 20){
                currWorldRow += 1;
                worldMap.player->setRowNum(1);
                worldMap.player->setColNum(map->bottomEntLoc);               
            }
            else if(worldMap.player->getColNum() == 0){
                currWorldCol -= 1;
                worldMap.player->setRowNum(map->leftEntLoc);
                worldMap.player->setColNum(78);    
            }
            else if(worldMap.player->getColNum() == 79){
                currWorldCol += 1;;
                worldMap.player->setRowNum(map->rightEntLoc);
                worldMap.player->setColNum(1);   
            }

            if(worldMap.placedArr[currWorldRow][currWorldCol] == 0){
                worldMap.worldArr[currWorldRow][currWorldCol] = createMapTile(&worldMap,currWorldRow,currWorldCol);
                worldMap.placedArr[currWorldRow][currWorldCol] = 1;
                map = (*(worldMap.worldArr + currWorldRow)) + currWorldCol;

                map->eventManager = new Queue(numNPCs + 1);
                map->eventManager->addWithPriority(worldMap.player,1);
                

                map->mapInfo = spawnNPCS(map,numNPCs);
                map->mapInfo.charLocations[worldMap.player->getRowNum()][worldMap.player->getColNum()] = *worldMap.player;

                map->mapInfo.playerLocation.rowNum = -1;
                map->mapInfo.playerLocation.colNum = -1;
            }
            else{
                map = (*(worldMap.worldArr + currWorldRow)) + currWorldCol;
                map->eventManager->addWithPriority(worldMap.player,map->savedTime);
            }


        }
        else if(moveCost == -4){
            
            map->savedTime = time;
            map->mapInfo.charLocations[map->mapInfo.playerLocation.rowNum][map->mapInfo.playerLocation.colNum] = GameCharacter();
            
            currWorldRow = worldMap.player->getRowNum();
            currWorldCol = worldMap.player->getColNum();

            if(worldMap.placedArr[currWorldRow][currWorldCol] == 0){
                worldMap.worldArr[currWorldRow][currWorldCol] = createMapTile(&worldMap,currWorldRow,currWorldCol);
                worldMap.placedArr[currWorldRow][currWorldCol] = 1;
                map = (*(worldMap.worldArr + currWorldRow)) + currWorldCol;


                worldMap.player->setRowNum(((map->biomeArr) + 1)->cenRowNum -1);
                worldMap.player->setColNum(((map->biomeArr) + 1)->cenColNum);   

                map->eventManager = new Queue(numNPCs + 1);
                map->eventManager->addWithPriority(worldMap.player,1);
                

                map->mapInfo = spawnNPCS(map,numNPCs);
                map->mapInfo.charLocations[worldMap.player->getRowNum()][worldMap.player->getColNum()] = *worldMap.player;

                map->mapInfo.playerLocation.rowNum = -1;
                map->mapInfo.playerLocation.colNum = -1;
            }
            else{
                worldMap.player->setRowNum(((map->biomeArr) + 1)->cenRowNum -1);
                worldMap.player->setColNum(((map->biomeArr) + 1)->cenColNum); 

                map = (*(worldMap.worldArr + currWorldRow)) + currWorldCol;
                map->eventManager->addWithPriority(worldMap.player,map->savedTime);
            }
        }   
        else if(moveCost != -2){
            //Readd the character to the queue
            map->eventManager->addWithPriority(toMove,moveCost + time);
            //delete temp;
        }

      
    }
    //npcMapInfoDestroy(mapInfo);
    //delete map->eventManager;
    endwin();

}