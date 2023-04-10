#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<climits>
#include"../PokemonData/PokemonData.h"

const std::string fileList[] = {"pokemon", "moves", "pokemon_moves", "pokemon_species", "experience","type_names", "pokemon_stats", "stats", "pokemon_types"};   

/**
 * @brief Reads all of the characters from a file stream until it hits a space or a comma
 * 
 * @param readFrom The file stream to read from
 * @return The character until a space or comma is encountered
 */
std::string readEntry(std::ifstream* readFrom){
    char currChar = readFrom->get();
    std::string readWord = "";

    while(currChar != ' ' && currChar != ',' && currChar != '\n' && currChar != EOF){
        readWord += currChar;
        currChar = readFrom->get(); 
    }

    if(readWord == ""){
        readWord = std::to_string(INT_MAX);
    }
    return readWord;
}

std::ifstream openFile(std::string fileName){
    std::ifstream dataFile;

    //Try to open file at first location
    dataFile.open("/share/cs327/pokedex/pokedex/data/csv/" + fileName + ".csv");

    //If the file couldn't be found there
    if(!dataFile.is_open()){
        //Try to open at second location
        dataFile.open("$HOME/.poke327/pokedex/pokedex/data/csv/" + fileName + ".csv");

        //Alert the user and exit if the file can't be opened
        if(!dataFile.is_open()){
            std::cout << "ERROR: File could not be opened" << std::endl;
            exit(1);
        }
    }

    return dataFile;
}



/**
 * @brief Extract the data from the pokemon.csv file and load it into the container object
 * 
 * @param dataCon Pointer to the container object
 */
void parsePokemonFile(DataCon* dataCon){    
    std::ifstream dataFile = openFile("pokemon");

    std::string lineDump;

	int idTemp;
	std::string identifierTemp;
	int species_idTemp;
	int heightTemp;
	int weightTemp;
	int base_experienceTemp;
	int orderTemp;
	int is_defaultTemp;


    
    std::getline(dataFile,lineDump);

    int placeTracker = 0;

    while(dataFile.peek() != EOF){
        idTemp = atoi(readEntry(&dataFile).c_str());
        identifierTemp = readEntry(&dataFile);
        species_idTemp = atoi(readEntry(&dataFile).c_str());  
        heightTemp = atoi(readEntry(&dataFile).c_str());
        weightTemp = atoi(readEntry(&dataFile).c_str());
        base_experienceTemp = atoi(readEntry(&dataFile).c_str());
        orderTemp = atoi(readEntry(&dataFile).c_str());
        is_defaultTemp = atoi(readEntry(&dataFile).c_str());

       	Pokemon_Info temp(idTemp,identifierTemp, species_idTemp, heightTemp, weightTemp, base_experienceTemp, orderTemp, is_defaultTemp);
        dataCon->pokemon.push_back(temp);

        placeTracker += 1;

    }

}


/**
 * @brief Extract the data from the moves.csv file and load it into the container object
 * 
 * @param dataCon Pointer to the container object
 */
void parseMoveFile(DataCon* dataCon){    
    std::ifstream dataFile = openFile("moves");

    std::string lineDump;

	int idTemp;
	std::string identifierTemp;
	int generation_idTemp;
	int type_idTemp;
	int powerTemp;
	int ppTemp;
	int accuracyTemp;
	int priorityTemp;
	int target_idTemp;
	int damage_class_idTemp;
	int effect_idTemp;
	int effect_chanceTemp;
	int contest_type_idTemp;
	int contest_effect_idTemp;
	int super_contest_effect_idTemp;


    
    std::getline(dataFile,lineDump);

    int placeTracker = 0;

    while(dataFile.peek() != EOF){
        idTemp = atoi(readEntry(&dataFile).c_str());
        identifierTemp = readEntry(&dataFile);
        generation_idTemp = atoi(readEntry(&dataFile).c_str());
        type_idTemp = atoi(readEntry(&dataFile).c_str());
        powerTemp = atoi(readEntry(&dataFile).c_str());
        ppTemp = atoi(readEntry(&dataFile).c_str());
        accuracyTemp = atoi(readEntry(&dataFile).c_str());
        priorityTemp = atoi(readEntry(&dataFile).c_str());
        target_idTemp = atoi(readEntry(&dataFile).c_str());
        damage_class_idTemp = atoi(readEntry(&dataFile).c_str());
        effect_idTemp = atoi(readEntry(&dataFile).c_str());
        effect_chanceTemp = atoi(readEntry(&dataFile).c_str());
        contest_type_idTemp = atoi(readEntry(&dataFile).c_str());
        contest_effect_idTemp = atoi(readEntry(&dataFile).c_str());
        super_contest_effect_idTemp = atoi(readEntry(&dataFile).c_str());

       	Move temp(idTemp, identifierTemp, generation_idTemp, type_idTemp, powerTemp, ppTemp, accuracyTemp, priorityTemp, target_idTemp, damage_class_idTemp, effect_idTemp, effect_chanceTemp, contest_type_idTemp, contest_effect_idTemp, super_contest_effect_idTemp);
        dataCon->moves.push_back(temp);

        placeTracker += 1;

    }
}


