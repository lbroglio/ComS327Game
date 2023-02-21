#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"biome.h"
#include"map.h"
#include"../Data-Structures/priorityQueue.h"
#include"worldGeneration.h"



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
 * @param biomeCount Memory address to set with the number of biomes
 * 
 */
void placeBiomesGrassLands(mapTile_t* map,int* biomeCount){
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
    map->biomeArr = malloc(sizeof(biome_t) * (*biomeCount));

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
        map->biomeArr[i] = temp;


    }
    
}

/**
 * @brief Places the starting points of biomes unto a map array. The number of each type of biome determines the type of map. 
 * This function creates a special map which is dominated but a single type of non grass biome.
 * 
 * @param map The map to place biomes on 
 * 
 */
void placeBiomesSpecial(mapTile_t* map,int* biomeCount){
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
    map->biomeArr = malloc(sizeof(biome_t) * (*biomeCount));

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
        map->biomeArr[i] = temp;


    }
    
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
 * @param biomeCount The number of biomes
 */
void generateMap(mapTile_t* map, int* biomeCount){
    int tilePlaced = 1;

    while(tilePlaced == 1){
        tilePlaced = 0;
        for(int i=0; i < *biomeCount; i++){
           ((map->biomeArr) + i)->radius += 1;
            expandBiome(map,*((map->biomeArr) + i),&tilePlaced);
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
               break;
            }

            map->mapArr[i][placeLoc] = '%';
        }
    }
}



/**
 * @brief Adds the Pokecenter and Pokemart to the map
 * 
 * @param map Map to place buildings on
 */
void placeBuildings(mapTile_t* map){

    //Gets locations of first biome for the building
    int rowNum = (map->biomeArr)->cenRowNum;
    int colNum = (map->biomeArr)->cenColNum;
    

    //Adds the Pokemon Center 
    map->mapArr[rowNum][colNum] = 'C';
    map->mapArr[rowNum+1][colNum] = 'C';
    map->mapArr[rowNum][colNum+1]= 'C';
    map->mapArr[rowNum+1][colNum+1]= 'C';

    //Gets the location of the second biome for the building 
    rowNum = ((map->biomeArr) + 1)->cenRowNum;
    colNum = ((map->biomeArr) + 1)->cenColNum;

    //Adds the Pokemart 
    map->mapArr[rowNum][colNum] = 'M';
    map->mapArr[rowNum+1][colNum] = 'M';
    map->mapArr[rowNum][colNum+1] = 'M';
    map->mapArr[rowNum+1][colNum+1] = 'M';

}

/**
 * @brief Converts a given point to its integer id
 * 
 * @param toConvert The point to convert
 * @return The ID 
 */
int convertPoint(point_t toConvert){
   return (toConvert.rowNum * 80) + toConvert.colNum;
}

/**
 * @brief Converts a given ID to its corresponding point
 * 
 * @param toConvert The ID to convert
 * @return The point 
 */
point_t convertID(int toConvert){
    point_t converted;
    converted.rowNum = toConvert / 80;
    converted.colNum = toConvert % 80;

   return converted;
}

/**
 * @brief Downshifts an ID to convert it to the number of space it is without the border. 
 * This value serves as its index in the arrays used in pathfinding
 * 
 * @param id The id to downshift
 * @return The downshifted id
 */
int indexID(int id){
    int rowNum =  id / 80;
    return id - (81 + ((rowNum -1) * 2));
}


/**
 * @brief Converts a point to an ID and then downshifts it to be used as its location in arrays.
 * Invalid points return -1
 * 
 * @param toConvert The point to get the ID for
 * @return The downshifted ID
 */
int pointToLocID(void* toConvert){
    point_t point = *((point_t*) toConvert);
    
    if(point.rowNum == 0 || point.rowNum == 20 || point.colNum == 0 || point.colNum == 79){
        return -1;
    }

    int id = convertPoint(point);
    return indexID(id);
}


/**
 * @brief Uses dijkstra's algorithm to generate an array which stores the shortest path for a road to take by holding the
 * predecessor of each point in the array
 * 
 * @param map The map to draw the roads on
 * @param startLoc The starting location to use as the source in  dijkstra's algorithm
 * @param prev The array to store the predecessors in
 */
