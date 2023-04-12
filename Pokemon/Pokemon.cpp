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
    int vectorSize = pokeData->pokemon_stats.size();
    //Get all the stats for pokemon 
    for(i=0; (i < vectorSize) && (statsSet < 6); i++){
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

Pokemon::PokemonStats Pokemon::PokemonStats::operator+(Pokemon::PokemonStats x){
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


/**
 * @brief Chooses moves to give to a Pokemon
 * 
 * @param givenID The special ID of the pokemon
 * @param level The level of the Pokemon
 * @return Vector containing the chosen moves
 */
std::vector<Move>* chooseMoves(int givenID, int level){
    //Create vectors
    std::vector<int> possibleMoveIDs;
    std::vector<Move>* chosenMoves = new std::vector<Move>();

    int  dataVectorSize = pokeData->pokemon_moves.size();

    //Get all moves for this pokemon below or at its current level
    for(int i =0; i < dataVectorSize; i++){
        Pokemon_Move temp = pokeData->pokemon_moves[i];

        if(temp.pokemon_id() == givenID && temp.pokemon_move_method_id() == 1 && temp.level() <= level){
            possibleMoveIDs.push_back(temp.move_id());
        }
    }

    int numMoves = possibleMoveIDs.size();

    //Randomly choose two moves
    int moveLoc1 = rand() % numMoves;
    int moveLoc2 = rand() % numMoves;

    

    //Make sure they aren't the same move
    if(moveLoc1 == moveLoc2){
        if(moveLoc2 ==   - 1){
            moveLoc2 -= 1;
        }
        else{
            moveLoc2 += 1;
        }
    }  
    int foundMoves = 0;

    int dataSize = pokeData->moves.size();
    //Get the chosen moves and add them to the vector
    int tracker = 0;
    while(foundMoves < 2 && tracker < dataSize){
        Move temp = pokeData->moves[tracker];

        if(temp.id() == possibleMoveIDs[moveLoc1] || temp.id() == possibleMoveIDs[moveLoc2]){
            chosenMoves->push_back(temp);
        }
        tracker++;
        foundMoves = chosenMoves->size();
    }
    
    //Return Chosen moves
    return chosenMoves;
}

Pokemon::Pokemon(int givenID, int startingLevel) : baseStats(PokemonStats(givenID)), IVs(generateIVs()), stats(baseStats){
        level = startingLevel;
        pokemonID = givenID;
        hasFainted = 0;
        updateStats();
        currentHP = stats.HP;
        int dataSize = pokeData->pokemon.size();

        for(int i =0; i <  dataSize; i++){
            Pokemon_Info temp = pokeData->pokemon[i];

            if(temp.id() == givenID){
                speciesID = temp.species_id();
                species = temp.identifier();
                break;
            }
        }
        
        name = species;
        moveList = chooseMoves(speciesID,startingLevel);
        if(rand() % 8192 == 0){
            isShiny = 1;
        }
        else{
            isShiny = 0;
        }
      

}


std::ostream &operator<<(std::ostream &o,  const Pokemon &s){
    o << "Pokemon{" << std::endl;
    o << "\tHealth: " << s.currentHP << std::endl;    
    o << "\tLevel: " << s.level << std::endl;    
    o << "\t" << (s.hasFainted == 1  ? "Fainted" : "Not Fainted")  << std::endl;    
    o << "\tName: " << s.name << std::endl;    
    o << "\tSpecies: " << s.species << std::endl;
    o << "\tStats" << s.stats;
    o << "\tBase Stats" << s.baseStats;
    o << "\tIVs" << s.IVs;
    o << "\tMoves[";

    int dataSize = s.moveList->size();
    for(int i=0; i < dataSize; i++){
        o << (*s.moveList)[i].identifier();
        if(i != dataSize -1){
            o <<  ", ";
        }
    }
    o << "]" << std::endl;
    o << "\t" << (s.isShiny == 0  ? "Normal" : "Shiny")  << std::endl;
    o << "}" << std::endl;
    return o;
}

std::ostream &operator<<(std::ostream &o,  const Pokemon::PokemonStats &s){
    o << "{" << std::endl;
    o <<  "\t\tHP: " << s.HP << std::endl; 
    o <<  "\t\tAttack: " << s.attack << std::endl;
    o <<  "\t\tDefense: " << s.defense << std::endl;
    o <<  "\t\tSpeed: " << s.speed << std::endl;
    o <<  "\t\tSpecial Attack: " << s.specialAttack << std::endl;
    o <<  "\t\tSpecial Defense: " << s.specialDefense << std::endl;
    o << "\t}" << std::endl;

    return o;

}

int getRandomPokemonID(){
    int id = (rand() % 1092) + 1;
    if (id > 898){
        id = (rand() % 193) + 10001;
    }
    return id;
}