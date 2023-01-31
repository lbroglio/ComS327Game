/**
 * @brief Holds the map tile.
 * 
 */
typedef struct mapTile{
    char mapArr[21][80];
    char mapType;
    int mountainRegion;
    int waterRegion;
    int topEntLoc;
    int bottomEntLoc;
    int leftEntLoc;
    int rightEntLoc;
}mapTile_t;


/**
 * @brief Creates a new map tile
 * 
 * @param type The type of map this is. Represente by the symbol of the dominant biome
 * 
 * @return The created map tile. It has the borders as rocks and all other spaces as X
 */
mapTile_t mapInit(char type);


/**
 * @brief Prints out a map to the console
 * 
 * @param map The map to print
 */
void printMap(mapTile_t* map);

