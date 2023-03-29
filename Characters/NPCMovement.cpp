#include<stdio.h>
#include<time.h>
#include<cstring>
#include<string>
#include"../Map/map.h"
#include"../Map/biome.h"
#include"../Map/mapGeneration.h"
#include"../Data-Structures/priorityQueue.h"
#include"../Battles/battles.h"
#include"gameCharacter.h"
#include"NPCMapInfo.h"
#include"../Screen/screen.h"
#include"playerMovement.h"

//CODE FOR WAYFINDERS ---------------------------------------------------

char Wayfinder::move(mapTile_t* map){
    Point nextSpace = this->checkDirection(map);

    //If a trainer battle was signaled
    if(nextSpace.rowNum == -2){
        printMapWithChars(map, map->mapInfo); 
        trainerBattle(*this, map);
        //THIS MIGHT NEED TO CHANGE DEPEDING ON WHAT THE CHARACTER WINNING A TRAINER BATTLE MEANS
        //Returns the current space
        return map->mapArr[this->rowNum][this->colNum];      
    }

    //Hold character location
    Point temp = Point(this->rowNum,this->colNum);

    //Changes the characters location within its struct
    this->rowNum = nextSpace.rowNum; 
    this->colNum = nextSpace.colNum;  

    //Moves the character inside the character location array
    map->mapInfo.charLocations[temp.rowNum][temp.colNum] = GameCharacter();
    map->mapInfo.charLocations[nextSpace.rowNum][nextSpace.colNum] = *this;

 

    return map->mapArr[nextSpace.rowNum][nextSpace.colNum];
}

Wayfinder::Wayfinder(Point startLoc, char type, int id) : GameCharacter(startLoc,type,id){
    this->direction.rowNum = (rand() % 3) - 1;
    this->direction.colNum = (rand() % 3) - 1;
}

//CODE FOR PACERS ---------------------------------------------------
Point Pacer::checkDirection(mapTile_t* map){
    Point nextSpace;
    std::string illegalChars = "~\"%% ";

    //Checks to see if the pacer can legally move forward
    if(illegalChars.find(map->mapArr[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)]) != std::string::npos || map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type != 'X'){
        //Checks to see if the next space holds the player
        if(map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type == '@'){
            //THIS MIGHT NEED TO CHANGE DEPEDING ON WHAT THE CHARACTER WINNING A TRAINER BATTLE MEANS
            //Sets the next space to an impossible space as a flag for the trainer battle
            nextSpace.rowNum = -2;
            nextSpace.colNum = -2;
        }
        else{
            //If the space is illegal turn around
            this->direction.rowNum *= -1;
            this->direction.colNum *= -1;
        
            //Checks to make sure the new space isn't occupied by another character 
            if(map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type != 'X'){
                //Updates nextSpace in case direction changed
                nextSpace.rowNum = this->rowNum + (this->direction.rowNum);
                nextSpace.colNum = this->colNum + (this->direction.colNum);
            }
            //If the next space is occupied by the player
            else if(map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type == '@'){
                //THIS MIGHT NEED TO CHANGE DEPEDING ON WHAT THE CHARACTER WINNING A TRAINER BATTLE MEANS
                //Sets the next space to an impossible space as a flag for the trainer battle
                nextSpace.rowNum = -2;
                nextSpace.colNum = -2;
            }
            else{
                //Sets next space to the current space (Character won't move)
                nextSpace.rowNum = this->rowNum;
                nextSpace.colNum = this->colNum;
            }
        }

    }
    else{
        //Updates Next Space
        nextSpace.rowNum = this->rowNum + (this->direction.rowNum);
        nextSpace.colNum = this->colNum + (this->direction.colNum);
    }
    return nextSpace;
}

GameCharacter* Pacer::clone(){
    Pacer* temp = new Pacer(Point(this->rowNum,this->colNum),this->id);
    temp->direction = this->direction;
    return temp;
}

