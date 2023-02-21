#ifndef MAP_GEN
#define MAP_GEN

#include"map.h"
#include"worldGeneration.h"

/**
 * @brief Creates a new tile to be placed on the map
 * 
 * @param worldMap The struvt representing the existing tiles on the map
 * @param worldRow The row location in the worldMap Array
 * @param worldCol The column location in the worldMap Array
 * @return The newly created map tile
 */
mapTile_t createMapTile(worldMap_t worldMap, int worldRow, int worldCol);


/**
 * @brief Creates a map tile which exists independant of a greater world map. 
 * Will always have all four gates and buildings
 * Meant for testing
 * 
 * @return The created map tile 
 */
mapTile_t createMapTileIndependent();

/**
 * @brief Converts a point to an ID and then downshifts it to be used as its location in arrays.
 * Invalid points return -1
 * 
 * @param toConvert The point to get the ID for
 * @return The downshifted ID
 */
int pointToLocID(void* toConvert);

#endif