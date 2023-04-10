#ifndef WORLDGEN_H
#define WORLDGEN_H

#include"map.h"
#include"../Characters/playerMovement.h"
//#include"../PokemonData/PokemonData.h"

/**
 * @brief Wrapper struct for the array holding all the tiles in the world map
 * 
 */
struct WorldMap{
    Player* player;
    mapTile_t** worldArr;
    int placedArr[401][401];
    //DataCon* pokeData; 
    /**
     * @brief Creates a world map - Allocates all the memory for the tiles
     * 
     * @return The created worldMap
     */
    WorldMap();

    /**
     * @brief Destorys a world map - Dellocates the memory
     * 
     * @param toDestroy The world map to destroy
     */
    ~WorldMap();

    

};





#endif