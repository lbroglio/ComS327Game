#ifndef POKEMON_H
#define POKEMON_H

#include<string>
#include<cstdlib>
#include"../PokemonData/PokemonData.h"


class Pokemon{
    private:
        /**
         * @brief Stores value representing the stats of a pokemon or its IVs
         * 
         */
        struct PokemonStats{
            int HP;
            int attack;
            int defense;
            int speed;
            int specialAttack;
            int specialDefense;
            PokemonStats(int pokemonId);
            PokemonStats(int HPVal, int attackVal, int defenseVal, int speedVal, int sAttackVal, int sDefenseVal);
        };
    private:
        /** @brief  The current HP this pokemon has*/
        int currentHP;
        /** @brief  This Pokemon's level*/
        int level;
        /** @brief  Stores a boolean for whether or not the Pokemon has fainted. 1 means it has fainted 0 means it hasn't*/
        int hasFainted;
        /** @brief  The user assigned name of this Pokemon*/
        std::string name;
        /** @brief  The species this pokemon belongs to (Pikachu, Charizard etc)*/
        std::string species;
        /** @brief  This type of pokemon's ID*/
        int pokemonID;
        /** @brief  Stores the stats of this pokemon*/
        PokemonStats stats;
        /** @brief  Stores the IVs of this poekmon*/
        PokemonStats IVs;
        /** @brief The moves this pokemon currently knows*/
        Move* moveList;
        /** @brief  Stores a boolean for whether or not the Pokemon is shiny. 0 means it isn't shiny 1 means it is*/
        int isShiny;
    public:
        /**
         * @brief Returns the number of Hit points this pokemon  has 
         * 
         * @return The value of currentHp
         */
        int getHealth(){return currentHP;}
        /**
         * @brief Removes the given amount from the pokemon health. Handles the pokemon fainting
         * 
         * @param damageTaken The damgage this pokemon has taken.
         * @return Indicator if the pokemon has fainted. Returns 1 if it has fainted 0 if it hasn't
         */
        int damage(int damageTaken);
        /**
         * @brief Restores the given amount of health to the pokemon. Won't heal over the max health.
         * 
         * @param healthReturned The health to return
         */
        void heal(int healthReturned);
        /**
         * @brief Completely restores this Pokemon's health and brings it back if it has fainted
         * 
         */
        void recover();
        /**
         * @brief Returns the boolean indicator for if this pokemon has fainted
         * 
         * @return Indicator for if the pokemon has fainted 1 if it has, 0 if it hasn't
         */
        int pokemonFainted(){return hasFainted;}
        /**
         * @brief Returns the name of this Pokemon
         * 
         * @return The name of the Pokemon 
         */
        std::string getName(){return name;}
        /**
         * @brief Returns this pokemons species
         * 
         * @return The species this Pokemon belongs too
         */
        std::string getSpecies(){return species;}
        /**
         * @brief Get the HP stat (Max HP) of this pokemon
         * 
         * @return The HP stat
         */
        int getHP(){return stats.HP;}
        /**
         * @brief Get the attack stat of this pokemon
         * 
         * @return The attack stat
         */
        int getattack(){return stats.attack;}
        /**
         * @brief Get the defense stat of this pokemon
         * 
         * @return The defense stat
         */
        int getDefense(){return stats.defense;}
        /**
         * @brief Get the speed stat of this pokemon
         * 
         * @return The speed stat
         */
        int getSpeed(){return stats.speed;}
        /**
         * @brief Get the special attack stat of this pokemon
         * 
         * @return The special attack stat
         */
        int getSpecialAttack(){return stats.HP;}
        /**
         * @brief Get the special defense stat of this pokemon
         * 
         * @return The special defense stat
         */
        int getSpecialDefense(){return stats.specialDefense;} 
        /**
         * @brief Get the list of moves this Pokemon knows
         * 
         * @return The list of moves
         */
        Move* getMoves(){return moveList;}
        /**
         * @brief Increases this Pokemon's level. Handles updating the Stats.
         * 
         */
        void levelUp();
        /**
         * @brief Returns the boolean for whether or not the Pokemon is shiny
         * 
         * @return 1 if it is shiny 0 is it isnt 
         */
        int pokemonShiny(){return isShiny;}
        /**
         * @brief Change this pokemons name
         * 
         * @param newName The new name to assign this Pokemon
         */
        void rename(std::string newName){name = newName;}
        /**
         * @brief Construct a new Pokemon object at the given level
         * 
         * @param startingLevel The level this Pokemon is
         */
        Pokemon(int givenID, int startingLevel);
        /**
         * @brief Destroy the Pokemon object
         * 
         */
        ~Pokemon(); 
    /**
    * @brief Randomly Generates a set of IVs (Indivudal Values) for a pokemon
    * 
    * @return A Stats struct holding the generated IVs 
    */
    friend PokemonStats generateIVs();
};

#endif