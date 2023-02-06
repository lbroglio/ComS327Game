#include<stdio.h>
#include<stdlib.h>
#include"map.h"


//Colors
#define GRN "\x1B[32m"
#define RED "\x1B[31m"
#define DRKYLLW "\x1B[38;5;58m"
#define FRSTGRN "\x1B[38;5;28m"
#define BLUE "\x1B[34m"
#define DRKBLUE "\x1B[38;5;17m"
#define GREY "\x1B[38;5;235m"
#define DSRTYLLW "\x1B[38;5;220m"
#define BROWN "\x1B[38;5;94m"
#define RESET "\x1B[0m"



mapTile_t mapInit(char type,mapTile_t** worldMap, int worldRow, int worldCol){
    mapTile_t toReturn;
    mapTile_t* neighbor;
    
    //Selects the locations of the entraces/ exits
    if(worldRow == 0){
        toReturn.topEntLoc = -1;
    }
    else{
        neighbor =  worldMap[worldRow - 1];

        if((neighbor + worldCol) != NULL){
            toReturn.topEntLoc = neighbor->bottomEntLoc;
        }
        else{
             toReturn.topEntLoc = (rand() % 78) +1;
        }
    }

    if(worldRow == 400){
        toReturn.bottomEntLoc = -1;
    }
    else{
        neighbor = worldMap[worldRow + 1];

        if((neighbor + worldCol) != NULL){
            toReturn.bottomEntLoc = neighbor->topEntLoc;
        }
        else{
             toReturn.bottomEntLoc = (rand() % 78) +1;
        }
    }

    if(worldCol == 0){
        toReturn.leftEntLoc = -1;
    }
    else{
        neighbor = worldMap[worldRow - 1];

        if((neighbor + worldCol) != NULL){
            toReturn.leftEntLoc = neighbor->rightEntLoc;
        }
        else{
             toReturn.leftEntLoc = (rand() % 78) +1;
        }
    }

    if(worldCol == 400){
        toReturn.rightEntLoc = -1;
    }
    else{
        neighbor = worldMap[worldRow + 1];

        if((neighbor + worldCol) != NULL){
            toReturn.rightEntLoc = neighbor->leftEntLoc;
        }
        else{
             toReturn.rightEntLoc = (rand() % 78) +1;
        }
    }


    //Draws the map
    for(int i = 0; i < 21; i++){
        for(int j = 0; j < 80;j ++){
            //Prints the edges of the map except at the entrnaces and exits
            if((i == 0 && j != toReturn.topEntLoc) || (j == 0 && i != toReturn.leftEntLoc) || (i == 20 && j != toReturn.bottomEntLoc) || (j == 79 && i != toReturn.rightEntLoc)){
                toReturn.mapArr[i][j] = '%';
                
            }
            //Adds a place holder for the body of the map
            else if(i != 0 && j != 0 && i != 20 && j != 79){
                toReturn.mapArr[i][j]= 'X';
            }
            //Space for edges
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
            else if(toPrint == '='){
                printf(BROWN "%c " RESET,toPrint);
            }
            else{
                printf("%c ",toPrint);
            }
            
        }
        printf("\n");
    }
}