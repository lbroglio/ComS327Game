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

            //Make sure the current point is in the queue
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
            if((i == 0 && j == 0) ||  toMove.rowNum + i == 0 || toMove.rowNum + i == 20 || toMove.colNum + j == 0 || toMove.rowNum + j == 79){
                continue;
            }

            int dist;
            //Gets the distance of the current neighbor
            if(toMove.type == 'h'){
                dist = mapInfo.hikerDist[toMove.rowNum + i][toMove.colNum + j];
            }
            else{
                dist = mapInfo.rivalDist[toMove.rowNum + i][toMove.colNum + j];
            }
            

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

                    int prevDist;

                    if(toMove.type == 'h'){
                        prevDist = mapInfo.hikerDist[possibleMoves[shift].rowNum][possibleMoves[shift].colNum];
                    }
                    else{
                        prevDist = mapInfo.rivalDist[possibleMoves[shift].rowNum][possibleMoves[shift].colNum];
                    }

                    if(dist < prevDist){
                        possibleMoves[shift + 1] = possibleMoves[shift];
                        possibleMoves[shift] = newPos;
                        shift -= 1;
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

/**
 * @brief Checks that the pacer can continue in its current direction while staying in complaince with its rules. Changes direction if necessary
 * Returns the next space the pacer wil move into
 * 
 * @param toCheck Pointer to the pacer to check
 * @param map The map which the pacer is on
 * @param nextSpace The space the pacer is moving unto 
 * @return The space the pacer should move into 
 */
point_t checkDirecPacer(character_t* toCheck,mapTile_t map, nMapInfo_t mapInfo){
    point_t nextSpace;
    char* illegalChars = "~\"%% ";
    //Checks to see if the pacer can legally move forward
    if(strchr(illegalChars,map.mapArr[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)]) != NULL || mapInfo.charLocations[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)] != 'X'){
        //If the space is illegal turn around
        toCheck->direction.rowNum *= -1;
        toCheck->direction.colNum *= -1;

        //Checks to make sure the new space isn't occupied by another character 
        if(mapInfo.charLocations[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)] != 'X'){
            //Updates nextSpace in case direction changed
            nextSpace.rowNum = toCheck->rowNum + (toCheck->direction.rowNum);
            nextSpace.colNum = toCheck->colNum + (toCheck->direction.colNum);
        }
        else{
            //Sets next space to the current space (Character won't move)
            nextSpace.rowNum = toCheck->rowNum;
            nextSpace.colNum = toCheck->colNum;
        }

    }
    else{
        //Updates Next Space
        nextSpace.rowNum = toCheck->rowNum + (toCheck->direction.rowNum);
        nextSpace.colNum = toCheck->colNum + (toCheck->direction.colNum);
    }
    return nextSpace;
}

/**
 * @brief Checks to see if a wanderer can keep moving in its current direction. If not finds a legal direction for it to move.
 * 
 * @param toCheck The wanderer to check the spaces for
 * @param map The map the wanderer is on
 * @param mapInfo The NPC info struct for the map
 * @param moveOptions List of possible moves that can be randomly chosen (Used for recusrive call)
 * @param numOptions The number of possible moves
 * @return The next space the wanderer will move into
 */
