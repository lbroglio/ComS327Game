#include<stdio.h>
#include"biome.h"

Biome::Biome(char type, int rowRange, int rowMin, int colRange, int colMin){
    
    this->type = type;
    this->cenRowNum = (rand() % rowRange) + rowMin;
    this->cenColNum = (rand() % colRange) + colMin;

    this->radius = 0;


}

