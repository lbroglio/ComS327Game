#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"map.h"
#include"mapGeneration.h"


/**
 * @brief Wrapper struct for the array holding all the tiles in the world map
 * 
 */
typedef struct worldMap{
    mapTile_t** worldArr;
}worldMap_t;

/**
 * @brief Creates a world map - Allocates all the memory for the tiles
 * 
 * @return The created worldMap
 */
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

    worldMap.worldArr[200][200] = createMapTile(worldMap.worldArr,200,200);
    
    int currWorldRow = 200;
    int currWorldCol = 200;
    
    char enteredChar = 'x';

    while(enteredChar != 'q'){
        if(worldMap.worldArr[currWorldRow][currWorldCol].mapType == '@'){
            worldMap.worldArr[currWorldRow][currWorldCol] = createMapTile(worldMap.worldArr,currWorldRow,currWorldCol);
        }

        printMap((*(worldMap.worldArr + currWorldRow)) + currWorldCol);
        fflush(stdin);
        scanf("%c",&enteredChar);


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