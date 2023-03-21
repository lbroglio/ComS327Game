#include<curses.h>
#include "playerMovement.h"
#include "gameCharacter.h"


int playerTurn(character_t* player, nMapInfo_t mapInfo){
    playerMoves_t move = getInput(mapInfo);

    if(move == QUIT){

    }
    else if(move == REST){

    }
    else if(move == ENTER_BUILDING){

    }
    else{
        
    }

}


playerMoves_t getInput(nMapInfo_t mapInfo){

    int inputEnded = 0;
    playerMoves_t chosenMove;


    while(inputEnded == 0){
        char move = getch();
        switch (move)
        {
        //Upper left
        case '7':
        case 'y':
            chosenMove = UP_LEFT;
            inputEnded = 1;
            break;
        //Up
        case '8':
        case 'k':
            chosenMove = UP;
            inputEnded = 1;
            break;
        //Upper right
        case '9':
        case 'u':
            chosenMove = UP_RIGHT;
            inputEnded = 1;
            break;
        //Right
        case '6':
        case 'l':
            chosenMove = RIGHT;
            inputEnded = 1;
            break;
        //Lower Right
        case '3':
        case 'n':
            chosenMove = DOWN_RIGHT;
            inputEnded = 1;
            break;
        //Down
        case '2':
        case 'j':
            chosenMove = DOWN;
            inputEnded = 1;
            break;
        //Lower left
        case '1':
        case 'b':
            chosenMove = DOWN_LEFT;
            inputEnded = 1;
            break;
        //Left
        case '4':
        case 'h':
            chosenMove = LEFT;
            inputEnded = 1;
            break;
        //Rest
        case '5':
        case ' ':
        case '.':
            chosenMove = REST;
            inputEnded = 1;
            break;
        //Enter Building
        case '>':
            inBuilding();
            chosenMove = ENTER_BUILDING;
            inputEnded = 1;
            break;
        //List Trainers
        case 't':
            listTrainers(mapInfo);
            break;
        //Quit Game
        case 'q':
        case 'Q':
            chosenMove = QUIT;
            inputEnded = 1;
            break;
        }
    }
}

void inBuilding(){
    //Display Message
    move(0,0);
    clrtoeol();

    printw("Welcome Inside. Press < to exit")
    char action;

    while(action != '<'){
        action =  getch();
    }

}





void listTrainers(nMapInfo_t mapInfo){
    //Make a list to the trainers in
    character_t NPCList[mapInfo.numNPCs];
    int placeTracker = 0;
    
    //Gets location of all trainers from the location array add them to the list 
    for(int i=0; i < 21; i++){
        for(int j = 0; j < 80; j++){
            if(mapInfo.charLocations[i][j] != 'X'){
                point_t temp;
                temp.rowNum = i;
                temp.colNum = j;

                NPCList[placeTracker] = characterInit(temp,mapInfo.charLocations[i][j],0,'.');

                placeTracker++;
            }
        }
    }


    int escPressed = 0;
    int pageTracker = 0; 

    //Display the list
    while(escPressed == 0){
        //Clears any text currently displayed at the top
        move(0,0);
        clrtoeol();
        for(int i = pageTracker; i < mapInfo.numNPCs || i < (pageTracker + 4); i++){
            character_t currChar = NPCList[i];
            char* locStr = locToPlayerStr(mapInfo.playerLocation, currChar);


            //Set up relative location
            //Gets the location difference for each direction
            int vertDiff = mapInfo.playerLocation.rowNum - currChar.rowNum;
            int horiDiff = mapInfo.playerLocation.colNum - currChar.colNum;

            //Setuip strings to hold the cardinal directions
            char* vertStr = "South";
            char* horiStr = "West";

            //Flips the sign and cardinal direction if the difference is negative
            if(vertDiff < 0){
                vertStr = "North";
                vertDiff *= -1;
            }

            if(horiDiff < 0){
                vertStr = "East";
                horiDiff *= -1;
            }

            printw("%c: %d %s %d %s",currChar.type,vertDiff,vertStr,horiDiff,horiStr);
        }
    
        //Wait for player input
        char action = getch();

        if(action == 'A' && (pageTrakcer - 4) >= 0){
            pageTracker -= 4;
        }
        else if(action == 'B'){
            pageTrakcer += 4
        }
        else if(action == '27'){
            escPressed = 1;
        }
    
    }
  

}