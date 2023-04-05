#ifndef SCREEN_H
#define SCREEN_H


#include<stdio.h>
#include<iostream>
#include<vector>
#include"../Map/map.h"
#include"../Map/point.h"
#include"../Characters/gameCharacter.h"




/**
 * @brief Sets up the terminal
 * 
 */
void terminalInit();

/**
 * @brief Prints a map to the console with NPCS and the player character in the correct location
 * 
 * @param map The map to print
 * @param mapInfo The NPC information for the map
 */
void printMapWithChars(mapTile_t* map, NPCMapInfo mapInfo);

/**
 * @brief Prints an array to the screen. Iterates through each element and prints it
 * 
 * @tparam T Type of the array to print
 * @param arr The array to print
 * @param length The length of the array to print
 */
template<typename T>
void printDataVector(std::vector<T> v, int length){
    
    for(int i = 0; i < length; i++){
        std::cout << v[i] << std::endl;
    }
}

#endif