point_t checkDirecWanderer(character_t* toCheck,mapTile_t map,nMapInfo_t mapInfo,point_t moveOptions[], int numOptions){
    point_t nextSpace;

    //Checks to see if there is only one space left
    if(numOptions == 1){
        //If the remaining space is invalid
        if(map.mapArr[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)] != toCheck->spawnBiome || mapInfo.charLocations[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)] != 'X'){
            //Sets next space to the current space (Character won't move)
            nextSpace.rowNum = toCheck->rowNum;
            nextSpace.colNum = toCheck->colNum;
        }
        //If its free
        else{
            //Updates Next Space
            nextSpace.rowNum = toCheck->rowNum + (toCheck->direction.rowNum);
            nextSpace.colNum = toCheck->colNum + (toCheck->direction.colNum);
            return nextSpace;
        }
    }
    //If the current space is blocked or illegal
    else if(map.mapArr[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)] != toCheck->spawnBiome || mapInfo.charLocations[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)] != 'X'){
        //Randomly chooses a new direction to move in 
        int moveNum = rand() % numOptions;
        toCheck->direction = moveOptions[moveNum];

        //Makes a new array to store moves
        point_t newArr[numOptions -1];
        int tracker = 0; 

        //Adds all the moves except for the current one to the array
        for(int i =0; i < numOptions; i ++){
            if(i != moveNum){
                newArr[tracker] = moveOptions[i];
                tracker += 1;
            }
        }
        //Recursively call to verify new move or choose another
        nextSpace = checkDirecWanderer(toCheck,map,mapInfo,newArr,numOptions - 1);
    }
    //If the space is avaiable
    else{
        //Updates Next Space
        nextSpace.rowNum = toCheck->rowNum + (toCheck->direction.rowNum);
        nextSpace.colNum = toCheck->colNum + (toCheck->direction.colNum);
    }
    return nextSpace;
}

/**
 * @brief Checks to see if a explorer can keep moving in its current direction. If not finds a legal direction for it to move.
 * 
 * @param toCheck The explorer to check the spaces for
 * @param map The map the explorer is on
 * @param mapInfo The NPC info struct for the map
 * @param moveOptions List of possible moves that can be randomly chosen (Used for recusrive call)
 * @param numOptions The number of possible moves
 * @return The next space the explorer will move into
 */
point_t checkDirecExplorer(character_t* toCheck,mapTile_t map,nMapInfo_t mapInfo,point_t moveOptions[], int numOptions){
    point_t nextSpace;
    char* illegalChars = "~%% ";
    //Checks to see if there is only one space left
    if(numOptions == 1){
        //If the remaining space is invalid
        if(strchr(illegalChars,map.mapArr[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)]) != NULL || mapInfo.charLocations[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)] != 'X'){
            //Sets next space to the current space (Character won't move)
            nextSpace.rowNum = toCheck->rowNum;
            nextSpace.colNum = toCheck->colNum;
        }
        //If its free
        else{
            //Updates Next Space
            nextSpace.rowNum = toCheck->rowNum + (toCheck->direction.rowNum);
            nextSpace.colNum = toCheck->colNum + (toCheck->direction.colNum);
            return nextSpace;
        }
    }
    //If the current space is blocked or illegal
    else if(strchr(illegalChars,map.mapArr[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)]) != NULL|| mapInfo.charLocations[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)] != 'X'){
        //Randomly chooses a new direction to move in 
        int moveNum = rand() % numOptions;
        toCheck->direction = moveOptions[moveNum];

        //Makes a new array to store moves
        point_t newArr[numOptions -1];
        int tracker = 0; 

        //Adds all the moves except for the current one to the array
        for(int i =0; i < numOptions; i ++){
            if(i != moveNum){
                newArr[tracker] = moveOptions[i];
                tracker += 1;
            }
        }
        //Recursively call to verify new move or choose another
        nextSpace = checkDirecExplorer(toCheck,map,mapInfo,newArr,numOptions - 1);
    }
    //If the space is avaiable
    else{
        //Updates Next Space
        nextSpace.rowNum = toCheck->rowNum + (toCheck->direction.rowNum);
        nextSpace.colNum = toCheck->colNum + (toCheck->direction.colNum);
    }
    return nextSpace;
}

/**
 * @brief Checks to see if a wandering swimmer can keep moving in its current direction. If not finds a legal direction for it to move.
 * 
 * @param toCheck The swimmer to check the spaces for
 * @param map The map the swimmer is on
 * @param mapInfo The NPC info struct for the map
 * @param moveOptions List of possible moves that can be randomly chosen (Used for recusrive call)
 * @param numOptions The number of possible moves
 * @return The next space the swimmer will move into
 */