void dijkstraPathfindRoad(mapTile_t map, point_t startLoc,int* prev){
    int mapSize = 1482;
    int dist[mapSize];
    dist[indexID(convertPoint(startLoc))] = 0;
    
    queue_t priQueue;
    queueInit(&priQueue,mapSize,sizeof(point_t), pointToLocID);

    point_t temp;
    int  id;

    for(int i=1; i< 20; i++){
        for(int j=1; j< 79; j++){
 
            temp.rowNum = i;
            temp.colNum = j;
            id = convertPoint(temp);

            if(i != startLoc.rowNum || j != startLoc.colNum){
                dist[indexID(id)] =  __INT_MAX__ - 500000;
                prev[indexID(id)] = -1;
            }
            if(map.mapArr[i][j] != 'C' && map.mapArr[i][j] != 'M'){
                void* tempV = malloc(sizeof(temp));
                memcpy(tempV,&temp,sizeof(temp));

                queueAddWithPriority(&priQueue,tempV,dist[indexID(id)]);

                free(tempV);
            }
            
        }
    }

    int size = queueSize(&priQueue);
    
    while (size > 0){
        void* currEntryV = (queueExtractMin(&priQueue));
        point_t currEntry = *((point_t*) currEntryV);
        free(currEntryV);

        int currID = convertPoint(currEntry);

        point_t currNeighbor;



        for(int i =0; i < 4; i++){
            int rowMod = 0;
            int colMod = 0;

            if(i == 0 ){
                rowMod = -1;
            }
            else if(i == 1){
                rowMod = 1;
            }
            else if(i == 2){
                colMod = -1;
            }
            else if(i == 3){
                colMod = 1;
            }



            currNeighbor.rowNum = currEntry.rowNum + rowMod;      
            currNeighbor.colNum = currEntry.colNum +  colMod;
            void* neighborV = malloc(sizeof(currNeighbor));
            memcpy(neighborV,&currNeighbor,sizeof(currNeighbor));

            if(checkInQueue(&priQueue,neighborV) == 0){
                free(neighborV);
                continue;
            }
            free(neighborV);

            int neighborID = convertPoint(currNeighbor);



            int currMod;
            char neighborChar = map.mapArr[currNeighbor.rowNum][currNeighbor.colNum];
            currMod = 1;
            if(neighborChar == '%' || neighborChar == '~'){
                currMod = 5000;
            }
            else if(neighborChar == '#' || neighborChar == '='){
                currMod = 1;
            }
            else{
                currMod = 2;
            }
            
            int altDist = dist[indexID(currID)] + currMod;
            
            if (altDist < dist[indexID(neighborID)]){
                dist[indexID(neighborID) ] = altDist;
                prev[indexID(neighborID)] = currID; 
                
                 void* neighborV = malloc(sizeof(currNeighbor));
                 memcpy(neighborV,&currNeighbor,sizeof(currNeighbor));

                queueDecreasePriority(&priQueue,neighborV, altDist);

                free(neighborV);

            }
        }
      
                

    size = queueSize(&priQueue);
    }
    queueDestroy(&priQueue);             
} 


/**
 * @brief Draws a road on the map between the two given points
 * 
 * @param map The map to draw the road on
 * @param startLoc The starting location to draw the road from.
 * @param targetLoc The end point to draw the road to
 */
void drawRoad(mapTile_t* map,point_t startLoc, point_t targetLoc){
    
    int prevArr[1482];

    dijkstraPathfindRoad(*map,startLoc,prevArr);
    
    int startID = convertPoint(startLoc);
    int currID  = convertPoint(targetLoc);
    //int nextID = convertPoint(targetLoc);
    int trigger = 1;

    while(trigger != 0){

        point_t currPoint = convertID(currID);
        if(map->mapArr[currPoint.rowNum][currPoint.colNum] == '~' || map->mapArr[currPoint.rowNum][currPoint.colNum] == '='){
            map->mapArr[currPoint.rowNum][currPoint.colNum] = '=';
        }
        else{
            map->mapArr[currPoint.rowNum][currPoint.colNum] = '#';
        }

        if(currID != startID){
            currID = prevArr[indexID(currID)];
        }
        else{
            trigger =0;
        }
        
        //nextID = currID;
    }


}

/**
 * @brief Adds the road network connecting the entrances and buildings to the map
 * 
 * @param map The map to add roads to
 */
