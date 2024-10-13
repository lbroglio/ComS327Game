#ifndef NMAPINFO_H
#define NMAPINFO_H

#include"../Map/point.h"


class GameCharacter;

struct GameCharStorage{
    public:
        int id;
        char type;

        GameCharStorage(int id, char type){this->id = id; this->type = type;}
        /**
         * @brief Default constructor - NOOP
         * 
         */
        GameCharStorage(){}
};

/**
 * @brief Stores information about a map tile used by npcs
 * 
 */
class NPCMapInfo{
    public:
        /** Point on map representing last know location of the player on this map*/
        Point playerLocation;
        /** Stores the results of the hiker's pathfinding algorithm*/
        int hikerDist[21][80];
        /** Stores the results of the rival's pathfinding algorithm*/
        int rivalDist[21][80];
        /** Stores the location of the NPCs on the map X if none is there*/
        GameCharacter** charLocations;
        /**Indicator of whether or not the player is by water. 1 = true, 0  = false*/
        int playerByWater;
        /**Stores the number of NPCs on this map*/
        int numNPCs;
        /**Stores the ids of trainers who have been defeated*/
        int* defTrainers;
        /**Stores the number of defeated trainer*/
        int numDef;

        /**
         * @brief Creates a new npcMapInfpo struct
         * 
         * @param numNPCs The number of NPCs on this map
         * @return The created struct
         */
        NPCMapInfo(int numNPCs);
        /**
         * @brief Default constructor - NOOP
         * 
         */
        NPCMapInfo(){}

};

#endif