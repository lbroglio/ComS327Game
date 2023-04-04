#ifndef FILEPARSER_H
#define FILEPARSR_H

#include"../PokemonData/PokemonData.h"

/**
 * @brief Loads in the data about Pokemon and there corresponding attributes (moves,type,species etc) from there .csv files into the program
 * 
 * @param dataCon Pointer to the container object for the data
 */
void loadData(DataCon* dataCon);

#endif