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
std::string readWord(std::string readFrom){
    char currChar = readFrom[0];
    std::string readWord = "";

    int tracker = 1;
    while(currChar != ' ' && currChar != ',' && currChar != '\n'){
        readWord += currChar;
        currChar = readFrom[tracker];
        tracker += 1;
    }


    return readWord;
}


int main(int argc, char* argv[]){

    return 0;
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