void addRoadSystem(mapTile_t* map){
    //Intialzied points to hold location
    point_t leftEnt;
    point_t rightEnt;
    point_t  startPoint;
    point_t  endPoint;

    if(map->leftEntLoc != -1){
        leftEnt.rowNum = map->leftEntLoc;
    }
    else{
         leftEnt.rowNum = (rand() % 15) +1;;
    }

    if(map->rightEntLoc != -1){
        rightEnt.rowNum = map->rightEntLoc;
    }
    else{
         rightEnt.rowNum = (rand() % 15) +1;;
    }
    
    leftEnt.colNum = 1;
    rightEnt.colNum = 78;


    //Draws a road from the left entrance to the right
     drawRoad(map,leftEnt,rightEnt);

    
    //Draws a road to the Pokecenter
    endPoint.colNum = (map->biomeArr)->cenColNum;
    endPoint.rowNum = (map->biomeArr)->cenRowNum -1;
    drawRoad(map,leftEnt,endPoint);

    //Draws a road to the Pokemart
    endPoint.colNum = ((map->biomeArr) + 1)->cenColNum;
    endPoint.rowNum = ((map->biomeArr) + 1)->cenRowNum -1;
    drawRoad(map,leftEnt,endPoint);
    
    int locTracker;
    char toCheck;
    if(map->topEntLoc != -1){
        //Make a variable to hold row num of roads
        locTracker = 1;

        //Draws a road from the top entrance
        startPoint.colNum = map->topEntLoc;
        startPoint.rowNum = 1;
        
        toCheck = map->mapArr[startPoint.colNum][locTracker];

        while(toCheck != '#' && toCheck != '='){
            locTracker++;
            toCheck = map->mapArr[locTracker][startPoint.colNum];
        }

        endPoint.colNum = startPoint.colNum;
        endPoint.rowNum = locTracker;
        drawRoad(map,startPoint,endPoint);
    }

    if(map->bottomEntLoc != -1){
        //Draws a road from the bottom entrance
        locTracker = 20;

        startPoint.colNum = map->bottomEntLoc;
        startPoint.rowNum = 19;
        toCheck = map->mapArr[locTracker][startPoint.colNum];

        while(toCheck != '#' && toCheck != '='){
            locTracker -= 1;
            toCheck = map->mapArr[locTracker][startPoint.colNum];
        }

        endPoint.colNum = startPoint.colNum;
        endPoint.rowNum = locTracker;
        drawRoad(map,startPoint,endPoint);
    }


    
}

mapTile_t createMapTile(worldMap_t worldMap, int worldRow, int worldCol){
    
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
    int placedInd;
    mapTile_t neighbor;

    if(worldRow == 0){
        topEnt = -1;
    }
    else{
        placedInd = worldMap.placedArr[worldRow -1][worldCol];
        if(placedInd == 1){
            neighbor = worldMap.worldArr[worldRow -1][worldCol];
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
        placedInd = worldMap.placedArr[worldRow + 1][worldCol];
        if(placedInd == 1){
            neighbor = worldMap.worldArr[worldRow + 1][worldCol];
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
        placedInd = worldMap.placedArr[worldRow][worldCol - 1];
        if(placedInd == 1){
            neighbor = worldMap.worldArr[worldRow][worldCol - 1];
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
         placedInd = worldMap.placedArr[worldRow][worldCol + 1];
        if(placedInd == 1){
            neighbor = worldMap.worldArr[worldRow][worldCol + 1];
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
    int biomeCount;


    //Randomly generates the biomes of this  map depending on type
    if(mapType == '.'){
        placeBiomesGrassLands(&map,&biomeCount);
    }
    else{
       placeBiomesSpecial(&map,&biomeCount);
    }

    generateMap(&map,&biomeCount);
    //Places other necessary items
    placeRiversxRanges(&map);

    int manDist = abs(200 - worldRow) + abs(200 - worldCol);
    int spawnChance = (((-45.0 * manDist)/200.0) + 50);
    int spawnNum = (rand() % 100) + 1;

    if(spawnNum < spawnChance || (worldRow == 200 && worldCol == 200)){
        placeBuildings(&map);
    }
    
    addRoadSystem(&map);
    
    

    return map;

}

mapTile_t createMapTileIndependent(){
    
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

    topEnt = (rand() % 78) +1;
    bottomEnt = (rand() % 78) +1;
    leftEnt = (rand() % 19) +1;
    rightEnt = (rand() % 19) +1;
  

    //Creates a struct to hold the map
    //mapTile_t* map = malloc(sizeof(mapTile_t));
    mapTile_t map = mapTileInit(mapType,topEnt,bottomEnt,leftEnt,rightEnt);

    //Creates a variable to store the number of biomes
    int biomeCount;


    //Randomly generates the biomes of this  map depending on type
    if(mapType == '.'){
        placeBiomesGrassLands(&map,&biomeCount);
    }
    else{
       placeBiomesSpecial(&map,&biomeCount);
    }

    generateMap(&map,&biomeCount);
    //Places other necessary items
    placeRiversxRanges(&map);
    placeBuildings(&map);
    
    
    addRoadSystem(&map);
    
    

    return map;

}
