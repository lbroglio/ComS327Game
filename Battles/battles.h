#ifndef BATTLES_H
#define BATTLES_H

#include"../Characters/gameCharacter.h"

/**
 * @brief Handles interface and logic for trainer battles.
 * Battles are a placeholder right now
 * 
 * 
 * @param enemyTrainer The enenmy trainer object
 * @param map The map the player/trainer is on
 */
void trainerBattle(GameCharacter player, GameCharacter enemyTrainer,mapTile_t* map);


#endif