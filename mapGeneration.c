#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"biome.h"
#include"map.h"



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

    //Adds the Pokemart 
    map->mapArr[rowNum][colNum] = 'M';
    map->mapArr[rowNum+1][colNum] = 'M';
    map->mapArr[rowNum][colNum+1] = 'M';
    map->mapArr[rowNum+1][colNum+1] = 'M';

}


/**
 * @brief Detects if an undesirable biome can be avoided by a road
 * 
 * @param map The map to check on
 * @param searchLoc The point where the road hit the undesired biome
 * @param searchVert Boolean used to determine the direction of travel. 1 means to check a way around vertically 0 horizontally
 * 
 * @return 0 if the biome can't be avoided. The squares to move if it can't (Negative means move up/left positve means move down/right) 
 */
int avoidBiome(mapTile_t* map, point_t searchLoc, int searchVert){
    //How far away from the starting location to check
    int offset =  0;
    //Stores the distance for each possible direction to go to avoid the obstacle
    int dist1 = 0;
    int dist2 = 0;
    //Stores the current character being checked
    char toCheck;

    if(map->mapArr[searchLoc.rowNum][searchLoc.colNum] == '~' && map->waterRegion == ){

    }
    

    //Look by moving vertically
    if(searchVert ==  1){
        //Searches out until both have found a way around or none is found
        while((dist1 == 0 || dist2 == 0) && offset < 21){
            //Makes sure the check isnt outside the array and this direction hasn't already been found
            if((searchLoc.rowNum - offset) > 0 && dist1 == 0){
                //Checks if the spot is a prefered biome
                toCheck = map->mapArr[searchLoc.rowNum - offset][searchLoc.colNum];
                if(toCheck != '~' & toCheck != '%'){
                    dist1 = offset * -1;
                }
            }

            //Makes sure the check isnt outside the array and this direction hasn't already been found
            if((searchLoc.rowNum + offset) < 20 && dist2 == 0){
                toCheck = map->mapArr[searchLoc.rowNum + offset][searchLoc.colNum];
                 //Checks if the spot is a prefered biome
                if(toCheck != '~' & toCheck != '%'){
                    dist2 = offset;
                }
            }
        }
       
    }
    //Look by moving horizontally
    else{
        //Searches out until both have found a way around or none is found
        while((dist1 == 0 || dist2 == 0) && offset < 21){
            //Makes sure the check isnt outside the array and this direction hasn't already been found
            if((searchLoc.colNum - offset) > 0){
                //Checks if the spot is a prefered biome
                toCheck = map->mapArr[searchLoc.rowNum][searchLoc.colNum - offset];
                if(toCheck != '~' & toCheck != '%'){
                    dist1 = offset * -1;
                }
            }

            //Makes sure the check isnt outside the array and this direction hasn't already been found
            if((searchLoc.colNum + offset) < 79){
                //Checks if the spot is a prefered biome
                toCheck = map->mapArr[searchLoc.rowNum ][searchLoc.colNum + offset];
                if(toCheck != '~' & toCheck != '%'){
                    dist1 = offset;
                }
            }
        }
       
    }

    //Returns the smaller distance 
    if(dist1 < dist2 && dist1 != 0){
        return dist1;
    }
    else{
        return dist2;
    }
}


/**
 * @brief Draws a road on the map between two given points
 * Will recursively call to break it into two straight lines of movement avoid undesired biomes and buildings 
 * 
 * @param map The map to draw the road on
 * @param biomeArr List of biomes on the map
 * @param currLoc The location to start drawing the road from. A road will not be placed here
 * @param endPoint The desired point to reach on the map 
 */
void drawRoad(mapTile_t* map, biome_t* biomeArr, point_t* currLoc, point_t endPoint){
    point_t temp;
    if(currLoc->colNum != endPoint.colNum && currLoc->rowNum != endPoint.rowNum){
        temp.rowNum = endPoint.rowNum;
        temp.colNum =  currLoc -> rowNum;
        drawRoad(map,biomeArr,currLoc,temp);

        temp.rowNum = currLoc->rowNum;
        temp.colNum =  endPoint.colNum;
        drawRoad(map,biomeArr,currLoc,temp);
    }
    else if(currLoc-> colNum != endPoint.colNum){
        while(currLoc->colNum != endPoint.colNum){
            char nextChar = map->mapArr[currLoc->rowNum][currLoc->colNum];
            if(nextChar == '~' || nextChar == '%'){
                temp.rowNum = currLoc->rowNum;
                temp.colNum = currLoc->colNum+1;

                avoidBiome(map,*currLoc,0);
            }
        }
    }

}

int main(int argc,char** argv){


    srand(time(NULL));

    
    mapTile_t map = mapInit('.');
    int* biomeCount = malloc(sizeof(biomeCount));


    biome_t* biomeArr = placeBiomesGrassLands(&map,biomeCount);
    generateMap(&map,biomeArr,biomeCount);
    placeRiversxRanges(&map);
    //placeRoadsExits(&map);
    placeBuildings(&map,biomeArr);
    

    

    printMap(&map);
    

}