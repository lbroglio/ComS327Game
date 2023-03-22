#ifndef PLAYERM_H
#define PLAYERM_H

#include"gameCharacter.h"

typedef enum playerMoves{
    UP_LEFT,
    UP,
    UP_RIGHT,
    RIGHT,
    DOWN_RIGHT,
    DOWN,
    DOWN_LEFT,
    LEFT,
    REST,
    ENTER_BUILDING,
    QUIT
}playerMoves_t;


/**
 * @brief Handles the players turn. Handles taking input and changing the game state / interacting with player accordingly
 * 
 * @param player The player to move
 * @param map The map to move across
 * @param mapInfo Info struct for the map
 * @return The cost of the palyer's move
 */
int playerTurn(character_t* player, mapTile_t map,nMapInfo_t* mapInfo);

#endif