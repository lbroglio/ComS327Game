#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"biome.h"

//Colors
#define GRN "\x1B[32m"
#define RED "\x1B[31m"
#define DRKYLLW "\x1B[38;5;58m"
#define FRSTGRN "\x1B[38;5;28m"
#define BLUE "\x1B[34m"
#define DRKBLUE "\x1B[38;5;17m"
#define GREY "\x1B[38;5;235m"
#define DSRTYLLW "\x1B[38;5;220m"
#define RESET "\x1B[0m"



/**
 * @brief Holds the map tile.
 * 
 */
typedef struct mapTile{
    char mapArr[21][80];
    char mapType;
    int mountainRegion;
    int waterRegion;
    int topEntLoc;
    int bottomEntLoc;
    int leftEntLoc;
    int rightEntLoc;
}mapTile_t;


/**
 * @brief Creates a new map tile
 * 
 * @return The created map tile. It has the borders as rocks and all other spaces as X
 */
mapTile_t mapInit(char type){
    mapTile_t toReturn;
    
    toReturn.topEntLoc = (rand() % 78) +1;
    toReturn.bottomEntLoc = (rand() % 78) +1;
    toReturn.leftEntLoc = (rand() % 19) +1;
    toReturn.rightEntLoc = (rand() % 19) +1;

    for(int i = 0; i < 21; i++){
        for(int j = 0; j < 80;j ++){
            if((i == 0 && j != toReturn.topEntLoc) || (j == 0 && i != toReturn.leftEntLoc) || (i == 20 && j != toReturn.bottomEntLoc) || (j == 79 && i != toReturn.rightEntLoc)){
                toReturn.mapArr[i][j] = '%';
                
            }
            else if(i != 0 && j != 0 && i != 20 && j != 79){
                toReturn.mapArr[i][j]= 'X';
            }
            else{
                 toReturn.mapArr[i][j]= ' ';
            }
            
        }    
    }

    toReturn.mountainRegion = 0;
    toReturn.waterRegion = 0;
    toReturn.mapType = type;
    return toReturn;
}

/**
 * @brief Prints out a map to the console
 * 
 * @param map The map to print
 */
void printMap(mapTile_t* map){

    for(int i =0; i < 21; i++){
        for(int j = 0; j < 80;j ++){
            char toPrint = map->mapArr[i][j];

            if(toPrint == '.'){
                printf(GRN "%c " RESET,toPrint);
            }
            else if(toPrint == ':'){
                printf(DRKYLLW "%c " RESET,toPrint);
            }
            else if(toPrint == '~'){
                printf(BLUE "%c " RESET,toPrint);
            }
            else if(toPrint == '%'){
                printf(GREY "%c " RESET,toPrint);
            }
            else if(toPrint == '\"'){
                printf(FRSTGRN "%c " RESET,toPrint);
            }
            else if(toPrint == '*'){
                printf(DSRTYLLW "%c " RESET,toPrint);
            }
            else if(toPrint == 'C'){
                printf(RED "%c " RESET,toPrint);
            }
            else if(toPrint == 'M'){
                printf(DRKBLUE "%c " RESET,toPrint);
            }
            else{
                printf("%c ",toPrint);
            }
            
        }
        printf("\n");
    }
}

const char biomeList[5] = {'w','f','m','s','t'};

/**
 * @brief Uses random numbers to make choices for how to layout water and mountains. 
 * 0 is a normal region of the type 
 * 1 is straight line (Ranges/rivers) with the result being the width of the line. 
 * 2 differs by biome. For water it is a river of 2 width. For mountains 2 means no mountains exist
 * 
 * Choices are added to map struct.
 * 
 * @param map The map to make the choices for and to mark them on  
 */
void makeBiomeChoices(mapTile_t* map){
    //Makes choice for water
    if(map->mapType != '~'){
        map->waterRegion = rand() % 3;
    }
    else{
        map->waterRegion =0;
    }

    //Makes choice for mountains
    if(map->mapType != '%'){
        map->mountainRegion = rand() % 3;
    }
    else{
        map->mountainRegion =0;
    }
    
}

/**
 * @brief Places the starting points of biomes unto a map array. The number of each type of biome determines the type of map. 
 * This function creates a grasslands(Default) map.
 * 
 * @param map The map to place biomes on 
 * 
 * @return An array of the created biomes
 */
