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
biome_t* placeBiomesGrassLands(mapTile_t* map){
    //Decides wheter to have lakes or rivers and mountain ranges or regions
    int* biomeChoiceArr = makeBiomeChoices();
    int biomeCount = 4;
    
    //Adjusts biome count to match choices
    if(*(biomeChoiceArr) > 0){
        biomeCount++;
    }

    if(*(biomeChoiceArr+1) > 0){
        biomeCount++;
    }

    //Decides whether or not to include a forest
    if(rand() % 1 > 0){
        biomeCount++;
    }
    
    //Creates an array to store the biomes in
    biome_t* biomeArr = malloc(sizeof(biomeArr) * biomeCount);
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


void generateMap(mapTile_t* map){
    

}


int main(int argc,char argv[]){
    srand(time(NULL));



}