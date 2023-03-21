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
    queue_t eventManager;
    queueInit(&eventManager,numNPCs + 1, sizeof(character_t),getCharacterId);

    mapTile_t map = createMapTileIndependent();

    point_t  playerSpawn;
    playerSpawn.colNum = ((map.biomeArr) + 1)->cenColNum;
    playerSpawn.rowNum = ((map.biomeArr) + 1)->cenRowNum -1;

    character_t player = characterInit(playerSpawn,'@',0,'#');
    void* addV = malloc(sizeof(character_t));
    memcpy(addV,&player,sizeof(character_t));
    queueAddWithPriority(&eventManager,addV,1);
    free(addV);

   
    nMapInfo_t mapInfo = spawnNPCS(map,numNPCs,&eventManager);
    mapInfo.charLocations[player.rowNum][player.colNum] = '@';

    mapInfo.playerLocation.rowNum = -1;
    mapInfo.playerLocation.colNum = -1;
    int exitCom = 0;

    while(exitCom == 0){
        //Remove the NPC which moves this turn from the queue
        int time; 
        void* temp = (queueExtractMinWithPri(&eventManager,&time));
        character_t* toMove = ((character_t*) temp); 
        int moveCost;

        if(toMove->type == '@'){
            //Player Movement
        }
        else{
            moveCost = moveNPC(toMove,time,&player,map,&mapInfo);
        }


        //Readd the character to the queue
        memcpy(temp,toMove,sizeof(character_t));
        queueAddWithPriority(&eventManager, temp,moveCost + time);
        free(temp);


    }


}