biome_t* placeBiomesGrassLands(mapTile_t* map,int* biomeCount){
    //Decides wheter to have lakes or rivers and mountain ranges or regions
    makeBiomeChoices(map);
    *biomeCount = 6;
    
    //Adjusts biome count to match choices
    if(map->mountainRegion == 0){
        (*biomeCount)++;
    }

    if(map->waterRegion == 0){
        (*biomeCount)++;
    }

    //Decides whether or not to include a forest
    if(rand() % 2 > 0){
        (*biomeCount)++;
    }
    
    //Creates an array to store the biomes in
    biome_t* biomeArr = malloc(sizeof(biome_t) * (*biomeCount));

    //Creates a temporary biome holder
    biome_t temp;

    //Chooses the ratio of short grass to tall grass biomes
    int numSG = (rand() % 3) + 2;
    int numTG = 6 - numSG;

   /*
    temp.cenXLoc = rand(20);
    temp.cenYLoc =  rand(21);
    */
    
    int marker =0;
    char typeHolder;
    //Places the biomes in the array and on the map

    //Decides what type of biomes to place
    for(int i=0; i < (*biomeCount); i++){
        if(i < numSG){
            typeHolder = '.';
        }
        else if(i < numTG+numSG){
            typeHolder = ':';
        }
        else{
            if(map->mountainRegion == 0 && marker == 0){
                typeHolder = '%';
                marker++;
            }
            else if(map->waterRegion == 0 && marker < 2){
                typeHolder = '~';
                marker += 2;
            }
            else{
                typeHolder = '\"';
            }
            
        }

        //Creates a biome to place
        temp = biomeInit(typeHolder,18,1,77,1);

        //Puts the biome into the arrays
        map->mapArr[temp.cenRowNum][temp.cenColNum] = temp.type;
        biomeArr[i] = temp;


    }
    
    return biomeArr;
}

/**
 * @brief Places the starting points of biomes unto a map array. The number of each type of biome determines the type of map. 
 * This function creates a special map which is dominated but a single type of non grass biome.
 * 
 * @param map The map to place biomes on 
 * 
 * @return An array of the created biomes
 */