/**
 * @brief Extract the data from the pokemon_moves.csv file and load it into the container object
 * 
 * @param dataCon Pointer to the container object
 */
void parsePokemonMoveFile(DataCon* dataCon){    
    std::ifstream dataFile = openFile("pokemon_moves");

    std::string lineDump;

	int pokemon_idTemp;
	int version_group_idTemp;
	int move_idTemp;
	int pokemon_move_method_idTemp;
	int levelTemp;
	int orderTemp;	

    std::getline(dataFile,lineDump);

    int placeTracker = 0;

    while(dataFile.peek() != EOF){
        pokemon_idTemp = atoi(readEntry(&dataFile).c_str());
        version_group_idTemp = atoi(readEntry(&dataFile).c_str());
        move_idTemp = atoi(readEntry(&dataFile).c_str());
        pokemon_move_method_idTemp = atoi(readEntry(&dataFile).c_str());
        levelTemp = atoi(readEntry(&dataFile).c_str());
        orderTemp = atoi(readEntry(&dataFile).c_str());	

       	Pokemon_Move temp(pokemon_idTemp, version_group_idTemp, move_idTemp, pokemon_move_method_idTemp, levelTemp, orderTemp);
        dataCon->pokemon_moves.push_back(temp);

        placeTracker += 1;

    }   

}

/**
 * @brief Extract the data from the pokemon_species.csv file and load it into the container object
 * 
 * @param dataCon Pointer to the container object
 */
void parsePokemonSpeciesFile(DataCon* dataCon){    
    std::ifstream dataFile = openFile("pokemon_species");

    std::string lineDump;

	int idTemp;
	std::string identifierTemp;
	int generation_idTemp;
	int evolves_from_species_idTemp;
	int evolution_chain_idTemp;
	int color_idTemp;
	int shape_idTemp;
	int habitat_idTemp;
	int gender_rateTemp;
	int capture_rateTemp;
	int base_happinessTemp;
	int is_babyTemp;
	int hatch_counterTemp;
	int has_gender_differencesTemp;
	int growth_rate_idTemp;
	int forms_switchableTemp;
	int is_legendaryTemp;
	int is_mythicalTemp;
	int orderTemp;
	int conquest_orderTemp;

    std::getline(dataFile,lineDump);

    int placeTracker = 0;

    while(dataFile.peek() != EOF){
        idTemp = atoi(readEntry(&dataFile).c_str());
        identifierTemp = readEntry(&dataFile);
        generation_idTemp = atoi(readEntry(&dataFile).c_str());
        evolves_from_species_idTemp = atoi(readEntry(&dataFile).c_str());
        evolution_chain_idTemp = atoi(readEntry(&dataFile).c_str());
        color_idTemp = atoi(readEntry(&dataFile).c_str());
        shape_idTemp = atoi(readEntry(&dataFile).c_str());
        habitat_idTemp = atoi(readEntry(&dataFile).c_str());
        gender_rateTemp = atoi(readEntry(&dataFile).c_str());
        capture_rateTemp = atoi(readEntry(&dataFile).c_str());
        base_happinessTemp = atoi(readEntry(&dataFile).c_str());
        is_babyTemp = atoi(readEntry(&dataFile).c_str());
        hatch_counterTemp = atoi(readEntry(&dataFile).c_str());
        has_gender_differencesTemp = atoi(readEntry(&dataFile).c_str());
        growth_rate_idTemp = atoi(readEntry(&dataFile).c_str());
        forms_switchableTemp = atoi(readEntry(&dataFile).c_str());
        is_legendaryTemp = atoi(readEntry(&dataFile).c_str());
        is_mythicalTemp = atoi(readEntry(&dataFile).c_str());
        orderTemp = atoi(readEntry(&dataFile).c_str());
        conquest_orderTemp = atoi(readEntry(&dataFile).c_str());

        Pokemon_Species temp(idTemp, identifierTemp, generation_idTemp, evolves_from_species_idTemp, evolution_chain_idTemp, color_idTemp, shape_idTemp, habitat_idTemp, gender_rateTemp, capture_rateTemp, base_happinessTemp, is_babyTemp, hatch_counterTemp, has_gender_differencesTemp, growth_rate_idTemp, forms_switchableTemp, is_legendaryTemp, is_mythicalTemp, orderTemp, conquest_orderTemp);
        dataCon->pokemon_species.push_back(temp);

        placeTracker += 1;

    }

}

