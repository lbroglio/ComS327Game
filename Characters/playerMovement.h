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
    QUIT,
    FLY
}playerMoves_t;


/**
 * @brief Object that holds the information for the player character
 * 
 */
class Player : public GameCharacter
{   
    private:
        /**
         * @brief Moves the player character on the map based on user input
         * 
         * @param move The move to make
         * @param map The map to move on
         * @return The type of move made
         */
        char movePlayerInMap(playerMoves_t playerMove,mapTile_t* map);

    public:
        /**
         * @brief Construct a new Player object
         * 
         * @param startLoc The starting location of the player
         */
        Player(Point startLoc) : GameCharacter(startLoc,'@',0){}

        /**
         * @brief Moves the player. Handles taking in input and making the corrsponding game state changes
         * 
         * @param map The map this character is on
         * @return Char for the type of move (What biome) 
         */
        char move(mapTile_t* map);

        /**
         * @brief Creates a copy of this Character
         * Includes memory allocation returned to the user 
         * 
         * @return A pointer to the created copy
         */
        virtual GameCharacter* clone();
};


/**
 * @brief Handles the players turn. Handles taking input and changing the game state / interacting with player accordingly
 * 
 * @param player The player to move
 * @param map The map to move across
 * @param mapInfo Info struct for the map
 * @return The cost of the palyer's move
 */
int playerTurn(GameCharacter* player, mapTile_t map);

/**
 * @brief Prompts the player to choose there starter pokemon and gives it to them
 * 
 * @param player Pointer to the player object
 * @param map Pointer to the map the player is on
 */
void chooseStarter(GameCharacter* player,mapTile_t* map);


#endif