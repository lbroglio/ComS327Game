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
        class PlayerInventory {
            public:
                int pokeBalls;
                int potions;
                int revives;
                PlayerInventory();
        };
    private:
        /**
         * @brief Moves the player character on the map based on user input
         * 
         * @param move The move to make
         * @param map The map to move on
         * @return The type of move made
         */
        char movePlayerInMap(playerMoves_t playerMove,mapTile_t* map);
        /**
         * @brief The players inventory of usable items
         * 
         */
        PlayerInventory inventory;
        /**
         * @brief Flag for if the player has lost a pokemon battle
         * 0 means it hasn't been. 1 means it has
         */
        int defeatedFlag = 0;
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
         * @brief Sets the defeated flag to one
         * 
         */
        void defeat(){defeatedFlag = 1;}
        /**
         * @brief Sets the defeated flag to zero
         *
         * 
         */
        void resetDefeat(){defeatedFlag = 0;}
        /**
         * @brief Returns the defeated flag
         *  0 means it hasn't been. 1 means it has
         * 
         * @return The defeated flag
         */
        int getDefeated(){return defeatedFlag;}
        /**
         * @brief Removes a pokeball from the players inventory
         * 
         */
        void usePokeball(){inventory.pokeBalls -= 1;}
        /**
         * @brief Creates a copy of this Character
         * Includes memory allocation returned to the user 
         * 
         * @return A pointer to the created copy
         */
        virtual GameCharacter* clone();

    /**
     * @brief Displays the interface for interacting with an inventory and using items
     * 
     * @param inventory The inventory to interact with
     * 
     * @return Indicator for what kind of item was used. 1 for Pokeball - -1 for no item 
     */
    friend int inventoryInterface(Player* player);
    /**
     * @brief Handles the interface and logic for using a potion item
     * 
     * @param player Pointer to the player
     * @return Indicator for it an item has been used. 1 if it has 0 if it hasnt
     */
    friend int usePotion(Player* player);
    /**
     * @brief Handles the interface and logic for using a revive item
     * 
     * @param player Pointer to the player
     * @return Indicator for it an item has been used. 1 if it has 0 if it hasnt
     */
    friend int useRevive(Player* player);
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

/**
 * @brief Hanldes the interface and logic for swapping a new pokemon
 * 
 * @param player Pointer to the player object holding the pokemon
 * @return The number of pokemon to swap in or -1 if none is
 */
int pokemonInterface(Player* player);

#endif