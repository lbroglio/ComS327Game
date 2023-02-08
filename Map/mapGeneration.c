#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"biome.h"
#include"map.h"
#include"../Data-Structures/priorityQueue.h"


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


void dijkstraPathfindRoad(mapTile_t map, point_t startLoc,int* prev){
    int mapSize = 1482;
    int* dist = malloc(sizeof(int) * mapSize);
    dist[indexID(convertPoint(startLoc))] = 0;
    int track = 0;

    queue_t* priQueue = malloc(sizeof(priQueue) * mapSize);
    queueInit(priQueue,mapSize);

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
                queueAddWithPriority(priQueue,temp,dist[indexID(id)]);
            }
            
        }
    }

    int size = queueSize(priQueue);
    
    while (size > 0){
        point_t currEntry = queueExtractMin(priQueue);
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
            if(checkInQueue(priQueue,currNeighbor) == 0){
                continue;
            }

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
                track++;
                dist[indexID(neighborID) ] = altDist;
                prev[indexID(neighborID)] = currID; 

                queueDecreasePriority(priQueue,currNeighbor, altDist);
            }
        }
      
                

    size = queueSize(priQueue);
    }
    queueDestroy(priQueue);             
    free(dist);
    printf("%d\n",track);

} 


/**
 * @brief Draws a road on the map between the two given points
 * 
 * @param map The map to draw the road on
 * @param startLoc The starting location to draw the road from.
 * @param targetLoc The end point to draw the road to
 */
void drawRoad(mapTile_t* map,point_t startLoc, point_t targetLoc){
    
    int* prevArr = malloc(sizeof(int) * 1482);

    dijkstraPathfindRoad(*map,startLoc,prevArr);
    
    int startID = convertPoint(startLoc);
    int currID  = 0;
    int nextID = convertPoint(targetLoc);

    while(currID != startID){
        currID = prevArr[indexID(nextID)];
        point_t currPoint = convertID(currID);
        if(map->mapArr[currPoint.rowNum][currPoint.colNum] == '~'){
            map->mapArr[currPoint.rowNum][currPoint.colNum] = '=';
        }
        else{
            map->mapArr[currPoint.rowNum][currPoint.colNum] = '#';
        }

        nextID = currID;
    }

}

/**
 * @brief Adds the road network connecting the entrances and buildings to the map
 * 
 * @param map The map to add roads to
 * @param biomeArr Array of biomes on the map
 */
void addRoadSystem(mapTile_t* map,biome_t* biomeArr){
    point_t leftEnt;
    point_t rightEnt;

    leftEnt.rowNum = map->leftEntLoc;
    leftEnt.colNum = 1;

    rightEnt.rowNum = map->rightEntLoc;
    rightEnt.colNum = 78;

    drawRoad(map,leftEnt,rightEnt);
    
}

mapTile_t* createMapTile(){
    //Randomly chooses what type of map this is. Grasslands maps are weighted slightly highrt
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

    //Creates a struct to hold the map
    mapTile_t* map = malloc(sizeof(mapTile_t));
    *map = mapInit(mapType);

    //Creates a variable to store the number of biomes
    int* biomeCount = malloc(sizeof(biomeCount));


    //Randomly generates the biomes of this  map depending on type
    biome_t* biomeArr;
    if(mapType == '.'){
        biomeArr = placeBiomesGrassLands(map,biomeCount);
    }
    else{
        biomeArr = placeBiomesSpecial(map,biomeCount);
    }

    generateMap(map,biomeArr,biomeCount);
    //Places other necessary items
    placeRiversxRanges(map);
    placeBuildings(map,biomeArr);
    addRoadSystem(map,biomeArr);
    
    //free(biomeCount);
    //free(biomeArr);

    return map;

}

int main(int argc,char** argv){


    srand(time(NULL));

    
    mapTile_t* map =createMapTile();
    printMap(map);
    

}