//CODE FOR WANDERERS ---------------------------------------------------
Point Wanderer::checkDirection(mapTile_t* map)
{
    //Stores the possible moves for the characters
    Point moveOptions[8] = {Point(-1,0),Point(-1,1),Point(0,1),Point(1,1),Point(1,0),Point(1,-1),Point(0,-1),Point(-1,-1)};

    return checkDirectionRec(map,moveOptions,8);
}


Point Wanderer::checkDirectionRec(mapTile_t* map, Point moveOptions[], int numOptions){
    Point nextSpace;

    //Checks to see if there is only one space left
    if(numOptions == 1){
        //If the remaining space is invalid
        if(map->mapArr[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)] != this->spawnBiome || map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type != 'X'){
            //Sets next space to the current space (Character won't move)
            nextSpace.rowNum = this->rowNum;
            nextSpace.colNum = this->colNum;
        }
        //Checks if the square is occupied by the player
        else if(map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type == '@'){
            //THIS MIGHT NEED TO CHANGE DEPEDING ON WHAT THE CHARACTER WINNING A TRAINER BATTLE MEANS
            //Sets the next space to an impossible space as a flag for the trainer battle
            nextSpace.rowNum = -2;
            nextSpace.colNum = -2;         
        }
        //If its free
        else{
            //Updates Next Space
            nextSpace.rowNum = this->rowNum + (this->direction.rowNum);
            nextSpace.colNum = this->colNum + (this->direction.colNum);
            return nextSpace;
        }
    }
    //Checks if the square is occupied by the player
    else if(map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type == '@'){
        //THIS MIGHT NEED TO CHANGE DEPEDING ON WHAT THE CHARACTER WINNING A TRAINER BATTLE MEANS
        //Sets the next space to an impossible space as a flag for the trainer battle
        nextSpace.rowNum = -2;
        nextSpace.colNum = -2;          
    }
    //If the current space is blocked or illegal
    else if(map->mapArr[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)] != this->spawnBiome || map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type != 'X'){

        //Randomly chooses a new direction to move in 
        int moveNum = rand() % numOptions;
        this->direction = moveOptions[moveNum];

        //Makes a new array to store moves
        Point newArr[numOptions -1];
        int tracker = 0; 

        //Adds all the moves except for the current one to the array
        for(int i =0; i < numOptions; i ++){
            if(i != moveNum){
                newArr[tracker] = moveOptions[i];
                tracker += 1;
            }
        }
        //Recursively call to verify new move or choose another
        nextSpace = checkDirectionRec(map,newArr,numOptions - 1);
    }
    //If the space is avaiable
    else{
        //Updates Next Space
        nextSpace.rowNum = this->rowNum + (this->direction.rowNum);
        nextSpace.colNum = this->colNum + (this->direction.colNum);
    }
    return nextSpace;
}

GameCharacter* Wanderer::clone(){
    Wanderer* temp = new Wanderer(Point(this->rowNum,this->colNum),this->spawnBiome,this->id);
    temp->direction = this->direction;
    temp->spawnBiome = this->spawnBiome;
    return temp;
}

//CODE FOR EXPLORERS ---------------------------------------------------

Point Explorer::checkDirection(mapTile_t* map)
{
    //Stores the possible moves for the characters
    Point moveOptions[8] = {Point(-1,0),Point(-1,1),Point(0,1),Point(1,1),Point(1,0),Point(1,-1),Point(0,-1),Point(-1,-1)};

    return checkDirectionRec(map,moveOptions,8);
}

