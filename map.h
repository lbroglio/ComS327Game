#ifndef MAP_H
#define MAP_H


/**
 * @brief Holds the map tile.
 * 
 */
typedef struct mapTile{
    /**2D array of chars that holds the map*/
    char mapArr[21][80];
    /**Stores the symbol of the dominant biome of this map*/
    char mapType;
    /**Determines how mountains are on this map. 0 means a normal biome, 1 means a range, 2 means no mountains*/
    int mountainRegion;
    /**Determines how water is on this map. 0 means a normal biome, 1 a river one char wide, 2 a river two chars wide*/
    int waterRegion;
    /**Location of the entrance/ exit on the top*/
    int topEntLoc;
    /**Location of the entrance/ exit on the bottom*/
    int bottomEntLoc;
    /**Location of the entrance/ exit on the left*/
    int leftEntLoc;
    /**Location of the entrance/ exit on  the right*/
    int rightEntLoc;
}mapTile_t;

/**
 * @brief Stores a point on the map
 * 
 */
typedef struct mapPoint{
    int rowNum;
    int colNum;
} point_t;


/**
 * @brief 
 * 
 * @param type 
 * @param worldMap 
 * @param worldRow 
 * @param worldCol 
 * @return mapTile_t 
 */
mapTile_t mapInit(char type,mapTile_t** worldMap, int worldRow, int worldCol);


/**
 * @brief Prints out a map to the console
 * 
 * @param map The map to print
 */
void printMap(mapTile_t* map);

#endif