point_t checkDirecSwimmerWander(character_t* toCheck,mapTile_t map,nMapInfo_t mapInfo,point_t moveOptions[], int numOptions){
    point_t nextSpace;
    char* illegalChars = "CM#\"%%.: ";
    //Checks to see if there is only one space left
    if(numOptions == 1){
        //If the remaining space is invalid
        if(strchr(illegalChars,map.mapArr[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)]) != NULL|| mapInfo.charLocations[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)] != 'X'){
            //Sets next space to the current space (Character won't move)
            nextSpace.rowNum = toCheck->rowNum;
            nextSpace.colNum = toCheck->colNum;
        }
        //If its free
        else{
            //Updates Next Space
            nextSpace.rowNum = toCheck->rowNum + (toCheck->direction.rowNum);
            nextSpace.colNum = toCheck->colNum + (toCheck->direction.colNum);
            return nextSpace;
        }
    }
    //If the current space is blocked or illegal
    else if(strchr(illegalChars,map.mapArr[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)]) != NULL|| mapInfo.charLocations[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)] != 'X'){
        //Randomly chooses a new direction to move in 
        int moveNum = rand() % numOptions;
        toCheck->direction = moveOptions[moveNum];

        //Makes a new array to store moves
        point_t newArr[numOptions -1];
        int tracker = 0; 

        //Adds all the moves except for the current one to the array
        for(int i =0; i < numOptions; i ++){
            if(i != moveNum){
                newArr[tracker] = moveOptions[i];
                tracker += 1;
            }
        }
        //Recursively call to verify new move or choose another
        nextSpace = checkDirecSwimmerWander(toCheck,map,mapInfo,newArr,numOptions - 1);
    }
    //If the space is avaiable
    else{
        //Updates Next Space
        nextSpace.rowNum = toCheck->rowNum + (toCheck->direction.rowNum);
        nextSpace.colNum = toCheck->colNum + (toCheck->direction.colNum);
    }
    return nextSpace;
}

/**
 * @brief Checks to see if a wandering swimmer can keep moving in its current direction. If not finds a legal direction for it to move.
 * 
 * @param toCheck The swimmer to check the spaces for
 * @param map The map the swimmer is on
 * @param mapInfo The NPC info struct for the map
 * @return The next space the swimmer will move into
 */
point_t checkDirecSwimmerCharge(character_t* toCheck,mapTile_t map,nMapInfo_t mapInfo){
    point_t nextSpace;
    char* illegalChars = "#\"%%.: ";
    toCheck->direction.rowNum = (mapInfo.playerLocation.rowNum - toCheck->rowNum ) / abs(mapInfo.playerLocation.rowNum - toCheck->rowNum );
    toCheck->direction.colNum = (mapInfo.playerLocation.colNum - toCheck->colNum ) / abs(mapInfo.playerLocation.colNum - toCheck->colNum );

    //If the swimmer can move in the direction of the player
    if((strchr(illegalChars,map.mapArr[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)])) == NULL && mapInfo.charLocations[toCheck->rowNum + (toCheck->direction.rowNum)][toCheck->colNum + (toCheck->direction.colNum)] == 'X'){
        //Updates Next Space
        nextSpace.rowNum = toCheck->rowNum + (toCheck->direction.rowNum);
        nextSpace.colNum = toCheck->colNum + (toCheck->direction.colNum);
    }
    //If it can't
    else{
        //Sets next space to the current space (Character won't move)
        nextSpace.rowNum = toCheck->rowNum;
        nextSpace.colNum = toCheck->colNum;
    }
    return nextSpace;
}






/**
 * @brief Checks that the character can continue in its current direction while staying in complaince with its rules. 
 * Changes direction if necessary. This function is a wrapper for the individual checks for different character types most of which act recursively (Pacer doesn't)
 * 
 * @param toCheck Pointer to the character to check
 * @param map The map which the character is on
 * @param nextSpace The space the character is moving unto 
 */
