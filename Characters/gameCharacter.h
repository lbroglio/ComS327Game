#ifndef CHARACTER_H
#define CHARACTER_H

/**
 * @brief Stores information about the a character
 */
typedef struct gameCharactor{
    /** Row this character is in*/
    int rowNum;
    /** Columns this character is in*/
    int colNum;
    /** Char represneting what type of NPC (or player character) this character is*/
    char type;
    /** Unique id used for indexing this character*/
    int id;

} character_t;


/**
 * @brief Stores information about a map tile used by npcs
 * 
 */
typedef struct npcMapInfo{
    /** Point on map representing last know location of the player on this map*/
    point_t playerLocation;
    /** Stores the results of the hiker's pathfinding algorithm*/
    int hikerDist[21][80];
    /** Stores the results of the rival's pathfinding algorithm*/
    int rivalDist[21][80];
    /** Stores the location of the NPCs on the map X if none is there*/
    char charLocations[21][80];
} nMapInfo_t;

/**
 * @brief Creates a new npcMapInfpo struct
 * 
 * @return The created struct
 */
nMapInfo_t npcMapInfoInit();





#endif
