#include<stdio.h>
#include<time.h>
#include <unistd.h>
#include<string.h>
#include"./Map/map.h"
#include"./Map/biome.h"
#include"./Map/mapGeneration.h"
#include"./Data-Structures/priorityQueue.h"
#include"./Characters/gameCharacter.h"


int main(int argc, char* argv[]){
    srand(time(NULL));
    int numNPCs;

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

   
    nMapInfo_t mapInfo = spawnNPCS(map,numNPCs);

    mapInfo.playerLocation.rowNum = player.rowNum;
    mapInfo.playerLocation.colNum = player.colNum;

    
    while(1 == 1){
        char moved = moveNPC(&eventManager,&player,map,&mapInfo);

        if(moved == '@'){
            usleep(25000);
            printMapWithChars(&map,mapInfo);
        }
    }


}