point_t checkDirection(character_t* toCheck, mapTile_t map, nMapInfo_t mapInfo){
    point_t defaultReturn;
    defaultReturn.rowNum = -1;

    defaultReturn.colNum = -1;

   //Stores the possible moves for the characters
   point_t moveOptions[8] = {pointInit(-1,0),pointInit(-1,1),pointInit(0,1),pointInit(1,1),pointInit(1,0),pointInit(1,-1),pointInit(0,-1),pointInit(-1,-1)};
   switch (toCheck->type)
   {
    case 'p':
        return checkDirecPacer(toCheck,map,mapInfo);
        break;
    case 'w':
        return checkDirecWanderer(toCheck,map,mapInfo,moveOptions,8);
        break;
    case 'e':
        return checkDirecExplorer(toCheck,map,mapInfo,moveOptions,8);
        break;
    case 'm':
        if(mapInfo.playerByWater == 0){
            return checkDirecSwimmerWander(toCheck,map,mapInfo,moveOptions,8);
        }
        else{
            return checkDirecSwimmerCharge(toCheck,map,mapInfo);
        }
        break;
    default:
        return defaultReturn;
        break; 
   }
}


/**
 * @brief Moves a given hiker or rival character on the map
 * 
 * @param toMove Pointer to the hiker to move
 * @param mapInfo NPC info for the current map tile
 */
char movePathfinder(character_t* toMove, mapTile_t map, nMapInfo_t* mapInfo){
    //Gets the squares it could move to ordered by distance
    point_t possibleMoves[8];
    int numMoves = getPossibleMoves(*toMove,*mapInfo,possibleMoves);
    //Creates a point to store the best move in
    point_t bestMove;
    bestMove.rowNum = -1;
    bestMove.colNum = -1;

    //Gets the move with the least distance that isnt occupied by a character
    for(int i =0; i < numMoves; i++){
        point_t currBestMove = possibleMoves[i];
        if(mapInfo->charLocations[currBestMove.rowNum][currBestMove.colNum] == 'X'){
            bestMove.rowNum = currBestMove.rowNum;
            bestMove.colNum = currBestMove.colNum;
            i += 8;
        }
    }

    //Returns if there is no possible move (This should be rare if not impossible)
    if(bestMove.rowNum == -1){
        printf("HERE");
        return  'x';
    }

    //Moves the character inside the character location array
    mapInfo->charLocations[toMove->rowNum][toMove->colNum] = 'X';
    mapInfo->charLocations[bestMove.rowNum][bestMove.colNum] = toMove->type;

    //Changes the characters location within its struct
    toMove->rowNum = bestMove.rowNum; 
    toMove->colNum = bestMove.colNum;

    return map.mapArr[bestMove.rowNum][bestMove.colNum];    
}

char moveWayfinder(character_t* toMove, mapTile_t map, nMapInfo_t* mapInfo){
    point_t nextSpace = checkDirection(toMove,map,*mapInfo);

    //Moves the character inside the character location array
    mapInfo->charLocations[toMove->rowNum][toMove->colNum] = 'X';
    mapInfo->charLocations[nextSpace.rowNum][nextSpace.colNum] = toMove->type;

    //Changes the characters location within its struct
    toMove->rowNum = nextSpace.rowNum; 
    toMove->colNum = nextSpace.colNum;   

    return map.mapArr[nextSpace.rowNum][nextSpace.colNum];
}

int checkPlayerByWater(character_t player, mapTile_t map){
    //Checks all adjacent squars
    if(map.mapArr[player.rowNum][player.colNum] == '~' || map.mapArr[player.rowNum ][player.colNum] == '=' || map.mapArr[player.rowNum - 1][player.colNum] == '~' || map.mapArr[player.rowNum - 1][player.colNum] == '=' || map.mapArr[player.rowNum + 1][player.colNum] == '~' || map.mapArr[player.rowNum + 1][player.colNum] == '=' || map.mapArr[player.rowNum][player.colNum - 1] == '~' || map.mapArr[player.rowNum][player.colNum - 1] == '=' || map.mapArr[player.rowNum ][player.colNum + 1] == '~' || map.mapArr[player.rowNum][player.colNum + 1] == '='){
        return 1;
    }
    else{
        return 0;
    }
}