biome_t* placeBiomesSpecial(mapTile_t* map,int* biomeCount){
    //Decides wheter to have lakes or rivers and mountain ranges or regions
    makeBiomeChoices(map);
    *biomeCount = 10;
    
    //Adjusts biome count to match choices
    if(map->mountainRegion == 0 && map->mapType != '%'){
        (*biomeCount)++;
    }


    if(map->waterRegion == 0 && map->mapType != '~'){
        (*biomeCount)++;
    }

    //Decides whether or not to include a forest
    if(rand() % 2 > 0){
        (*biomeCount)++;
    }
    
    //Creates an array to store the biomes in
    biome_t* biomeArr = malloc(sizeof(biome_t) * (*biomeCount));

    //Creates a temporary biome holder
    biome_t temp;



   /*
    temp.cenXLoc = rand(20);
    temp.cenYLoc =  rand(21);
    */
    
    int marker =0;
    char typeHolder;
    //Places the biomes in the array and on the map

    //Decides what type of biomes to place
    for(int i=0; i < (*biomeCount); i++){
        if(i < 2){
            typeHolder = '.';
        }
        else if(i <4){
            typeHolder = ':';
        }
        else if(i < 10){
            typeHolder = map->mapType;
        }
        else{
            if(map->mountainRegion == 0 && marker == 0 && map->mapType != '%'){
                typeHolder = '%';
                marker++;
            }
            else if(map->waterRegion == 0 && marker < 2 && map->mapType != '~'){
                typeHolder = '~';
                marker += 2;
            }
            else if (map->mapType != '\"'){
                typeHolder = '\"';
            }
            
        }

        //Creates a biome to place
        temp = biomeInit(typeHolder,18,1,77,1);

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
 * @param tilePlaced A tracker of if a tile was placed this expansion
 */
void expandBiome(mapTile_t* map,biome_t biome,int* tilePlaced){
    //Sets the cursors to be the right of the region
    int rowNum = biome.cenRowNum ;
    int colNum = biome.cenColNum + biome.radius;


    //Places the 1st quadrant expansion
    while((biome.cenRowNum - rowNum) != biome.radius){
        if(rowNum > 0 && rowNum < 20 && colNum > 0 && colNum < 79 && map->mapArr[rowNum][colNum] == 'X' ){
            map->mapArr[rowNum][colNum] = biome.type;
            *tilePlaced = 1;
 
        }
        rowNum -= 1;
        colNum -= 1;
     
    }

    //Sets the cursors to be the top of the region
    rowNum = biome.cenRowNum - biome.radius;
    colNum = biome.cenColNum;


    //Places the 2nd quadrant expansion
    while((biome.cenColNum - colNum) != biome.radius){
        if(rowNum > 0 && rowNum < 20 && colNum > 0 && colNum < 79 &&  map->mapArr[rowNum][colNum] == 'X' ){
            map->mapArr[rowNum][colNum] = biome.type;
            *tilePlaced = 1;
        }
        rowNum += 1;
        colNum -= 1;
     
    }

    //Sets the cursors to be the left of the region
    rowNum = biome.cenRowNum;
    colNum = biome.cenColNum - biome.radius;


    //Places the 3rd quadrant expansion
    while((rowNum - biome.cenRowNum) != biome.radius){
        if(rowNum > 0 && rowNum < 20 && colNum > 0 && colNum < 79 && map->mapArr[rowNum][colNum] == 'X' ){
            map->mapArr[rowNum][colNum] = biome.type;
            *tilePlaced = 1;
        }
        rowNum += 1;
        colNum += 1;
     
    }

    //Sets the cursors to be the bottom of the region
    rowNum = biome.cenRowNum + biome.radius;
    colNum = biome.cenColNum;


    //Places the 4th quadrant expansion
    while((colNum - biome.cenColNum) != biome.radius){
        if(rowNum > 0 && rowNum < 20 && colNum > 0 && colNum < 79 && map->mapArr[rowNum][colNum] == 'X'){
            map->mapArr[rowNum][colNum] = biome.type;
             *tilePlaced = 1;
        }
        rowNum -= 1;
        colNum += 1;
     
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
    int tilePlaced = 1;

    while(tilePlaced == 1){
        tilePlaced = 0;
        for(int i=0; i < *biomeCount; i++){
           (biomeArr + i)->radius += 1;
            expandBiome(map,*(biomeArr + i),&tilePlaced);
        }
    }

}

/**
 * @brief Adds rivers and mountain ranges to the map if neccessary.
 * 
 * @param map The map to place the ranges and rivers on
 */
void placeRiversxRanges(mapTile_t* map){
    //Place River
    if(map->waterRegion != 0){
        int placeLoc = (rand() % 78) + 1;
        for(int i=1; i<20; i++){
            //Decide if it turns
            placeLoc =placeLoc + (rand() % 3) - 1;
            map->mapArr[i][placeLoc] = '~';

            //Ends if river reaches edge of map
            if(placeLoc >= 79 || placeLoc <= 0){
                i+= 20;
            }

            //Place a second  block if the river is two wide
            if(map->waterRegion == 2){
                //Ends if river reaches edge of map
                if(placeLoc >= 78){
                    i+=20;
                }  

                map->mapArr[i][placeLoc + 1] = '~';
            }
        }
    }

    //Place Range
    if(map->mountainRegion == 1){
        int placeLoc = (rand() % 78) + 1;
        for(int i=1; i<20; i++){
            //Decide if it turns
            placeLoc =placeLoc + (rand() % 3) - 1;
            
            //Ends if range reaches edge of map
             if(placeLoc >= 79 || placeLoc <= 0){
                i+= 20;
            }

            map->mapArr[i][placeLoc] = '%';
        }
    }
}

/**
 * @brief Adds the Pokecenter and Pokemart to the map
 * 
 * @param map Map to place buildings on
 * @param biomeArr Array contianing biome locations
 */
void placeBuildings(mapTile_t* map, biome_t* biomeArr){

    //Gets locations of first biome for the building
    int rowNum = (biomeArr)->cenRowNum;
    int colNum = (biomeArr)->cenColNum;
    

    //Adds the Pokemon Center 
    map->mapArr[rowNum][colNum] = 'C';
    map->mapArr[rowNum+1][colNum] = 'C';
    map->mapArr[rowNum][colNum+1]= 'C';
    map->mapArr[rowNum+1][colNum+1]= 'C';

    //Gets the location of the second biome for the building 
    rowNum = (biomeArr + 1)->cenRowNum;
    colNum = (biomeArr + 1)->cenColNum;

    //Adds the Pokemon Center 
    map->mapArr[rowNum][colNum] = 'M';
    map->mapArr[rowNum+1][colNum] = 'M';
    map->mapArr[rowNum][colNum+1] = 'M';
    map->mapArr[rowNum+1][colNum+1] = 'M';

}




int main(int argc,char** argv){


    srand(time(NULL));

    
    mapTile_t map = mapInit('\"');
    int* biomeCount = malloc(sizeof(biomeCount));


    biome_t* biomeArr = placeBiomesSpecial(&map,biomeCount);
    generateMap(&map,biomeArr,biomeCount);
    placeRiversxRanges(&map);
    placeBuildings(&map,biomeArr);

    

    printMap(&map);
    

}