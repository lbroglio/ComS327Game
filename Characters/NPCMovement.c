#include<stdio.h>
#include<time.h>
#include<string.h>
#include"../Map/map.h"
#include"../Map/biome.h"
#include"../Map/mapGeneration.h"
#include"../Data-Structures/priorityQueue.h"
#include"gameCharacter.h"


/**
 * @brief Generates an array with the distances from every square to the player for a hiker NPC
 * 
 * @param map To map to find the distances for
 * @param player The player struct with the PCs location
 * @param dist Array to store the tiles distances in 
 */
void dijkstraPathfindHiker(mapTile_t map, character_t player,int dist[21][80]){
    //Creates the necessary array
    int mapSize = 1482;
    dist[player.rowNum][player.colNum] = 0;
    
    //Creates Priority Queue
    queue_t priQueue;
    queueInit(&priQueue,mapSize,sizeof(point_t),pointToLocID);

    point_t temp;

    //Puts all the points into the Queue 
    for(int i=1; i< 20; i++){
        for(int j=1; j< 79; j++){
 
            temp.rowNum = i;
            temp.colNum = j;

            if(i != player.rowNum || j != player.colNum){
                dist[i][j] =  __INT_MAX__ - 500000;
            }
            if(map.mapArr[i][j] != '~'){
                void* tempV = malloc(sizeof(temp));
                memcpy(tempV,&temp,sizeof(temp));

                queueAddWithPriority(&priQueue,tempV,dist[i][j]);

                free(tempV);
            }
            else{
                dist[i][j] =  -1;
            }
            
        }
    }

    int size = queueSize(&priQueue);
    
    while (size > 0){
        void* currEntryV = (queueExtractMin(&priQueue));
        point_t currEntry = *((point_t*) currEntryV);
        free(currEntryV);

        point_t currNeighbor;


        //For Every neighbor
        for(int i =0; i < 8; i++){
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
            else if(i == 4){
                rowMod = -1;
                colMod = -1;
            }
            else if(i ==  5){
                rowMod = 1;
                colMod = 1;
            }
            else if(i == 6){
                colMod = -1;
                rowMod  = 1;
            }
            else if(i == 7){
                colMod = 1;
                rowMod = -1;
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


            //Check Distance
            int currMod;
            char neighborChar = map.mapArr[currNeighbor.rowNum][currNeighbor.colNum];
            currMod = 1;
            if(neighborChar == '%' || neighborChar == '\"' || neighborChar == ':' ){
                currMod = 15;
            }
            else if(neighborChar == '#' || neighborChar == '=' || neighborChar == '.'){
                currMod = 10;
            }
            else if(neighborChar == 'C' || neighborChar == 'M'){
                currMod = 50;
            }
            
            //Change  its distance if its left
            int altDist = dist[currEntry.rowNum][currEntry.colNum] + currMod;
            
            if (altDist < dist[currNeighbor.rowNum][currNeighbor.colNum]){
                dist[currNeighbor.rowNum][currNeighbor.colNum] = altDist; 

                
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
 * @brief Generates an array with the distances from every square to the player for a rival NPC
 * 
 * @param map To map to find the distances for
 * @param player The player struct with the PCs location
 * @param dist Array to store the tiles distances in 
 */
void dijkstraPathfindRival(mapTile_t map,  character_t player,int dist[21][80]){
//Creates the necessary array
    int mapSize = 1482;
    dist[player.rowNum][player.colNum] = 0;
    
    //Creates Priority Queue
    queue_t priQueue;
    queueInit(&priQueue,mapSize,sizeof(point_t),pointToLocID);

    point_t temp;

    //Puts all the points into the Queue 
    for(int i=1; i< 20; i++){
        for(int j=1; j< 79; j++){
 
            temp.rowNum = i;
            temp.colNum = j;

            if(i != player.rowNum || j != player.colNum){
                dist[i][j] =  __INT_MAX__ - 500000;
            }
            if(map.mapArr[i][j] != '~' && map.mapArr[i][j] != '%' && map.mapArr[i][j] != '\"'){
                void* tempV = malloc(sizeof(temp));
                memcpy(tempV,&temp,sizeof(temp));

                queueAddWithPriority(&priQueue,tempV,dist[i][j]);

                free(tempV);
            }
            else{
                dist[i][j] =  -1;
            }
            
        }
    }

    int size = queueSize(&priQueue);
    
    while (size > 0){
        void* currEntryV = (queueExtractMin(&priQueue));
        point_t currEntry = *((point_t*) currEntryV);
        free(currEntryV);

        point_t currNeighbor;


        //For Every neighbor
        for(int i =0; i < 8; i++){
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
            else if(i == 4){
                rowMod = -1;
                colMod = -1;
            }
            else if(i ==  5){
                rowMod = 1;
                colMod = 1;
            }
            else if(i == 6){
                colMod = -1;
                rowMod  = 1;
            }
            else if(i == 7){
                colMod = 1;
                rowMod = -1;
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


            //Check Distance
            int currMod;
            char neighborChar = map.mapArr[currNeighbor.rowNum][currNeighbor.colNum];
            currMod = 1;
            if(neighborChar == ':' ){
                currMod = 20;
            }
            else if(neighborChar == '#' || neighborChar == '=' || neighborChar == '.'){
                currMod = 10;
            }
            else if(neighborChar == 'C' || neighborChar == 'M'){
                currMod = 50;
            }
            
            //Change  its distance if its left
            int altDist = dist[currEntry.rowNum][currEntry.colNum] + currMod;
            
            if (altDist < dist[currNeighbor.rowNum][currNeighbor.colNum]){
                dist[currNeighbor.rowNum][currNeighbor.colNum] = altDist; 

                
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
 * @brief Prints out a distance array 
 * (Limits the dist vals to 2 digits)
 * @param dist The array to print out
 */
void printDistArr(int dist[21][80]){
    for(int i =0; i < 21; i++){
        for(int j =0; j < 80; j++){
            if(i != 0 && i != 20 && j != 0 && j != 79 && dist[i][j] != -1){
                printf("%02d ",dist[i][j] % 100);
            }
            else{
                printf("  ");
            }
            
    }
    printf("\n");
    }
}

/**
 * @brief Gets all possible moves a character could make and stores them in an array sorted by distance
 * 
 * @param toMove The character being moved
 * @param mapInfo The NPC info for the current map
 * @param possible_moves The array to store the possible moves in
 * @return The number of possible moves
 */
int getPossibleMoves(character_t toMove, nMapInfo_t mapInfo, point_t* possibleMoves){
     //Stores the current number of added points
     int tracker = 0;

    //Loops through all the possible increments that can find the points neighbors
     for(int i=-1; i < 2; i++){
        for(int j=-1; j < 2; j++){

            //Skips if both are zero (This is the same location as the character which is being moved)
            if(i == 0 && j == 0){
                continue;
            }

            //Gets the distance of the current neighbor
            int dist = mapInfo.hikerDist[toMove.rowNum + i][toMove.colNum + j];

            //If the space is reachable (-1 represents terrain which cannot be traversed)
            if(dist != -1){

                //Creates a point for the current neighbor
                point_t newPos;
                newPos.rowNum = toMove.rowNum + i;
                newPos.colNum = toMove.colNum + j;

                //Adds the new point to the end of the array 
                possibleMoves[tracker] = newPos;

                //Sets up a tracker varaible to sort the array with 
                int shift = tracker - 1;

                //Increments number of stores elements by one
                tracker += 1;

                //Moves the new point down the array unti its in a sorted position. (Functionally this is a single pass of insertion sort)
                while(shift >= 0){
                    int prevDist = mapInfo.hikerDist[possibleMoves[shift].rowNum][possibleMoves[shift].colNum];
                    if(dist < prevDist){
                        possibleMoves[shift + 1] = possibleMoves[shift];
                        possibleMoves[shift] = newPos;
                    }
                    else{
                        shift -= 8;
                    }
                }

            }

        }
    }
    //Returns the number of stored points
    return tracker;
}


void moveHiker(character_t* toMove, nMapInfo_t* mapInfo){
    //Gets the squares it could move to ordered by distance
    point_t possibleMoves[8];
    int numMoves = getPossibleMoves(*toMove,*mapInfo,possibleMoves);
    int i;
    point_t bestMove;
    bestMove.rowNum = -1;
    bestMove.colNum = -1;

    for(int i =0; i < numMoves; i++){
        point_t currBestMove = possibleMoves[i];
        if(mapInfo->charLocations[currBestMove.rowNum][currBestMove.colNum] != 'X'){
            bestMove = currBestMove;
            i += 8;
        }
    }

    if(bestMove.rowNum == -1){
        return;
    }
   

   
}




char moveNPC(queue_t* eventManager,character_t* player, mapTile_t map, nMapInfo_t* mapInfo){

    if(mapInfo->playerLocation.rowNum != player->rowNum || mapInfo->playerLocation.colNum != player->colNum){
        dijkstraPathfindHiker(map,*(player),mapInfo->hikerDist);
        dijkstraPathfindRival(map,*(player),mapInfo->rivalDist);
        mapInfo->playerLocation.rowNum = player->rowNum;
        mapInfo->playerLocation.colNum = player->colNum;
    }

    character_t* toMove = malloc(sizeof(toMove)); 
    memcpy(toMove,queueExtractMin(eventManager),sizeof(toMove));  

    switch (toMove->type)
    {
        case '@':
            //TO BE IMPLEMENTED AS IT IS THIS SHOULD NEVER HAPPEN
            break;
        case 'h':
            //HIKER
            break;
        case 'r':
            //RIVAL
            break;
        case 'p':
            //PACER
            break;
        case 'w':
            //WANDERERS
            break;
        case 's':
            //SENTRIES
            break;
        case 'e':
            //EXPLORERS
            break;
         case 'm':
            //Swimmers
            break;
    }



}

nMapInfo_t npcMapInfoInit(){
    nMapInfo_t toReturn;
    toReturn.playerLocation.rowNum = -1;
    toReturn.playerLocation.colNum = -1;

    //Fills the adjacency array with X markers
    for(int i =0; i< 21; i++){
        for(int j =0; j < 80; j++){
            toReturn.charLocations[i][j] = 'X';
        }
    }
}

 
