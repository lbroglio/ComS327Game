#ifndef BATTLES_H
#define BATTLES_H

#include"../Characters/gameCharacter.h"

/**
 * @brief Handles interface and logic for trainer battles.
 * 
 * @param player A pointer to the player
 * @param enemyTrainer The enenmy trainer object
 * @param map The map the player/trainer is on
 */
void trainerBattle(Player* player, GameCharacter enemyTrainer,mapTile_t* map);


/**
 * @brief Handles the interface and logic for a battle with a wild pokemon
 * 
 * @param player Pointer to the player
 * @param encounteredPokemon The pokemon the player encountered
 * @param map Pointer to the map the player is on
 */
void wildBattle(Player* player, Pokemon encounteredPokemon,mapTile_t* map);


#endif