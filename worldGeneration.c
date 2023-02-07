#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"map.h"
#include"mapGeneration.h"



typedef struct worldMap{
    mapTile_t** worldArr;
}worldMap_t;

worldMap_t worldMapInit(){
    worldMap_t toReturn;
    mapTile_t placeHolder;
    placeHolder.mapType = '@';

    toReturn.worldArr = malloc(sizeof(mapTile_t*) * 401);

    for(int i =0; i < 401; i++){
        *(toReturn.worldArr + i) =  malloc(sizeof(mapTile_t) * 401);

        for(int j =0; j < 401; j++){
            toReturn.worldArr[i][j] =  placeHolder;
        }
    }

    return toReturn;
}

void worldMapDestroy(worldMap_t toDestroy){
        for(int i =0; i < 401; i++){
            free((toDestroy.worldArr + i));
        }
        free(toDestroy.worldArr);  
}

int main (int argc, char** argv){
    srand(time(NULL));
    
    worldMap_t worldMap = worldMapInit();

    worldMap.worldArr[200][200] = createMapTile(worldMap.worldArr,200,200);

    /*
    int currWorldRow = 200;
    int currWorldCol = 200;
    */

    printMap((*(worldMap.worldArr + 200)) + 200);

    return 0;
}