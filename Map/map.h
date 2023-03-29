#ifndef MAP_H
#define MAP_H

#include"biome.h"
#include"../Data-Structures/priorityQueue.h"
#include"../Characters/NPCMapInfo.h"

/**
 * @brief Holds the map tile.
 * 
 */
typedef struct mapTile{
    /**2D array of chars that holds the map*/
    char mapArr[21][80];
    /**Array which stores the biome structs in this map*/
    Biome* biomeArr;
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
    /**The NPC info class for this map*/
    NPCMapInfo mapInfo;
    
}mapTile_t;


/**
 * @brief Stores a point on the map. Also used as unit vectors sometimes
 * 
 */
struct Point : public IDable{
    /**The row this point is in*/
    int rowNum;
    /**The column this point is in*/
    int colNum;
    /**
     * @brief Converts a point to an ID and then downshifts it to be used as its location in arrays.
     * Invalid points return -1
     * 
     * @param toConvert The point to get the ID for
     * @return The downshifted ID
     */
    int getID();

    /**
     * @brief Creates a copy of the point object.
     * Includes memory allocation returned to the user
     * 
     * @return A pointer to the created copy
     */
    Point* clone();
    /**
     * @brief Creates a new point struct with the given row and column
     * 
     * @param row The row the point is in
     * @param col The column the point is in
     * @return The newly created point
     */
    Point(int row, int col);
    /**
     * @brief Construct a new Point object
     * Default Constructor
     */
    Point();
    
    /**
    * @brief Converts a given point to its NONDOWNSHIFTEDinteger id
    * 
    * @param toConvert The point to convert
    * @return The ID 
    */
    int convertPoint(){ return (rowNum * 80) + colNum;}
};
 
//std::ostream &operator<<(std::ostream &o,  const Point &p);



/**
 * @brief Creates a new map tile
 * 
 * @param type The type of map this should be represented by the symbol of the dominant biome
 * @param topEnt The location of the top gate. 
 * @param bottomEnt The location of the bottom gate. 
 * @param leftEnt The location of the left gate.
 * @param rightEnt The location of the right gate.
 * @return The newly created map tile
 */
mapTile_t mapTileInit(char type, int topEnt, int bottomEnt, int leftEnt, int rightEnt);

/**
 * THIS IS DEPRECATED. IT'S NOT FIXED FOR CURSORS AND IT WON'T PRINT NPCs OR THE PLAYER
 * @brief Prints out a map to the console
 * 
 * @param map The map to print
 */
void printMap(mapTile_t* map);

/**
 * @brief Destroys a map tile freeing the memory inside it
 * 
 * @param map The map to destroy
 */
void mapTileDestory(mapTile_t* map);


/**
 * @brief Converts a given ID to its corresponding point
 * 
 * @param toConvert The ID to convert
 * @return The point 
 */
Point convertID(int toConvert);


#endif