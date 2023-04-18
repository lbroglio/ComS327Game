#ifndef SCREEN_H
#define SCREEN_H


#include<stdio.h>
#include<iostream>
#include<vector>
#include"../Map/map.h"
#include"../Map/point.h"
#include"../Characters/gameCharacter.h"


//Colors
#define COLOR_SOFT_BLACK 236
#define COLOR_TALLGRASS 58
#define COLOR_FOREST 28
#define COLOR_POKEMART 17
#define COLOR_ROCK 235
#define COLOR_DESSERT 220
#define COLOR_BRIDGE 94
#define COLOR_PATH 255



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

/**
 * @brief Change the terminal display to have a space in the center of the map to be ready for battle/ catch interface etc
 * 
 */
void setInterfaceScreen();

/**
 * @brief Removes text currently on the interface screen
 * 
 */
void clearInterfaceScreen();
/**
 * @brief Redraws the map after setting an interface
 * 
 * @param map The map to draw
 */
void  endInterfaceScreen(mapTile_t* map);

/**
 * @brief Gets the player to choose a move to make
 * 
 * @return Number corresponding to the chosen move
 */
int playerBattleInterface();


/**
 * @brief Removes all the content from a given section of the interface scren
 * 
 * @param startLine The line to start on 
 * @param numLines The number of lines to clear
 */
void clearInterfaceSection(int startLine, int numLines);
#endif