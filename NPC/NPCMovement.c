#include<stdio.h>
#include<time.h>
#include"../Map/map.h"
#include"../Map/biome.h"
#include"../Map/mapGeneration.h"
#include"../Data-Structures/priorityQueue.h"
#include"../Player/Player.h"


/**
 * @brief Generates an array with the distances from every square to the player for a hiker NPC
 * 
 * @param map To map to find the distances for
 * @param player The player struct with the PCs location
 * @param dist Array to store the tiles distances in 
 */
void dijkstraPathfindHiker(mapTile_t map, player_t player,int dist[21][80]){
    //Creates the necessary array
    int mapSize = 1482;
    dist[player.rowNum][player.colNum] = 0;
    
    //Creates Priority Queue
    queue_t priQueue;
    queueInit(&priQueue,mapSize);

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
                queueAddWithPriority(&priQueue,temp,dist[i][j]);
            }
            else{
                dist[i][j] =  -1;
            }
            
        }
    }

    int size = queueSize(&priQueue);
    
    while (size > 0){
        point_t currEntry = queueExtractMin(&priQueue);

        point_t currNeighbor;


        //For Every neighbor
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
            if(checkInQueue(&priQueue,currNeighbor) == 0){
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
            int altDist = dist[currEntry.rowNum][currEntry.colNum] + currMod;
            
            if (altDist < dist[currNeighbor.rowNum][currNeighbor.colNum]){
                dist[currNeighbor.rowNum][currNeighbor.colNum] = altDist; 

                queueDecreasePriority(&priQueue,currNeighbor, altDist);
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
void dijkstraPathfindRival(mapTile_t map,  player_t player,int dist[21][80]){
    //Creates the necessary array
    int mapSize = 1482;
    dist[player.rowNum][player.colNum] = 0;
    
     //Creates Priority Queue
    queue_t priQueue;
    queueInit(&priQueue,mapSize);

    point_t temp;

     //Creates Priority Queue
    for(int i=1; i< 20; i++){
        for(int j=1; j< 79; j++){
 
            temp.rowNum = i;
            temp.colNum = j;

            if(i != player.rowNum || j != player.colNum){
                dist[i][j] =  __INT_MAX__ - 500000;
            }
            if(map.mapArr[i][j] != '~' && map.mapArr[i][j] != '%' && map.mapArr[i][j] != '\"'){
                queueAddWithPriority(&priQueue,temp,dist[i][j]);
            }
            else{
                dist[i][j] =  -1;
            }
            
        }
    }

    int size = queueSize(&priQueue);
    
    while (size > 0){
        point_t currEntry = queueExtractMin(&priQueue);

        point_t currNeighbor;



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



            currNeighbor.rowNum = currEntry.rowNum + rowMod;      
            currNeighbor.colNum = currEntry.colNum +  colMod;
            if(checkInQueue(&priQueue,currNeighbor) == 0){
                continue;
            }



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
            
            int altDist = dist[currEntry.rowNum][currEntry.colNum] + currMod;
            
            if (altDist < dist[currNeighbor.rowNum][currNeighbor.colNum]){
                dist[currNeighbor.rowNum][currNeighbor.colNum] = altDist; 

                queueDecreasePriority(&priQueue,currNeighbor, altDist);
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


int main(int argc, char* argv[]){
    srand(time(NULL));
    int hikerDist[21][80];
    int rivalDist[21][80];
    
    mapTile_t map = createMapTileIndependent();
    
    player_t player;
    player.colNum = ((map.biomeArr) + 1)->cenColNum;
    player.rowNum = ((map.biomeArr) + 1)->cenRowNum -1;
    map.mapArr[player.rowNum][player.colNum] = '@';

    dijkstraPathfindHiker(map,player,hikerDist);
    dijkstraPathfindRival(map,player,rivalDist);

    printMap(&map);
    printf("\n Hiker:\n");
    printDistArr(hikerDist);
    printf("\n Rival:\n");
    printDistArr(rivalDist);


}

 
