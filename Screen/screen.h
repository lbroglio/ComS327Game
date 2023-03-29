#ifndef SCREEN_H
#define SCREEN_H


#include<stdio.h>
#include"../Map/map.h"
#include"../Map/point.h"
#include"../Characters/gameCharacter.h"




/**
 * @brief Sets up the terminal
 * 
 */
void terminalInit();

/**
 * @brief Prints a map to the console with NPCS and the player character in the correct location
 * 
 * @param map The map to print
 * @param mapInfo The NPC information for the map
 */
void printMapWithChars(mapTile_t* map, NPCMapInfo mapInfo);


#endif