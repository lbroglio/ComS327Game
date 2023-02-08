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
        temp = biomeInit(typeHolder,17,2,75,2);
        
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
        temp = biomeInit(typeHolder,17,2,75,2);

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
 * @brief Draws a road on the map between the two given points
 * 
 * @param map The map to draw the road on
 * @param currLoc The starting location to draw the road from. A road will be drawn here
 * @param targetLoc The end point to draw the road to
 */
void drawRoad(mapTile_t* map,point_t* currLoc, point_t targetLoc){
    //Sets -1 or 1 as the modifier depending on what direction the road needs to move in
    

    //Temporary point used for redirecting
    point_t temp;

    while(currLoc->colNum != targetLoc.colNum || currLoc->rowNum != targetLoc.rowNum){
        
        while(currLoc->colNum != targetLoc.colNum)
        {   
            int colMod = (targetLoc.colNum - currLoc->colNum) / abs(targetLoc.colNum - currLoc->colNum);
            char newChar = '#';
            //Gets the char being replaced by the road
            char repChar = map->mapArr[currLoc->rowNum][currLoc->colNum + colMod];
        
            //Checks to make sure a building isnt being replaced
            if(repChar == 'C' || repChar == 'M'){
                 
                //Redirects below the building
                if(currLoc->rowNum < 11){
                    temp.colNum = currLoc->colNum;
                    temp.rowNum = currLoc->rowNum + 2;
                    drawRoad(map,currLoc,temp);
                }
                //Redirects above the building
                else{
                    temp.colNum = currLoc->colNum;
                    temp.rowNum = currLoc->rowNum - 2;
                    drawRoad(map,currLoc,temp);
                }
            }
            else{
                //If moving over water uses a "bridge" character
                if(repChar == '~'){
                    newChar = '=';
                }  

                //Replaces the character and moves forward
                currLoc->colNum += colMod;
                map->mapArr[currLoc->rowNum][currLoc->colNum] = newChar;
                
            }
 

        }   
        while(currLoc->rowNum != targetLoc.rowNum)
        {  
            int rowMod = (targetLoc.rowNum - currLoc->rowNum) / abs(targetLoc.rowNum - currLoc->rowNum);
            char newChar = '#';
            char repChar = map->mapArr[currLoc->rowNum + rowMod][currLoc->colNum];
            //Checks to make sure a building isnt being replaced
            if(repChar == 'C' || repChar == 'M'){
                if(currLoc->colNum < 40){
                    //Redirects to the right of the building
                    temp.colNum = currLoc->colNum + 2;
                    temp.rowNum = currLoc->rowNum ;
                    drawRoad(map,currLoc,temp);
                }
                else{
                    //Redirects to the left of the building
                    temp.colNum = currLoc->colNum - 2;
                    temp.rowNum = currLoc->rowNum;
                    drawRoad(map,currLoc,temp);
                }
            }
            else{
                //If moving over water uses a "bridge" character
                if(repChar == '~'){
                    newChar = '=';
                }

                //Replaces the character and moves forward
                currLoc->rowNum += rowMod;
                map->mapArr[currLoc->rowNum][currLoc->colNum] = newChar;
                
            }
        }
    }
    
}

/**
 * @brief Adds the road network connecting the entrances and buildings to the map
 * 
 * @param map The map to add roads to
 * @param biomeArr Array of biomes on the map
 */
