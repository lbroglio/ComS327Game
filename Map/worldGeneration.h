#ifndef WORLDGEN_H
#define WORLDGEN_H

#include"map.h"

/**
 * @brief Wrapper struct for the array holding all the tiles in the world map
 * 
 */
typedef struct worldMap{
    mapTile_t** worldArr;
    int placedArr[401][401];

}worldMap_t;


/**
 * @brief Creates a world map - Allocates all the memory for the tiles
 * 
 * @return The created worldMap
 */
worldMap_t worldMapInit();

/**
 * @brief Destorys a world map - Dellocates the memory
 * 
 * @param toDestroy The world map to destroy
 */
void worldMapDestroy(worldMap_t toDestroy);


#endif