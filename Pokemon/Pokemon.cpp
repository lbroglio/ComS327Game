#include<string>
#include"../PokemonData/PokemonData.h"
#include"Pokemon.h"


int Pokemon::damage(int damageTaken){
    currentHP -= damageTaken;

    if(currentHP <= 0){
        currentHP = 0;
        hasFainted = 1;
        return 1;
    }
    else{
        return 0;
    }
}

void Pokemon::heal(int healthReturned){
    currentHP += healthReturned;
    if(currentHP > stats.HP){
        currentHP = stats.HP;
    }
}

void Pokemon::recover(){
    hasFainted =0;
    currentHP = stats.HP;
}

//To be implemented later
void levelUp();

Pokemon::PokemonStats::PokemonStats(int pokemonId){
    
}
Pokemon::PokemonStats::PokemonStats(int HPVal, int attackVal, int defenseVal, int speedVal, int sAttackVal, int sDefenseVal){

}


Pokemon::PokemonStats generateIVs(){
    return PokemonStats();
}


Pokemon::Pokemon(int givenID, int startingLevel) : stats(PokemonStats(givenID)), IVs(generateIVs()){
        level = startingLevel;
        this->pokemonID = pokemonID;

        int currentHP;
        int hasFainted;
        std::string name;
        std::string species;
        int pokemonID;
        Move moveList[4];
        int isShiny;

}