Point Explorer::checkDirectionRec(mapTile_t* map, Point moveOptions[], int numOptions){
    Point nextSpace;

    std::string illegalChars = "~%% ";
    //Checks to see if there is only one space left
    if(numOptions == 1){
        //If the remaining space is invalid
        if(illegalChars.find(map->mapArr[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)]) != std::string::npos || map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type != 'X'){
            //Sets next space to the current space (Character won't move)
            nextSpace.rowNum = this->rowNum;
            nextSpace.colNum = this->colNum;
        }
        //Checks if the square is occupied by the player
        else if(map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type == '@'){
            //THIS MIGHT NEED TO CHANGE DEPEDING ON WHAT THE CHARACTER WINNING A TRAINER BATTLE MEANS
            //Sets the next space to an impossible space as a flag for the trainer battle
            nextSpace.rowNum = -2;
            nextSpace.colNum = -2;         
        }
        //If its free
        else{
            //Updates Next Space
            nextSpace.rowNum = this->rowNum + (this->direction.rowNum);
            nextSpace.colNum = this->colNum + (this->direction.colNum);
            return nextSpace;
        }
    }
    //Checks if the square is occupied by the player
    else if(map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type == '@'){
        //THIS MIGHT NEED TO CHANGE DEPEDING ON WHAT THE CHARACTER WINNING A TRAINER BATTLE MEANS
        //Sets the next space to an impossible space as a flag for the trainer battle
        nextSpace.rowNum = -2;
        nextSpace.colNum = -2;          
    }
    //If the current space is blocked or illegal
    else if(illegalChars.find(map->mapArr[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)]) != std::string::npos|| map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type != 'X'){

        
        //Randomly chooses a new direction to move in 
        int moveNum = rand() % numOptions;
        this->direction = moveOptions[moveNum];

        //Makes a new array to store moves
        Point newArr[numOptions -1];
        int tracker = 0; 

        //Adds all the moves except for the current one to the array
        for(int i =0; i < numOptions; i ++){
            if(i != moveNum){
                newArr[tracker] = moveOptions[i];
                tracker += 1;
            }
        }
        //Recursively call to verify new move or choose another
        nextSpace = checkDirectionRec(map,newArr,numOptions - 1);
    }
    //If the space is avaiable
    else{
        //Updates Next Space
        nextSpace.rowNum = this->rowNum + (this->direction.rowNum);
        nextSpace.colNum = this->colNum + (this->direction.colNum);
    }
    return nextSpace;
}

GameCharacter* Explorer::clone(){
    Explorer* temp = new Explorer(Point(this->rowNum,this->colNum),this->id);
    temp->direction = this->direction;
    return temp;
}

//CODE FOR SWIMMERS ---------------------------------------------------
Point Swimmer::checkDirection(mapTile_t* map)
{   
    if(map->mapInfo.playerByWater == 0){
        //Stores the possible moves for the characters
        Point moveOptions[8] = {Point(-1,0),Point(-1,1),Point(0,1),Point(1,1),Point(1,0),Point(1,-1),Point(0,-1),Point(-1,-1)};

        return checkDirectionRec(map,moveOptions,8);
    }
    else{
        return checkDirectionCharge(map);
    }

}

Point Swimmer::checkDirectionRec(mapTile_t* map,Point moveOptions[], int numOptions){
    Point nextSpace;
    std::string illegalChars = "CM#\"%%.: ";

    //Checks to see if there is only one space left
    if(numOptions == 1){
        //If the remaining space is invalid
        if(illegalChars.find(map->mapArr[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)]) != std::string::npos|| map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type != 'X'){
            //Sets next space to the current space (Character won't move)
            nextSpace.rowNum = this->rowNum;
            nextSpace.colNum = this->colNum;
        }
        //If its free
        else{
            //Updates Next Space
            nextSpace.rowNum = this->rowNum + (this->direction.rowNum);
            nextSpace.colNum = this->colNum + (this->direction.colNum);
            return nextSpace;
        }
    }
    //If the current space is blocked or illegal
    else if(illegalChars.find(map->mapArr[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)]) != std::string::npos|| map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type != 'X'){
        //Randomly chooses a new direction to move in 
        int moveNum = rand() % numOptions;
        this->direction = moveOptions[moveNum];

        //Makes a new array to store moves
        Point newArr[numOptions -1];
        int tracker = 0; 

        //Adds all the moves except for the current one to the array
        for(int i =0; i < numOptions; i ++){
            if(i != moveNum){
                newArr[tracker] = moveOptions[i];
                tracker += 1;
            }
        }
        //Recursively call to verify new move or choose another
        nextSpace = checkDirectionRec(map,newArr,numOptions - 1);
    }
    //If the space is avaiable
    else{
        //Updates Next Space
        nextSpace.rowNum = this->rowNum + (this->direction.rowNum);
        nextSpace.colNum = this->colNum + (this->direction.colNum);
    }
    return nextSpace;
}


