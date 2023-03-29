#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<curses.h>
#include<iostream>

#include"./Screen/screen.h"
#include"./Map/map.h"
#include"./Map/biome.h"
#include"./Map/mapGeneration.h"
#include"./Data-Structures/priorityQueue.h"
#include"./Characters/gameCharacter.h"
#include"./Characters/playerMovement.h"
#include"./Characters/NPCMapInfo.h"


int main(int argc, char* argv[]){
    srand(time(NULL));
    int numNPCs;
    terminalInit();


    if(argc == 2){
        numNPCs = atoi(argv[1]);
    }
    else{
        numNPCs = (rand() %  4) + 9;
    }
    Queue eventManager = Queue(numNPCs + 1);

    mapTile_t map = createMapTileIndependent();




    Point playerSpawn;
    playerSpawn.colNum = ((map.biomeArr) + 1)->cenColNum;
    playerSpawn.rowNum = ((map.biomeArr) + 1)->cenRowNum -1;

    Player player = Player(playerSpawn);
    eventManager.addWithPriority(&player,1);



    map.mapInfo = spawnNPCS(map,numNPCs,&eventManager);
    map.mapInfo.charLocations[player.getRowNum()][player.getColNum()] = player;

    map.mapInfo.playerLocation.rowNum = -1;
    map.mapInfo.playerLocation.colNum = -1;
    int exitCom = 0;


    while(exitCom == 0){
        //printMapWithChars(&map,map.mapInfo);
        //Remove the NPC which moves this turn from the queue
        int time; 
        IDable* temp = (eventManager.extractMinWithPri(&time));
        GameCharacter* toMove = dynamic_cast<GameCharacter*>(temp);

        int moveCost;
        moveCost = moveGameChar(toMove,time,&player,&map);
        
        if(toMove->type == '@'){
            player = *(dynamic_cast<Player*>(toMove));
        }

        if(moveCost == -1){
            exitCom = 1;
        }

        if(moveCost != -2){
            //Readd the character to the queue
            eventManager.addWithPriority(toMove,moveCost + time);
        }

        delete temp;
    }
    //npcMapInfoDestroy(mapInfo);
    endwin();

}