char moveNPC(queue_t* eventManager, character_t* player, mapTile_t map, nMapInfo_t* mapInfo){

    //If the player has moved
    if(mapInfo->playerLocation.rowNum != player->rowNum || mapInfo->playerLocation.colNum != player->colNum){
        //Redraw pathfinding maps
        dijkstraPathfindHiker(map,*(player),mapInfo->hikerDist);
        dijkstraPathfindRival(map,*(player),mapInfo->rivalDist);

        //Change last known player location
        mapInfo->playerLocation.rowNum = player->rowNum;
        mapInfo->playerLocation.colNum = player->colNum;

        //Check if the player is adjacent to water
        mapInfo->playerByWater = checkPlayerByWater(*player,map);
    }

    //Get the next Character to move from the queue
    int time;
    void* temp = (queueExtractMinWithPri(eventManager,&time));
    character_t* toMove = ((character_t*) temp);


    //Perform the move
    char moveType;
    if(toMove->type == '@' || toMove->type == 's'){
        //THIS OPTION CURRENTLY DOES NOTHIING AS THESE CHARACTER TYPES DON'T HAVE ANY MOVES THEY CAN TAKE
        //They are given mountain move typees as place holders so they move back in the queue
        moveType = '%';
        /*
        printMapWithChars(&map,*mapInfo);
        printf("\n");
        */

    }
    else if(toMove->type == 'h' || toMove->type == 'r'){
        moveType = movePathfinder(toMove,map,mapInfo);
    }
    else{
        moveType = moveWayfinder(toMove,map,mapInfo);
    }

    //Set the cost for the move
    int moveCost;
    if(moveType == '%'){
        moveCost = 15;
    }
    else if(moveType == '#' || moveType == '='){
        if(toMove->type == 's'){
            moveCost = 7;
        }
        moveCost = 10;
    }
    else if(moveType == 'C' || moveType == 'M'){
        if(toMove -> type == '@'){
            moveCost = 10;
        }
        else{
            moveCost = 50;
        }
    }
    else if(moveType == ':'){
        if(toMove->type == 'h'){
            moveCost = 15;
        }
        else{
            moveCost = 20;
        }
    }
    else if(moveType == '.'){
        moveCost = 10;
    }
    else if(moveType == '\"'){
        moveCost = 15;
    }
    else if(moveType == '~'){
        moveCost = 7;
    }
    else{
        moveCost = 10;
    }
    
    //Readd the character to the queue
    char typeToReturn = toMove->type;
    memcpy(temp,toMove,sizeof(character_t));
    queueAddWithPriority(eventManager, temp,moveCost + time);

    free(temp);
    
    return typeToReturn;
}

nMapInfo_t npcMapInfoInit(){
    nMapInfo_t toReturn;
    toReturn.playerLocation.rowNum = -1;
    toReturn.playerLocation.colNum = -1;

    //Fills the NPC positions array with X markers
    for(int i =0; i< 21; i++){
        for(int j =0; j < 80; j++){
            toReturn.charLocations[i][j] = 'X';
        }
    }

    return toReturn;

}

character_t characterInit(point_t startLoc, char type, int id, char spawnBiome){
    character_t toReturn;

    toReturn.rowNum = startLoc.rowNum;
    toReturn.colNum = startLoc.colNum;
    toReturn.type = type;
    toReturn.id = id;
    toReturn.spawnBiome = spawnBiome;

    if(type == 'e' || type == 'w' || type == 'm' || type == 'p'){
        toReturn.direction.rowNum = (rand() % 3) - 1;
        toReturn.direction.colNum = (rand() % 3) - 1;
    }  
    else{
        toReturn.direction.rowNum = 0;
        toReturn.direction.colNum = 0;
    }

    return toReturn;
}

int getCharacterId(void* toId){
    return ((character_t*)(toId))->id;
}
 