Point Swimmer::checkDirectionCharge(mapTile_t* map){
    Point nextSpace;
    std::string illegalChars = "#\"%%.: ";
    this->direction.rowNum = (map->mapInfo.playerLocation.rowNum - this->rowNum ) / abs(map->mapInfo.playerLocation.rowNum - this->rowNum );
    this->direction.colNum = (map->mapInfo.playerLocation.colNum - this->colNum ) / abs(map->mapInfo.playerLocation.colNum - this->colNum );

    //If the swimmer can move in the direction of the player
    if(illegalChars.find(map->mapArr[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)]) == std::string::npos && map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type == 'X'){
        //Updates Next Space
        nextSpace.rowNum = this->rowNum + (this->direction.rowNum);
        nextSpace.colNum = this->colNum + (this->direction.colNum);
    }
    //Checks if the square is occupied by the player
    else if(map->mapInfo.charLocations[this->rowNum + (this->direction.rowNum)][this->colNum + (this->direction.colNum)].type == '@'){
        //THIS MIGHT NEED TO CHANGE DEPEDING ON WHAT THE CHARACTER WINNING A TRAINER BATTLE MEANS
        //Sets the next space to an impossible space as a flag for the trainer battle
        nextSpace.rowNum = -2;
        nextSpace.colNum = -2;           
    }
    //If it can't
    else{
        //Sets next space to the current space (Character won't move)
        nextSpace.rowNum = this->rowNum;
        nextSpace.colNum = this->colNum;
    }
    return nextSpace;
}

GameCharacter* Swimmer::clone(){
    Swimmer* temp = new Swimmer(Point(this->rowNum,this->colNum),this->id);
    temp->direction = this->direction;
    return temp;
}

//CODE FOR PATHFINDING ALGORITHMS ---------------------------------------------------

/**
 * @brief Generates an array with the distances from every square to the player for a hiker NPC
 * 
 * @param map To map to find the distances for
 * @param player The player struct with the PCs location
 * @param dist Array to store the tiles distances in 
 */
void dijkstraPathfindHiker(mapTile_t map, GameCharacter player,int dist[21][80]){
    //Creates the necessary array
    int mapSize = 1482;
    dist[player.getRowNum()][player.getColNum()] = 0;
    
    //Creates Priority Queue
    Queue priQueue = Queue(mapSize);
    
    Point temp;

    //Puts all the points into the Queue 
    for(int i=1; i< 20; i++){
        for(int j=1; j< 79; j++){
 
            temp.rowNum = i;
            temp.colNum = j;

            if(i != player.getRowNum() || j != player.getColNum()){
                dist[i][j] =  __INT_MAX__ - 500000;
            }
            if(map.mapArr[i][j] != '~'){
                
                priQueue.addWithPriority(&temp,dist[i][j]);
                
            }
            else{
                dist[i][j] =  -1;
            }
            
        }
    }

    int size = priQueue.getSize();
    
    while (size > 0){
        IDable* temp = priQueue.extractMin();
        Point* currEntry = dynamic_cast<Point*>(temp);
        

        Point currNeighbor;


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



            currNeighbor.rowNum = currEntry->rowNum + rowMod;      
            currNeighbor.colNum = currEntry->colNum +  colMod;

            //Make sure the current point is in the queue
            if(priQueue.checkInQueue(&currNeighbor) == 0){
                continue;
            }

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
            int altDist = dist[currEntry->rowNum][currEntry->colNum] + currMod;
            
            if (altDist < dist[currNeighbor.rowNum][currNeighbor.colNum]){
                dist[currNeighbor.rowNum][currNeighbor.colNum] = altDist; 

                priQueue.decreasePriority(&currNeighbor, altDist);
            }
        }
      
                

    size = priQueue.getSize();
    delete currEntry;
    }
    //delete priQueue;             
} 


