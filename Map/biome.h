#ifndef BIOME_H
#define BIOME_H

#include<stdlib.h>

/**
 * @brief A struct data structure which holds information about a biome on the map
 * 
 */
struct Biome{
    int cenRowNum;
    int cenColNum;
    char type;
    int radius;

    /**
     * @brief Constructor for a biome object
     * 
     * @param type The type of biome to create
     * @param rowRange The range of possible random locations for the row the biome is in
     * @param rowMin The minimum possible random location for the row the biome is in
     * @param colRange The range of possible random locations for the column biome is in
     * @param colMin The minimum possible random location for the column biome is in
     * @return The newly created biome struct
     */
    Biome(char type, int rowRange, int rowMin, int colRange, int colMin);
};





#endif