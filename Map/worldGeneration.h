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


#endif