//CODE FOR PATHFINDERS ---------------------------------------------------

/**
 * @brief Generates an array with the distances from every square to the player for a rival NPC
 * 
 * @param map To map to find the distances for
 * @param player The player struct with the PCs location
 * @param dist Array to store the tiles distances in 
 */
void dijkstraPathfindRival(mapTile_t map, GameCharacter player,int dist[21][80]){
//Creates the necessary array
    int mapSize = 1482;
    dist[player.getRowNum()][player.getColNum()] = 0;
    
    //Creates Priority Queue
    Queue priQueue = Queue(mapSize);

    Point temp;

    //Puts all the points into the Queue 
    for(int i=1; i< 20; i++){
        for(int j=1; j< 79; j++){
 
            temp.rowNum = i;
            temp.colNum = j;

            if(i != player.getRowNum() || j != player.getColNum()){
                dist[i][j] =  __INT_MAX__ - 500000;
            }
            if(map.mapArr[i][j] != '~' && map.mapArr[i][j] != '%' && map.mapArr[i][j] != '\"'){

                priQueue.addWithPriority(&temp,dist[i][j]);

            }
            else{
                dist[i][j] =  -1;
            }
            
        }
    }

    int size = priQueue.getSize();
    
    while (size > 0){
        IDable* temp = priQueue.extractMin();
        Point* currEntry = dynamic_cast<Point*>(temp);

        Point currNeighbor;


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



            currNeighbor.rowNum = currEntry->rowNum + rowMod;      
            currNeighbor.colNum = currEntry->colNum +  colMod;

            if(priQueue.checkInQueue(&currNeighbor) == 0){
                continue;
            }


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
            int altDist = dist[currEntry->rowNum][currEntry->colNum] + currMod;
            
            if (altDist < dist[currNeighbor.rowNum][currNeighbor.colNum]){
                dist[currNeighbor.rowNum][currNeighbor.colNum] = altDist; 

                priQueue.decreasePriority(&currNeighbor, altDist);
            }
        }
      
                

    size = priQueue.getSize();
    delete currEntry;
    }
    //queueDestroy(&priQueue);                     
} 



