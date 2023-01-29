#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"biome.h"

/**
 * @brief Holds the map tile.
 * 
 */
typedef struct mapTile{
    char mapArr[80][21];
}mapTile_t;



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
    for(int i=0; i<biomeCount; i++){
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
        temp =  biomeInit(typeHolder,78,1,19,1);

        //Puts the biome into the arrays
        map->mapArr[temp.cenXLoc][temp.cenYLoc] = temp.type;
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
    int xLoc = biome.cenXLoc + biome.radius;
    int yLoc = biome.cenXLoc;


    //Places the 1st quadrant expansion
    while(xLoc != biome.radius){
        if(map->mapArr[xLoc][yLoc] == "X" && xLoc > 0 && yLoc < 21){
            map->mapArr[xLoc][yLoc] = biome.type;
            xLoc -= 1;
            yLoc -= 1;
        }
     
    }

    //Sets the cursors to be the right of the region
    int xLoc = biome.cenXLoc + biome.radius;
    int yLoc = biome.cenXLoc;


    //Places the 2nd quadrant expansion
    while(xLoc != biome.radius){
        if(map->mapArr[xLoc][yLoc] == "X" && xLoc > 0 && yLoc < 21){
            map->mapArr[xLoc][yLoc] = biome.type;
            xLoc -= 1;
            yLoc -= 1;
        }
     
    }

    //Sets the cursors to be the top of the region
    int xLoc = biome.cenXLoc;
    int yLoc = biome.cenXLoc - biome.radius;


    //Places the 3rd quadrant expansion
    while(xLoc != biome.radius){
        if(map->mapArr[xLoc][yLoc] == "X" && xLoc > 0 && yLoc < 21){
            map->mapArr[xLoc][yLoc] = biome.type;
            xLoc += 1;
            yLoc += 1;
        }
     
    }

    //Sets the cursors to be the left of the region
    int xLoc = biome.cenXLoc;
    int yLoc = biome.cenXLoc + biome.radius;


    //Places the 4th quadrant expansion
    while(xLoc != biome.radius){
        if(map->mapArr[xLoc][yLoc] == "X" && xLoc > 0 && yLoc < 21){
            map->mapArr[xLoc][yLoc] = biome.type;
            xLoc += 1;
            yLoc -= 1;
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