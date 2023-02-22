#include<stdio.h>
#include<time.h>
#include<string.h>
#include"./Map/map.h"
#include"./Map/biome.h"
#include"./Map/mapGeneration.h"
#include"./Data-Structures/priorityQueue.h"
#include"./Characters/gameCharacter.h"


int main(int argc, char* argv[]){
    srand(time(NULL));
    int hikerDist[21][80];
    int rivalDist[21][80];
    
    mapTile_t map = createMapTileIndependent();
    
    character_t player;
    player.colNum = ((map.biomeArr) + 1)->cenColNum;
    player.rowNum = ((map.biomeArr) + 1)->cenRowNum -1;
    map.mapArr[player.rowNum][player.colNum] = '@';

    dijkstraPathfindHiker(map,player,hikerDist);
    dijkstraPathfindRival(map,player,rivalDist);

    printMap(&map);
    printf("\n Hiker:\n");
    printDistArr(hikerDist);
    printf("\n Rival:\n");
    printDistArr(rivalDist);


}