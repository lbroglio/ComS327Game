#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"biome.h"

/**
 * @brief Holds the map tile.
 * 
 */
typedef struct mapTile{
    char mapArr[21][80];
}mapTile_t;


/**
 * @brief Creates a new map tile
 * 
 * @return The created map tile. It has the borders as rocks and all other spaces as X
 */
mapTile_t mapInit(){
    mapTile_t toReturn;
    
    for(int i = 0; i < 22; i++){
        for(int j = 0; j < 81;j ++){
            if(i == 0 || j == 0 || i == 21 || j == 80){
                toReturn.mapArr[i][j] = '%';
            }
            else{
                toReturn.mapArr[i][j]= 'X';
            }
            
        }    
    }
    return toReturn;
}

/**
 * @brief Prints out a map to the console
 * 
 * @param map The map to print
 */
void printMap(mapTile_t* map){

    for(int i =0; i<21; i++){
        for(int j = 0; j < 80;j ++){
            char toPrint = map->mapArr[i][j];
            printf("%c ",toPrint);
        }
        printf("\n");
    }
}

const char biomeList[5] = {'w','f','m','s','t'};

/**
 * @brief Uses random numbers to make choices for how to layout water and mountains. 
 * 1-2 is straight line (Ranges/rivers) with the result being the width of the line
 * 0 is a normal region of the type 
 * 
 * @return int* 
 */
int* makeBiomeChoices(){
    int* biomeChoiceArr = malloc(sizeof(biomeChoiceArr) * 2);

    *biomeChoiceArr = rand() % 2;
    *(biomeChoiceArr+1) = rand() % 2;

    return biomeChoiceArr;
}

/**
 * @brief Creates a grass lands type map
 * 
 * @param map The map to generate on 
 * 
 * @return An array of the created biomes
 */
biome_t* placeBiomesGrassLands(mapTile_t* map,int* biomeCount){
    //Decides wheter to have lakes or rivers and mountain ranges or regions
    int* biomeChoiceArr = makeBiomeChoices();
    *biomeCount = 4;
    
    //Adjusts biome count to match choices
    if(*(biomeChoiceArr) > 0){
        (*biomeCount)++;
    }

    if(*(biomeChoiceArr+1) > 0){
        (*biomeCount)++;
    }

    //Decides whether or not to include a forest
    if(rand() % 1 > 0){
        (*biomeCount)++;
    }
    
    //Creates an array to store the biomes in
    biome_t* biomeArr = malloc(sizeof(biomeArr) * (*biomeCount));
    //Creates a temporary biome holder
    biome_t temp;

    //Chooses the ratio of short grass to tall grass biomes
    int numSG = (rand() % 2) + 2;
    int numTG = 6 - numSG;

   /*
    temp.cenXLoc = rand(20);
    temp.cenYLoc =  rand(21);
    */
    
    int marker =0;
    char typeHolder;
    //Places the biomes in the array and on the map

    //Decides what type of biomes to place
    for(int i=0; i < *biomeCount; i++){
        if(i < numSG){
            typeHolder = '.';
        }
        else if(i < numTG+numSG){
            typeHolder = ':';
        }
        else if(i >= (numTG+numSG)){
            if(*(biomeChoiceArr) == 0 && marker == 0){
                typeHolder = '%';
                marker++;
            }
            else if(*(biomeChoiceArr) == 0 && marker < 2){
                typeHolder = '~';
                marker += 2;
            }
            else{
                typeHolder = '\"';
            }
        }

        //Creates a biome to place
        temp =  biomeInit(typeHolder,19,1,78,1);

        //Puts the biome into the arrays
        map->mapArr[temp.cenRowNum][temp.cenColNum] = temp.type;
        biomeArr[i] = temp;


    }

    return biomeArr;
}

/**
 * @brief Expands a biome increasing its radius by one
 * 
 * @param map The map to expands the biome on
 * @param biome The information on the biome to expand
 */
void expandBiome(mapTile_t* map,biome_t biome){
    //Sets the cursors to be the right of the region
    int rowNum = biome.cenRowNum ;
    int colNum = biome.cenColNum + biome.radius;


    //Places the 1st quadrant expansion
    while((biome.cenRowNum - rowNum) != biome.radius){
        if(map->mapArr[rowNum][colNum] == 'X' && colNum > 0 && rowNum > 0){
            map->mapArr[rowNum][colNum] = biome.type;
 
        }
        rowNum -= 1;
        colNum -= 1;
     
    }

    //Sets the cursors to be the top of the region
    rowNum = biome.cenRowNum - biome.radius;
    colNum = biome.cenColNum;


    //Places the 2nd quadrant expansion
    while((biome.cenColNum - colNum) != biome.radius){
        if(map->mapArr[rowNum][colNum] == 'X' && rowNum < 21 && colNum > 0){
            map->mapArr[rowNum][colNum] = biome.type;

        }
        rowNum += 1;
        colNum -= 1;
     
    }

    //Sets the cursors to be the left of the region



    //Places the 3rd quadrant expansion
    while((rowNum - biome.cenRowNum) != biome.radius){
        if(map->mapArr[rowNum][colNum] == 'X' && rowNum < 21 && colNum < 80){
            map->mapArr[rowNum][colNum] = biome.type;
          
        }
        rowNum += 1;
        colNum += 1;
     
    }

    //Sets the cursors to be the bottom of the region
    rowNum = biome.cenRowNum;
    colNum = biome.cenColNum - biome.radius;


    //Places the 4th quadrant expansion
    while((colNum - biome.cenColNum) != biome.radius){
        if(map->mapArr[rowNum][colNum] == 'X' && rowNum > 0 && colNum < 80){
            map->mapArr[rowNum][colNum] = biome.type;
            rowNum -= 1;
            colNum += 1;
        }
     
    }
    
}

/**
 * @brief Takes in a map with biomes placed on it. Expands the biomes to cover the entire map
 * 
 * @param map The map to generate
 * @param biomeArr An array of the biomes on the map
 * @param biomeCount The number of biomes
 */
void generateMap(mapTile_t* map, biome_t* biomeArr, int* biomeCount){
    int tilesPlaced = 0;

    while(tilesPlaced != 1580){
        for(int i=0; i < *biomeCount; i++){
           (biomeArr + i)->radius += 1;
            expandBiome(map,*(biomeArr + i));
        }
    }

}



int main(int argc,char argv[]){
    srand(time(NULL));

    mapTile_t* map = malloc(sizeof(map));
    int* biomeCount = malloc(sizeof(biomeCount));

    biome_t* biomeArr = placeBiomesGrassLands(map,biomeCount);
    generateMap(map,biomeArr,biomeCount);


}