#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"map.h"
#include"mapGeneration.h"
#include"worldGeneration.h"


/**
 * @brief Creates a world map - Allocates all the memory for the tiles
 * 
 * @return The created worldMap
 */
worldMap_t worldMapInit(){
    worldMap_t toReturn;

    toReturn.worldArr = malloc(sizeof(mapTile_t*) * 401);

    for(int i =0; i < 401; i++){
        *(toReturn.worldArr + i) =  malloc(sizeof(mapTile_t) * 401);

        for(int j =0; j < 401; j++){
            toReturn.placedArr[i][j] = 0;
        }
    }

    return toReturn;
}

/**
 * @brief Destorys a world map - Dellocates the memory
 * 
 * @param toDestroy The world map to destroy
 */
void worldMapDestroy(worldMap_t toDestroy){
        for(int i =0; i < 401; i++){
            free((toDestroy.worldArr + i));
        }
        free(toDestroy.worldArr);  
}


int main (int argc, char** argv){
    srand(time(NULL));
    
    worldMap_t worldMap = worldMapInit();

    worldMap.worldArr[200][200] = createMapTile(worldMap,200,200);
    worldMap.placedArr[200][200] = 1;
    
    int currWorldRow = 200;
    int currWorldCol = 200;
    
    char enteredChar = 'x';
    char junk;
    int xTemp;
    int yTemp;
    while(enteredChar != 'q'){
        if(worldMap.placedArr[currWorldRow][currWorldCol] == 0){
            worldMap.worldArr[currWorldRow][currWorldCol] = createMapTile(worldMap,currWorldRow,currWorldCol);
            worldMap.placedArr[currWorldRow][currWorldCol] = 1;
        }

        printMap((*(worldMap.worldArr + currWorldRow)) + currWorldCol);
        scanf("%c",&enteredChar);
        if(enteredChar == 'f'){
            scanf(" %d %d",&xTemp,&yTemp);
        }
        scanf("%c",&junk);


        if(enteredChar == 'n'){
            currWorldRow -= 1;
        }
        else if(enteredChar == 's'){
            currWorldRow += 1;
        }
        else if(enteredChar == 'e'){
            currWorldCol += 1;
        }
        else if(enteredChar == 'w'){
            currWorldCol -= 1;
        }
        else if(enteredChar == 'f'){
            currWorldRow = xTemp;
            currWorldCol = yTemp;
        }
        else if(enteredChar == 'q'){
            printf("\nEnding Program\n");
        }
        else{
            printf("\nUnrecognized Input. Please enter n, s, e, w, f, or q.\n");
        }
    }

    worldMapDestroy(worldMap);
   

    return 0;
}