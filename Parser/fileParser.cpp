#include<iostream>
#include<fstream>
#include<string>
#include<vector>
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

    while(currChar != ' ' && currChar != ',' && currChar != '\n'){
        readWord += currChar;
        currChar = readFrom->get(); 
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



void parsePokemonFile(){    
     std::ifstream dataFile = openFile("pokemon");

}


void parseTypeNames(DataCon* dataCon){
    std::ifstream dataFile("/share/cs327/pokedex/pokedex/data/csv/type_names.csv");

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
            dataCon->type_names[placeTracker] = temp;
        }
        else{
            dataCon->otherLangues.push_back(temp);
        }
    }
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
           std::cout  << "\t\tint "<< savedAtts[j] << "() const {return " << savedAtts[j] << "_;}\n"; 
        }
        std::cout << "};";
        std::getline(getFrom,currWord);
        std::cout << currWord << "\n" << std::endl;
        

        getFrom.close();
    }
    
    return 0;
}
*/