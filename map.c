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
#define RESET "\x1B[0m"



mapTile_t mapInit(char type){
    mapTile_t toReturn;
    
    //Selects the locations of the entraces/ exits
    toReturn.topEntLoc = (rand() % 78) +1;
    toReturn.bottomEntLoc = (rand() % 78) +1;
    toReturn.leftEntLoc = (rand() % 19) +1;
    toReturn.rightEntLoc = (rand() % 19) +1;


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
            else{
                printf("%c ",toPrint);
            }
            
        }
        printf("\n");
    }
}