/**
 * @brief Extract the data from the experience.csv file and load it into the container object
 * 
 * @param dataCon Pointer to the container object
 */
void parseExperienceFile(DataCon* dataCon){    
    std::ifstream dataFile = openFile("experience");

    std::string lineDump;

	int growth_rate_idTemp;
	int levelTemp;
	int experienceTemp;

    std::getline(dataFile,lineDump);

    int placeTracker = 0;

    while(dataFile.peek() != EOF){
        growth_rate_idTemp = atoi(readEntry(&dataFile).c_str());
        levelTemp = atoi(readEntry(&dataFile).c_str());
        experienceTemp = atoi(readEntry(&dataFile).c_str());


       	Experience temp(growth_rate_idTemp, levelTemp, experienceTemp);
        dataCon->experience.push_back(temp);

        placeTracker += 1;

    }   

}

/**
 * @brief Extract the data from the pokemon_stats.csv file and load it into the container object
 * 
 * @param dataCon Pointer to the container object
 */
void parsePokemonStatFile(DataCon* dataCon){    
    std::ifstream dataFile = openFile("pokemon_stats");

    std::string lineDump;

	int pokemon_idTemp;
	int stat_idTemp;
	int base_statTemp;
	int effortTemp;

    std::getline(dataFile,lineDump);

    int placeTracker = 0;

    while(dataFile.peek() != EOF){
	    pokemon_idTemp = atoi(readEntry(&dataFile).c_str());
	    stat_idTemp = atoi(readEntry(&dataFile).c_str());
	    base_statTemp = atoi(readEntry(&dataFile).c_str());
	    effortTemp = atoi(readEntry(&dataFile).c_str());

       	Pokemon_Stat temp(pokemon_idTemp,stat_idTemp,base_statTemp,effortTemp);
        dataCon->pokemon_stats.push_back(temp);

        placeTracker += 1;

    }   

}

/**
 * @brief Extract the data from the stats.csv file and load it into the container object
 * 
 * @param dataCon Pointer to the container object
 */
void parseStatFile(DataCon* dataCon){    
    std::ifstream dataFile = openFile("stats");

    std::string lineDump;

	int idTemp;
	int damage_class_idTemp;
	std::string identifierTemp;
	int is_battle_onlyTemp;
	int game_indexTemp;

    std::getline(dataFile,lineDump);

    int placeTracker = 0;

    while(dataFile.peek() != EOF){
        idTemp = atoi(readEntry(&dataFile).c_str());
	    damage_class_idTemp = atoi(readEntry(&dataFile).c_str());
	    identifierTemp =readEntry(&dataFile);
	    is_battle_onlyTemp = atoi(readEntry(&dataFile).c_str());
	    game_indexTemp = atoi(readEntry(&dataFile).c_str());

       	Stat temp(idTemp,damage_class_idTemp, identifierTemp, is_battle_onlyTemp, game_indexTemp);
        dataCon->stats.push_back(temp);

        placeTracker += 1;

    }   

}

