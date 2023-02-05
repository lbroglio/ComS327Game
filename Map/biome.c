#include<stdio.h>
#include"biome.h"

biome_t biomeInit(char type, int rowRange, int rowMin, int colRange, int colMin){
    biome_t toReturn;
    
    toReturn.type = type;
    toReturn.cenRowNum = (rand() % rowRange) + rowMin;
    toReturn.cenColNum = (rand() % colRange) + colMin;

    toReturn.radius = 0;

    return toReturn;

}

