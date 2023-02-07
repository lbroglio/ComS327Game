#ifndef MAP_GEN
#define MAP_GEN

#include"map.h"

/**
 * @brief Creates a new tile to be placed on the map
 * 
 * @param worldMap The array representing the existing tiles on the map
 * @param worldRow The row location in the worldMap Array
 * @param worldCol The column location in the worldMap Array
 * @return The newly created map tile
 */
mapTile_t createMapTile(mapTile_t** worldMap, int worldRow, int worldCol);



#endif