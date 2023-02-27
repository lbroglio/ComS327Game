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



mapTile_t mapTileInit(char type, int topEnt, int bottomEnt, int leftEnt, int rightEnt){
    mapTile_t toReturn;
    
    toReturn.topEntLoc = topEnt;
    toReturn.bottomEntLoc =  bottomEnt;
    toReturn.leftEntLoc = leftEnt;
    toReturn.rightEntLoc =  rightEnt;


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

void mapTileDestroy(mapTile_t* map){
    free(map->biomeArr);
}

point_t pointInit(int row, int col){
    point_t toReturn;
    toReturn.rowNum = row;
    toReturn.colNum = col;
    return toReturn;
}