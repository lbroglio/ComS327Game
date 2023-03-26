#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<curses.h>
#include"./Screen/screen.h"
#include"./Map/map.h"
#include"./Map/biome.h"
#include"./Map/mapGeneration.h"
#include"./Data-Structures/priorityQueue.h"
#include"./Characters/gameCharacter.h"
#include"./Characters/playerMovement.h"


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

    GameCharacter player = GameCharacter(playerSpawn,'@',0,'#');
    eventManager.addWithPriority(&player,1);

   
    NPCMapInfo mapInfo = spawnNPCS(map,numNPCs,&eventManager);
    mapInfo.charLocations[player.rowNum][player.colNum] = player;

    mapInfo.playerLocation.rowNum = -1;
    mapInfo.playerLocation.colNum = -1;
    int exitCom = 0;

    while(exitCom == 0){
        //Remove the NPC which moves this turn from the queue
        int time; 
        IDable* temp = (eventManager.extractMinWithPri(&time));
        GameCharacter toMove = dynamic_cast<GameCharacter&>(*temp);
        free(temp);

        int moveCost;

        if(toMove.type == '@'){
            //Player Movement
            printMapWithChars(&map, mapInfo);
            moveCost = playerTurn(&toMove,map,&mapInfo);
            player = toMove;
        }
        else{
            moveCost = moveNPC(&toMove,time,&player,map,&mapInfo);
        }
        if(moveCost == -1){
            exitCom = 1;
        }


        if(moveCost != -2){
            //Readd the character to the queue
            eventManager.addWithPriority(&toMove,moveCost + time);
        }


    }
    //npcMapInfoDestroy(mapInfo);
    endwin();

}