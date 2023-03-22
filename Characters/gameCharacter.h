#ifndef CHARACTER_H
#define CHARACTER_H

#include"../Map/map.h"
#include"../Data-Structures/priorityQueue.h"

/**
 * @brief Stores information about the a character
 */
typedef struct gameCharacter{
    /** Row this character is in*/
    int rowNum;
    /** Columns this character is in*/
    int colNum;
    /** Char represneting what type of NPC (or player character) this character is*/
    char type;
    /** Unique id used for indexing this character*/
    int id;
    /** Stores the current direction this character is moving in as a unit vector. Not used by all character types */
    point_t direction;
    /** Stores the biome this character spawned in. Set for all only used by Wanderer*/
    char spawnBiome;
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
    character_t charLocations[21][80];
    /**Indicator of whether or not the player is by water. 1 = true, 0  = false*/
    int playerByWater;
    /**Stores the number of NPCs on this map*/
    int numNPCs;
    /**Stores the ids of trainers who have been defeated*/
    int* defTrainers;
    /**Stores the number of defeated trainer*/
    int numDef;

} nMapInfo_t;


/**
 * @brief Performs the next move in the game. - Takes the given character and handles the logic for moving it
 * 
 * @param toMove Pointer to the character to move 
 * @param time The time of the current move
 * @param player Pointer to the struct containing the information about the player
 * @param map The map tile that the player is currently on
 * @param mapInfo Pointer to the struct which hold the information about NPC's on this map
 * @return The cost of the move the npc made
 */

int moveNPC(character_t* toMove, int time, character_t* player, mapTile_t map, nMapInfo_t* mapInfo);

/**
 * @brief Creates a new npcMapInfpo struct
 * 
 * @param numNPCs The number of NPCs on this map
 * @return The created struct
 */
nMapInfo_t npcMapInfoInit(int numNPCs);

/**
 * @brief Creates a new character struct
 * 
 * @param startLoc point the character is at
 * @param type The type of character it is
 * @param id The id to assign it
 * @param spawnBiome The biome this character spawns in
 * @return The newly created character
 */
character_t characterInit(point_t startLoc, char type, int id, char spawnBiome);

/**
 * @brief Destoys the given nMapInfo struct and frees its allocated memory
 * 
 * @param toDestroy The struct to destroy
 */
void npcMapInfoDestroy(nMapInfo_t toDestroy);

/**
 * @brief Returns the ID of a given character 
 * 
 * @return The ID
 */
int getCharacterId(void* toId);

/**
 * @brief Returns the 'Empty' character
 * 
 * @return the 'Empty' character
 */
character_t getEmptyCharacter();


/**
 * @brief Checks to see if the trainer with the given ID has been defeated
 * 
 * @param id The id of the trainer to check
 * @param mapInfo The info struct for the current map
 * 
 * @return 0 if the trainer is not defeated. 1 if it is
 */
int checkTrainerDefeated(int id,nMapInfo_t mapInfo);

#endif
