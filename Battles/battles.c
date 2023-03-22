#include<curses.h>

void trainerBattle(){
    //Display Message
    move(0,0);
    clrtoeol();

    printw("You are in a trainer battle. Press esc to exit");
    char action;

    while(action != 27){
        action =  getch();
    }
}