/**
 * @brief Extract the data from the pokemon_types.csv file and load it into the container object
 * 
 * @param dataCon Pointer to the container object
 */
void parsePokemonTypeFile(DataCon* dataCon){    
    std::ifstream dataFile = openFile("pokemon_types");

    std::string lineDump;

	int pokemon_idTemp;
	int type_idTemp;
	int slotTemp;

    std::getline(dataFile,lineDump);

    int placeTracker = 0;

    while(dataFile.peek() != EOF){
	    pokemon_idTemp = atoi(readEntry(&dataFile).c_str());
	    type_idTemp = atoi(readEntry(&dataFile).c_str());
	    slotTemp = atoi(readEntry(&dataFile).c_str());

       	Pokemon_Type temp(pokemon_idTemp,type_idTemp,slotTemp);
        dataCon->pokemon_types.push_back(temp);

        placeTracker += 1;

    }   

}

/**
 * @brief Extract the data from the type_names.csv file and load it into the container object
 * Non english data is grouped together in a vector
 * 
 * @param dataCon Pointer to the container object
 */
void parseTypeNameFile(DataCon* dataCon){
    std::ifstream dataFile = openFile("type_names");

    std::string lineDump;

    int idTemp;
    int lanTemp;
    std::string nameTemp;
    
    std::getline(dataFile,lineDump);

    int placeTracker = 0;

    while(dataFile.peek() != EOF){
        idTemp = atoi(readEntry(&dataFile).c_str());
        lanTemp = atoi(readEntry(&dataFile).c_str());
        nameTemp = readEntry(&dataFile);

        Type_Name temp(idTemp,lanTemp,nameTemp);

        if(temp.local_language_id() == 9){
            dataCon->type_names.push_back(temp);
        }
        else{
            dataCon->otherLangues.push_back(temp);
        }

        placeTracker += 1;
    }
}



void loadData(DataCon* dataCon){

    //Parses the data from all the files and loads it
    parsePokemonFile(dataCon);
    parseMoveFile(dataCon);
    parsePokemonMoveFile(dataCon);
    parsePokemonSpeciesFile(dataCon);
    parseExperienceFile(dataCon);
    parsePokemonStatFile(dataCon);
    parseStatFile(dataCon);
    parsePokemonTypeFile(dataCon);
    parseTypeNameFile(dataCon);
}



/*Old code used to generate class code
int main(int argc, char* argv[]){
    for(int i = 0; i < 9; i++){
        std::ifstream getFrom("/share/cs327/pokedex/pokedex/data/csv/" + fileList[i] + ".csv");


        std::string temp;
        std::vector<std::string> savedAtts;

        char curr = getFrom.get();
        std::string currWord = "";
        while(curr != '\n'){
            if(curr == ',' || curr == ' '){
                curr = getFrom.get();
                savedAtts.push_back(currWord);
                currWord = "";
            }
            else{
                currWord += curr;
                curr = getFrom.get();
               
            }
        }
        savedAtts.push_back(currWord);




        std::cout << "class "<< fileList[i] << "{\n";

        std::cout  << "\tprivate:\n";
        for(int j =0; j < savedAtts.size(); j++){
            std::cout  << "\t\tint "<< savedAtts[j] << "_" << ";\n";
        }
        std::cout  << "\tpublic:\n";
        std::cout <<"\t\t" << fileList[i] << "(";
        for(int j =0; j < savedAtts.size(); j++){
            std::cout  << "int "<< savedAtts[j] << ", ";
        }
        std::cout << ") : ";

        for(int j =0; j < savedAtts.size(); j++){
            std::cout << savedAtts[j] << "_(" <<savedAtts[j] << "), ";
        }
        std::cout << "{}\n";


        for(int j =0; j < savedAtts.size(); j++){
           std::cout  << "\t\tint "<< savedAtts[j] << "() const {return " << savedAtts[j] << "_ ;}\n"; 
        }
        std::cout << "};";
        std::getline(getFrom,currWord);
        std::cout << currWord << "\n" << std::endl;
        

        getFrom.close();
    }
    
    return 0;
}
*/