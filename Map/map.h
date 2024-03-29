#ifndef MAP_H
#define MAP_H

#include"biome.h"
#include"point.h"
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
    /**Stores the current Queue for this map*/
    Queue* eventManager;    
    /** Stores the current time as of when the player last left this map*/
    int savedTime;
    public:
        mapTile(){}
    
}mapTile_t;



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
void mapTileDestroy(mapTile_t* map);


/**
 * @brief Converts a given ID to its corresponding point
 * 
 * @param toConvert The ID to convert
 * @return The point 
 */
Point convertID(int toConvert);


#endif