//NOTE TO SELF MAYBE REDO THIS WITH VECTOR LATER ***************
int Pathfinder::getPossibleMoves(mapTile_t map, Point* possibleMoves){
     //Stores the current number of added points
     int tracker = 0;
     
    //Loops through all the possible increments that can find the points neighbors
     for(int i=-1; i < 2; i++){
        for(int j=-1; j < 2; j++){

            //Skips if both are zero (This is the same location as the character which is being moved)
            if((i == 0 && j == 0) ||  this->rowNum + i == 0 || this->rowNum + i == 20 || this->colNum + j == 0 || this->rowNum + j == 79){
                continue;
            }

            int dist;
            //Gets the distance of the current neighbor
            if(this->type == 'h'){
                dist = map.mapInfo.hikerDist[this->rowNum + i][this->colNum + j];
            }
            else{
                dist = map.mapInfo.rivalDist[this->rowNum + i][this->colNum + j];
            }
            

            //If the space is reachable (-1 represents terrain which cannot be traversed)
            if(dist != -1){

                //Creates a point for the current neighbor
                Point newPos;
                newPos.rowNum = this->rowNum + i;
                newPos.colNum = this->colNum + j;

                //Adds the new point to the end of the array 
                possibleMoves[tracker] = newPos;

                //Sets up a tracker varaible to sort the array with 
                int shift = tracker - 1;

                //Increments number of stores elements by one
                tracker += 1;

                //Moves the new point down the array unti its in a sorted position. (Functionally this is a single pass of insertion sort)
                while(shift >= 0){

                    int prevDist;

                    if(this->type == 'h'){
                        prevDist = map.mapInfo.hikerDist[possibleMoves[shift].rowNum][possibleMoves[shift].colNum];
                    }
                    else{
                        prevDist = map.mapInfo.rivalDist[possibleMoves[shift].rowNum][possibleMoves[shift].colNum];
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
 * @brief Moves a given hiker or rival character on the map
 * 
 * @param toMove Pointer to the hiker to move
 * @param mapInfo NPC info for the current map tile
 */
char Pathfinder::move(mapTile_t* map){
    //Gets the squares it could move to ordered by distance
    Point possibleMoves[8];
    int numMoves = getPossibleMoves(*map,possibleMoves);
    //Creates a point to store the best move in
    Point bestMove;
    bestMove.rowNum = -1;
    bestMove.colNum = -1;

    //Gets the move with the least distance that isnt occupied by a character
    for(int i =0; i < numMoves; i++){
        Point currBestMove = possibleMoves[i];
        if(map->mapInfo.charLocations[currBestMove.rowNum][currBestMove.colNum].type == 'X'){
            bestMove.rowNum = currBestMove.rowNum;
            bestMove.colNum = currBestMove.colNum;
            i += 8;
        }
        //Checks if the square is occupied by the player
        else if(map->mapInfo.charLocations[currBestMove.rowNum][currBestMove.colNum].type == '@'){
            printMapWithChars(map,map->mapInfo);
            trainerBattle(*this,map);
            //THIS MIGHT NEED TO CHANGE DEPEDING ON WHAT THE CHARACTER WINNING A TRAINER BATTLE MEANS
            //Returns the current space
            return map->mapArr[this->rowNum][this->colNum];        
    }
    }

    //Returns if there is no possible move (This should be rare if not impossible)
    if(bestMove.rowNum == -1){
        //printf("HERE");
        return map->mapArr[this->rowNum][this->colNum];  
    }
    //Hold player location
    Point temp = Point(this->rowNum,this->colNum);

    //Changes the characters location within its struct
    this->rowNum = bestMove.rowNum; 
    this->colNum = bestMove.colNum;

    //Moves the character inside the character location array
    map->mapInfo.charLocations[temp.rowNum][temp.colNum] = GameCharacter();
    map->mapInfo.charLocations[bestMove.rowNum][bestMove.colNum] = *this;



    return map->mapArr[bestMove.rowNum][bestMove.colNum];    
}

GameCharacter* Pathfinder::clone(){
    Pathfinder* temp = new Pathfinder(Point(this->rowNum,this->colNum),this->type,this->id);
    return temp;
}



int checkPlayerByWater(GameCharacter player, mapTile_t map){
    //Checks all adjacent squars
    if(map.mapArr[player.getRowNum()][player.getColNum()] == '~' || map.mapArr[player.getRowNum() ][player.getColNum()] == '=' || map.mapArr[player.getRowNum() - 1][player.getColNum()] == '~' || map.mapArr[player.getRowNum() - 1][player.getColNum()] == '=' || map.mapArr[player.getRowNum() + 1][player.getColNum()] == '~' || map.mapArr[player.getRowNum() + 1][player.getColNum()] == '=' || map.mapArr[player.getRowNum()][player.getColNum() - 1] == '~' || map.mapArr[player.getRowNum()][player.getColNum() - 1] == '=' || map.mapArr[player.getRowNum() ][player.getColNum() + 1] == '~' || map.mapArr[player.getRowNum()][player.getColNum() + 1] == '='){
        return 1;
    }
    else{
        return 0;
    }
}

int moveGameChar(GameCharacter* toMove, int time, GameCharacter* player, mapTile_t* map){
    //Checks if this npc has been defeated
    if(checkTrainerDefeated(toMove->getID(),map->mapInfo) == 1){
        //Return a defeated flag
        return -2;
    }
    //If the player has moved
    if(map->mapInfo.playerLocation.rowNum != player->getRowNum() || map->mapInfo.playerLocation.colNum != player->getColNum()){ 
        //printf("HERE");
        //Redraw pathfinding maps
        dijkstraPathfindHiker(*map,*(player),map->mapInfo.hikerDist);
        dijkstraPathfindRival(*map,*(player),map->mapInfo.rivalDist);

        //Change last known player location
        map->mapInfo.playerLocation.rowNum = player->getRowNum();
        map->mapInfo.playerLocation.colNum = player->getColNum();

        //Check if the player is adjacent to water
        map->mapInfo.playerByWater = checkPlayerByWater(*player,*map);
    }

    //Perform the move
    char moveType;

    switch(toMove->type){
        case 'p':
        {
            Pacer* moveAs = dynamic_cast<Pacer*>(toMove);
            moveType = moveAs->move(map);
            break;
        }
        case 'w':
        {
            Wanderer* moveAs = dynamic_cast<Wanderer*>(toMove);
            moveType = moveAs->move(map);
            break;
        }
        case 'e':
        {
            Explorer* moveAs = dynamic_cast<Explorer*>(toMove);
            moveType = moveAs->move(map);
            break;
        }             
        case 'm':
        {
            Swimmer* moveAs = dynamic_cast<Swimmer*>(toMove);
            moveType = moveAs->move(map);
            break;
        }
        case 'r':
        case 'h':
        {
            Pathfinder* moveAs = dynamic_cast<Pathfinder*>(toMove);
            moveType = moveAs->move(map);
            break;
        }
        case '@':
        {
            Player* moveAs = dynamic_cast<Player*>(toMove);
            moveType = moveAs->move(map);
            break;
        }
        default:
            moveType = toMove->move(map);
            break;
    }
    if(moveType == 'Q'){
        return -1;
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
    
    return moveCost;
}



NPCMapInfo::NPCMapInfo(int numNPCs){
    
    //Sets the number of NPCs
    this->numNPCs = numNPCs;
    
    //Sets up defeated trainers array 
    this->defTrainers = (int*)malloc(sizeof(int) * numNPCs);

    //Initalized numDef
    this->numDef = 0;

    //Sets the player location as an unreachable tile so it will be updated when the game starts running
    this->playerLocation.rowNum = -1;
    this->playerLocation.colNum = -1;

    //Fills the NPC positions array with Empty Character markers
    for(int i =0; i< 21; i++){
        for(int j =0; j < 80; j++){
            this->charLocations[i][j] = GameCharacter();
        }
    }
}



/*
NPCMapInfo::~NPCMapInfo(){
    free(defTrainers);
}
*/

GameCharacter::GameCharacter(Point startLoc, char type, int id){

    this->rowNum = startLoc.rowNum;
    this->colNum = startLoc.colNum;
    this->type = type;
    this->id = id;

}

GameCharacter::GameCharacter(){

    this->rowNum = -1;
    this->colNum = -1;

    this->type = 'X';
    this->id = -1;

}

int checkTrainerDefeated(int id,NPCMapInfo mapInfo){
    for(int i =0; i < mapInfo.numDef; i++){
        if(mapInfo.defTrainers[i] == id){
            return 1;
        }
    }
    return 0;
}


GameCharacter* GameCharacter::clone(){
    GameCharacter* temp = new GameCharacter(Point(this->rowNum,this->colNum),this->type,this->id);
    return temp;
}


//MISC---------------------------------------------------

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

