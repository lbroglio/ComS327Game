#include<stdio.h>
#include<curses.h>
#include"screen.h"
#include"../Map/map.h"
#include"../Characters/gameCharacter.h"




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

    //Set default print color
    attron(COLOR_PAIR(COLOR_WHITE));
}


void printMapWithChars(mapTile_t* map, NPCMapInfo  mapInfo){
    //Clear the screen
    clear();

    //Move cursor to the location to print the map
    move(1,0);

    //Print the map
    for(int i =0; i < 21; i++){
        for(int j = 0; j < 80;j ++){
             char toPrint;
            if(mapInfo.charLocations[i][j].type == 'X'){
                toPrint = map->mapArr[i][j];
            }
            else{
                toPrint = mapInfo.charLocations[i][j].type;
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
        attron(COLOR_PAIR(COLOR_WHITE));
        printw("\n");
    }
    refresh();
}

void setInterfaceScreen(){
    //CREATE NEW COLOR FOR BACKGROUND
    init_pair(COLOR_SOFT_BLACK, COLOR_WHITE, COLOR_SOFT_BLACK);

    for(int i = 3; i < 20; i++){
        move(i,4);
        for(int j = 0; j < 76;j ++){
                attron(COLOR_PAIR(COLOR_SOFT_BLACK));
                printw("  ");
        }
        
    }

}


void clearInterfaceScreen(){
        for(int i =3; i < 20; i++){
            move(i,4);
            for(int j = 0; j < 76; j++){
                    attron(COLOR_PAIR(COLOR_SOFT_BLACK));
                    printw("  ");
            }   
    }
}


void  endInterfaceScreen(mapTile_t* map){
    printMapWithChars(map, map->mapInfo);
}


void clearInterfaceSection(int startLine, int numLines){
    for(int i = 0; i < numLines; i++){
        move(startLine + i,4);
        for(int j = 0; j < 76; j++){
            printw("  ");
        }
    }
}

int playerBattleInterface(){

    mvprintw(10,6,"Use spacebar to choose an action");
    mvprintw(11,7,"Fight");
    mvprintw(12,7,"Bag");
    mvprintw(13,7,"Run");
    mvprintw(14,7,"Pokemon");    


    int actionSelected = 0;
    int i =0;
    while(actionSelected == 0){
        mvprintw(11+i,5,"*");
        //Wait for player input
        int action = getch();
        
        mvprintw(11+i,5," ");

        if(action == KEY_UP && i > 0){
            i -= 1;
        }
        else if(action == KEY_DOWN && i < 3){
            i += 1;
        }
        else if(action == ' '){
            actionSelected = 1;
        }
        
    }

    clearInterfaceSection(10,5);
    return i;
}


void setDeathScreen(){
    clear();
    attron(COLOR_PAIR(COLOR_WHITE));
    mvprintw(10,5,"All your Pokemon are defeated. You have been returned to the spawn. Press any key to advance");
    getch();

}


