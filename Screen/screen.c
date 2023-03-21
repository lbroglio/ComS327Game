#include<stdio.h>
#include<curses.h>
#include"../Map/map.h"
#include"../Characters/gameCharacter.h"

//Colors
#define COLOR_TALLGRASS 58
#define COLOR_FOREST 28
#define COLOR_POKEMART 17
#define COLOR_ROCK 235
#define COLOR_DESSERT 220
#define COLOR_BRIDGE 94
#define COLOR_PATH 255


void terminalInit(){
    initscr();
    raw();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    start_color();

    //BASE EIGHT COLORS
    init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);

    //CUSTOM COLORS
    init_pair(COLOR_TALLGRASS, COLOR_TALLGRASS, COLOR_BLACK);
    init_pair(COLOR_FOREST, COLOR_FOREST, COLOR_BLACK);
    init_pair(COLOR_POKEMART, COLOR_POKEMART, COLOR_BLACK);
    init_pair(COLOR_ROCK, COLOR_ROCK, COLOR_BLACK);
    init_pair(COLOR_DESSERT, COLOR_DESSERT, COLOR_BLACK);
    init_pair(COLOR_PATH, COLOR_PATH, COLOR_BLACK);
    init_pair(COLOR_BRIDGE, COLOR_BRIDGE, COLOR_BLACK);
}


void printMapWithChars(mapTile_t* map, nMapInfo_t mapInfo){
    //Clear the screen
    clear();

    //Move cursor to the location to print the map
    move(1,0);

    //Print the map
    for(int i =0; i < 21; i++){
        for(int j = 0; j < 80;j ++){
             char toPrint;
            if(mapInfo.charLocations[i][j] == 'X'){
                toPrint = map->mapArr[i][j];
            }
            else{
                toPrint = mapInfo.charLocations[i][j];
            }
           

            if(toPrint == '.'){
                attron(COLOR_PAIR(COLOR_GREEN));
                printw("%c ",toPrint);
                
            }
            else if(toPrint == ':'){
                attron(COLOR_PAIR(COLOR_TALLGRASS));
                printw("%c ",toPrint);
            }
            else if(toPrint == '~'){
                attron(COLOR_PAIR(COLOR_BLUE));
                printw("%c ",toPrint);
            }
            else if(toPrint == '%'){
                attron(COLOR_PAIR(COLOR_ROCK));
                printw("%c ",toPrint);
            }
            else if(toPrint == '\"'){
                attron(COLOR_PAIR(COLOR_FOREST));
                printw("%c ",toPrint);
            }
            else if(toPrint == '*'){
                attron(COLOR_PAIR(COLOR_DESSERT));
                printw("%c ",toPrint);
            }
            else if(toPrint == 'C'){
                attron(COLOR_PAIR(COLOR_RED));
                printw("%c ",toPrint);
            }
            else if(toPrint == 'M'){
                attron(COLOR_PAIR(COLOR_POKEMART));
                printw("%c ",toPrint);
            }
            else if(toPrint == '#'){
                attron(COLOR_PAIR(COLOR_PATH));
                printw("%c ",toPrint);
            }
            else if(toPrint == '='){
                attron(COLOR_PAIR(COLOR_BRIDGE));
                printw("%c ",toPrint);
            }
            else{
                attron(COLOR_PAIR(COLOR_WHITE));
                printw("%c ",toPrint);
            }
            
        }
        printw("\n");
    }
    refresh();
}