#ifndef POKEMON_H
#define POKEMON_H

#include<string>
#include<cstdlib>
#include"../PokemonData/PokemonData.h"

enum StatID{
    HP = 1,
    ATTACK,
    DEFENSE,
    SPEED,
    SPECIAL_ATTACK,
    SPECIAL_DEFENSE
};


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
            /**
             * @brief Construct a new Pokemon Stats object by pulling the base stats of the pokemon with the given id from the parsed data
             * 
             * @param pokemonId The id of the pokemon to pull stats from
             */
            PokemonStats(int pokemonID);
            /**
             * @brief Construct a new Pokemon Stats object by setting its values to the provided ones. Used for consturctiong IVs
             * 
             * @param HPVal The HP to set this to
             * @param attackVal The attack to set this to
             * @param defenseVal The defense to set this to
             * @param speedVal The speed to set this to
             * @param sAttackVal The special sttack to set this to
             * @param sDefenseVal The special defense to set this to
             */
            PokemonStats(int HPVal, int attackVal, int defenseVal, int speedVal, int sAttackVal, int sDefenseVal);
            PokemonStats(){}

            /**
             * @brief Adds two PokemonStats together by adding the individual stats
             * 
             * @param x The Stat struct to add to this one
             * @return Reference to the result of the additon
             */
            PokemonStats operator+(PokemonStats x);
            /**
             * @brief Adds a PokemonStat to this one by adding the individual stats
             * 
             * @param x The Stat struct to add to this one
             * @return Reference to the result of the additon
             */
            PokemonStats& operator+=(PokemonStats x);
            /**
             * @brief Gets string to display these stats to the screen
             * 
             * @return The display string
             */
            std::string getDisplayString();
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
        /** @brief  This kind of pokemon's ID*/
        int pokemonID;
        /** @brief  This kind of pokemon's species ID*/
        int speciesID;
        /** @brief  Stores the Base Stats of this pokemon*/
        PokemonStats baseStats;
        /** @brief  Stores the IVs of this poekmon*/
        PokemonStats IVs;
        /** @brief  Stores the stats of this pokemon*/
        PokemonStats stats;
        /** @brief  Stores the base(starting) stats of this pokemon*/
        /** @brief The moves this pokemon currently knows*/
        std::vector<Move> moveList;
        /** @brief  Stores a boolean for whether or not the Pokemon is shiny. 0 means it isn't shiny 1 means it is*/
        int isShiny;
        /** @brief  Stores the gener of this pokemon*/
        std::string gender;
        /** @brief  Stores the types of this pokemon*/
        std::vector<Type_Name> typeList;
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
         * @brief Bring a pokemon back if it has fainted and gives it half of its health
         * 
         */
        void revive();
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
        std::vector<Move> getMoves(){return moveList;}
        /**
         * @brief Get this pokemon's gender
         * 
         * @return The pokemons gender
         */
        std::string getGender(){return gender;}
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
         * @brief Get the list of types for this pokemon
         * 
         * @return std::vector<std::string> 
         */
        std::vector<Type_Name> getTypes(){return typeList;}
        /**
         * @brief Change this pokemons name
         * 
         * @param newName The new name to assign this Pokemon
         */
        void rename(std::string newName){name = newName;}
        /**
         * @brief Calculates the current stats for this Pokemon based on its current level and IVs. Changes the stats member accordingly
         * 
         */
        void updateStats();
        /**
        * @brief Gets string to display this pokemone to the screen
        * 
        * @return The display string
        */
        std::string getDisplayString();
        /**
        * @brief Gets stats string to display this pokmemon's stats to the screen
        * 
        * @return The stat's display string
        */
        std::string getStatsString(){return  this->stats.getDisplayString();}
        Pokemon(){}
        /**
         * @brief Construct a new Pokemon object at the given level
         * 
         * @param startingLevel The level this Pokemon is
         */
        Pokemon(int givenID, int startingLevel);
    /**
    * @brief Randomly Generates a set of IVs (Indivudal Values) for a pokemon
    * 
    * @return A Stats struct holding the generated IVs 
    */
    friend PokemonStats generateIVs();

    /**
    * @brief Prints a formated Pokemon object to the provided ostream
    * 
    * @param o The stream to print the class to
    * @param s The Pokemon to print
    * @return The stream with the class added
    */
    friend std::ostream &operator<<(std::ostream &o,  const Pokemon &s);
    /**
    * @brief Prints a formated PokemonStats object to the provided ostream
    * 
    * @param o The stream to print the class to
    * @param s The PokemonStats object to print
    * @return The stream with the class added
    */
    friend std::ostream &operator<<(std::ostream &o,  const PokemonStats &s);
    
};

/**
 * @brief Randomly creates new Pokemon based on the location in the world
 * 
 * 
 * @return The created pokemon 
 */
Pokemon getRandomPokemon();

/**
 * @brief Randomly creates new Pokemon based on a given level
 * 
 * @param level The level to make this pokemon
 * @return The created pokemon  
 */
Pokemon getRandomPokemon(int level);
#endif