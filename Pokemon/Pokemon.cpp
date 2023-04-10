#include<string>
#include<vector>
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

Pokemon::PokemonStats::PokemonStats(int pokemonID){
    int i;
    int statsSet = 0;
    //Get all the stats for pokemon 
    for(i=0; i < pokeData->pokemon_stats.size() || statsSet == 6; i++){
        Pokemon_Stat temp = pokeData->pokemon_stats[i];
        //If the stat is for this pokemon
        if(temp.pokemon_id() == pokemonID){
            switch (temp.stat_id())
            {
            //Set the value based on which stat it is
            case StatID::HP:
                this->HP = temp.base_stat();
                statsSet++;
                break;
            case StatID::ATTACK:
                this->attack = temp.base_stat();
                statsSet++;
                break;
            case StatID::DEFENSE:
                this->defense = temp.base_stat();
                statsSet++;
                break;
            case StatID::SPEED:
                this->speed = temp.base_stat();
                statsSet++;
                break;
            case StatID::SPECIAL_ATTACK:
                this->specialAttack = temp.base_stat();
                statsSet++;
                break;
            case StatID::SPECIAL_DEFENSE:
                this->specialDefense = temp.base_stat();
                statsSet++;
                break;
            }
        }
    }
}

Pokemon::PokemonStats::PokemonStats(int HPVal, int attackVal, int defenseVal, int speedVal, int sAttackVal, int sDefenseVal){
    this->HP = HPVal;
    this->attack = attackVal;
    this->defense = defenseVal;
    this->speed = speedVal;
    this->specialAttack = sAttackVal;
    this->specialDefense = sDefenseVal;
}

Pokemon::PokemonStats& Pokemon::PokemonStats::operator+(Pokemon::PokemonStats x){
    PokemonStats temp;
    temp.HP = this->HP + x.HP;
    temp.attack = this->attack + x.attack;
    temp.defense = this->defense + x.defense;
    temp.speed = this->speed + x.speed;
    temp.specialAttack = this->specialAttack + x.specialAttack;
    temp.specialAttack = this->specialAttack + x.specialAttack;

    return temp;

}

Pokemon::PokemonStats& Pokemon::PokemonStats::operator+=(Pokemon::PokemonStats x){
    *this = *this + x;
    return *this;
}



Pokemon::PokemonStats generateIVs(){
    return Pokemon::PokemonStats(rand() % 16,rand() % 16,rand() % 16,rand() % 16,rand() % 16,rand() % 16);
}

void Pokemon::updateStats(){
    Pokemon::PokemonStats temp = this->baseStats + this->IVs;

    this->stats.HP = (((temp.HP * 2) * this->level) / 100) + this->level + 10;
    this->stats.attack = (((temp.attack * 2) * this->level) / 100) + 5;
    this->stats.defense = (((temp.defense * 2) * this->level) / 100) + 5;
    this->stats.speed = (((temp.speed * 2) * this->level) / 100) + 5;
    this->stats.specialAttack = (((temp.specialAttack * 2) * this->level) / 100) + 5;
    this->stats.specialDefense = (((temp.specialDefense * 2) * this->level) / 100) + 5;
}


std::vector<Move> chooseMoves(int pokemonID, int level){

}

Pokemon::Pokemon(int givenID, int startingLevel) : baseStats(PokemonStats(givenID)), IVs(generateIVs()), stats(baseStats){
        level = startingLevel;
        pokemonID = givenID;
        currentHP = stats.HP;
        hasFainted = 0;
        updateStats();

        for(int i =0; i< pokeData->pokemon.size(); i++){
            Pokemon_Info temp = pokeData->pokemon[i];

            if(temp.id() == givenID){
                species = temp.identifier();
                break;
            }
        }
        
        name = species;

        if(rand() % 8192 == 0){
            isShiny = 1;
        }
        else{
            isShiny = 0;
        }
      

}

