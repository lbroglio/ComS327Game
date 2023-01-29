#ifndef STACK_H
#define STACK_H

#include<stdlib.h>

/**
 * @brief A struct data structure which holds information about a biome on the map
 * 
 */
typedef struct biome{
    int cenRowNum;
    int cenColNum;
    char type;
    int radius;
}biome_t;

/**
 * @brief Creates a new biome struct with the given information.
 * 
 * @param type The type of biome to create
 * @param xRange The range of possible random locations for the x coordinate
 * @param xMin The minimum possible random location for the x coordinate
 * @param yRange The range of possible random locations for the y coordinate
 * @param yMin The minimum possible random location for the y coordinate
 * @return The newly created biome struct
 */
biome_t biomeInit(char type, int xRange, int xMin, int yRange, int yMin){
    biome_t toReturn;
    
    toReturn.type = type;
    toReturn.cenXLoc = (rand() % xRange) + xMin;
    toReturn.cenYLoc = (rand() % yRange) + yMin;

    toReturn.radius = 0;

    return toReturn;

}

#endif