void addRoadSystem(mapTile_t* map,biome_t* biomeArr){
    //Intialzied points to hold location
    point_t startPoint;
    point_t endPoint;
    point_t meetPoint;

    //Randomly chooses a point for the roads to converge
    meetPoint.colNum = (rand() % 60) + 10;
    meetPoint.rowNum = (rand() % 10) + 5;


    //Draws a road from the left entrance
    startPoint.colNum = 0;
    startPoint.rowNum = map->leftEntLoc;
    drawRoad(map,&startPoint,meetPoint);

    //Draws a road from the right entrance
    startPoint.colNum = 79;
    startPoint.rowNum = map->rightEntLoc;
    drawRoad(map,&startPoint,meetPoint);


    //Draws a road to the Pokecenter
    startPoint.colNum = meetPoint.colNum;
    startPoint.rowNum = meetPoint.rowNum;

    endPoint.colNum = biomeArr->cenColNum;
    endPoint.rowNum = biomeArr->cenRowNum -1;
    drawRoad(map,&startPoint,endPoint);

    //Draws a road to the Pokemart
    startPoint.colNum = meetPoint.colNum;
    startPoint.rowNum = meetPoint.rowNum;

    endPoint.colNum = (biomeArr + 1)->cenColNum;
    endPoint.rowNum = (biomeArr + 1)->cenRowNum -1;
    drawRoad(map,&startPoint,endPoint);
    

    //Make a variable to hold row num of roads
    int locTracker = 1;

    //Draws a road from the top entrance
    startPoint.colNum = map->topEntLoc;
    startPoint.rowNum = 0;
    char toCheck = map->mapArr[startPoint.colNum][locTracker];

    while(toCheck != '#' && toCheck != '='){
        locTracker++;
        toCheck = map->mapArr[locTracker][startPoint.colNum];
    }

    endPoint.colNum = startPoint.colNum;
    endPoint.rowNum = locTracker;
    drawRoad(map,&startPoint,endPoint);

    //Draws a road from the bottom entrance
    locTracker = 79;

    startPoint.colNum = map->bottomEntLoc;
    startPoint.rowNum = 20;
    toCheck = map->mapArr[startPoint.colNum][locTracker];

    while(toCheck != '#' && toCheck != '='){
        locTracker -= 1;
        toCheck = map->mapArr[locTracker][startPoint.colNum];
    }

    endPoint.colNum = startPoint.colNum;
    endPoint.rowNum = locTracker;
    drawRoad(map,&startPoint,endPoint);


    
}

mapTile_t createMapTile(mapTile_t** worldMap, int worldRow, int worldCol){
    //Randomly chooses what type of map this is. Grasslands maps are weighted slightly higher
    char mapType;

    int typeChooser = rand() % 5;

    if(typeChooser == 2){
        mapType = '\"';
    }
    else if(typeChooser == 3){
        mapType = '%';
    }
    else if(typeChooser == 4){
        mapType = '~';
    }
    else{
         mapType = '.';
    }


    //mapTile_t* neighbor;
    int topEnt, bottomEnt, leftEnt,rightEnt;

    mapTile_t neighbor;

    

    if(worldRow == 0){
        topEnt = -1;
    }
    else{
        neighbor = worldMap[worldRow -1][worldCol];
        if(neighbor.mapType != '@'){
            topEnt = neighbor.bottomEntLoc;
        }
        else{
            topEnt = (rand() % 78) +1;
        }
    }
   
    if(worldRow  == 400){
        bottomEnt = -1;
    }
    else{
        neighbor = worldMap[worldRow + 1][worldCol];
        if(neighbor.mapType != '@'){
            bottomEnt = neighbor.topEntLoc;
        }
        else{
            bottomEnt = (rand() % 78) +1;
        }
    }

    if(worldCol == 0){
        leftEnt = -1;
    }
    else{
        neighbor = worldMap[worldRow][worldCol - 1];
        if(neighbor.mapType != '@'){
            leftEnt = neighbor.rightEntLoc;
        }
        else{
            leftEnt = (rand() % 19) +1;
        }
    }

    if(worldCol == 400){
        rightEnt = -1;
    }
    else{
        neighbor = worldMap[worldRow][worldCol + 1];
        if(neighbor.mapType != '@'){
            rightEnt = neighbor.leftEntLoc;
        }
        else{
            rightEnt = (rand() % 19) +1;
        }
    }

    //Creates a struct to hold the map
    //mapTile_t* map = malloc(sizeof(mapTile_t));
    mapTile_t map = mapTileInit(mapType,topEnt,bottomEnt,leftEnt,rightEnt);

    //Creates a variable to store the number of biomes
    int* biomeCount = malloc(sizeof(biomeCount));


    //Randomly generates the biomes of this  map depending on type
    biome_t* biomeArr;
    if(mapType == '.'){
        biomeArr = placeBiomesGrassLands(&map,biomeCount);
    }
    else{
        biomeArr = placeBiomesSpecial(&map,biomeCount);
    }

    generateMap(&map,biomeArr,biomeCount);
    //Places other necessary items
    placeRiversxRanges(&map);

    int manDist = abs(200 - worldRow) + abs(200 - worldCol);
    int spawnChance = (((-45.0 * manDist)/200.0) + 50);
    int spawnNum = (rand() % 100) + 1;

    if(spawnNum < spawnChance || (worldRow == 200 && worldCol == 200)){
        placeBuildings(&map,biomeArr);
    }
    
    addRoadSystem(&map,biomeArr);
    
    
    free(biomeCount);
    free(biomeArr);

    return map;

}
