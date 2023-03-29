#include<curses.h>
#include<string.h>
#include<string>
#include<iostream>
#include "playerMovement.h"
#include "gameCharacter.h"
#include "NPCMapInfo.h"
#include "../Map/map.h"
#include "../Battles/battles.h"
#include"../Map/mapGeneration.h"
#include"../Screen/screen.h"

//Function Prototypes
void fly(Player* player);
playerMoves_t getInput(NPCMapInfo mapInfo);
int costOfPlayerMove(char moveType);
void displayPlayerMoveError(char moveType);
void listTrainers(NPCMapInfo mapInfo);
void inBuilding();


char Player::move(mapTile_t* map){
    printMapWithChars(map,map->mapInfo);

    while(1 == 1){
        playerMoves_t playerMove = getInput(map->mapInfo);
        if(playerMove == QUIT){
            return 'Q';
        }
        else if(playerMove == REST){ 
            return  map->mapArr[rowNum][colNum];
        }   
        else if(playerMove == ENTER_BUILDING){
            if(map->mapArr[rowNum][colNum] == 'M' || map->mapArr[rowNum][colNum] == 'C'){
                inBuilding();
                return map->mapArr[rowNum][colNum];
            }
           else{
               //Display Error Message
                ::move(0,0);
                clrtoeol();
                printw("You cannot enter as you aren't at a building");
           }
        }
        else if(playerMove == FLY){
            fly(this);
            return 'F';
        }
        else{
            char type = movePlayerInMap(playerMove,map);
            
            if(type != 'I'){
                return type;
            }
        }
    }
}


char Player::movePlayerInMap(playerMoves_t playerMove,mapTile_t* map){
    Point newPos;

    switch (playerMove)
    {
    case UP_LEFT:
        newPos = Point(rowNum -1,colNum -1);
        break;
    case UP:
        newPos = Point(rowNum -1,colNum);
        break;
    case UP_RIGHT:
        newPos = Point(rowNum -1,colNum +1);
        break;
    case RIGHT:
        newPos = Point(rowNum,colNum +1);
        break;
    case DOWN_RIGHT:
        newPos = Point(rowNum +1,colNum +1);
        break;
    case DOWN:
        newPos = Point(rowNum +1,colNum);
        break;
    case DOWN_LEFT:
        newPos = Point(rowNum +1,colNum -1);
        break;
    case LEFT:
        newPos = Point(rowNum,colNum -1);
        break;
    default:
        break;

    }


    
    std::string illegalChars = "%%\"~";

    //If theres a trainer at the location to move to
    if(map->mapInfo.charLocations[newPos.rowNum][newPos.colNum].type != 'X'){
        if(checkTrainerDefeated(map->mapInfo.charLocations[newPos.rowNum][newPos.colNum].id,map->mapInfo) ==  0){
             trainerBattle(map->mapInfo.charLocations[newPos.rowNum][newPos.colNum].id,map);
        }
        return map->mapArr[newPos.rowNum][newPos.colNum];
    }
    //If the move is illegal
    else if(illegalChars.find(map->mapArr[newPos.rowNum][newPos.colNum]) != std::string::npos){
        displayPlayerMoveError(map->mapArr[newPos.rowNum][newPos.colNum]);
        return 'I';
    }

    //Hold player location
    Point temp = Point(rowNum,colNum);

    //Changes the player's location within its object
    rowNum = newPos.rowNum; 
    colNum = newPos.colNum;

    //Moves the player inside the character location array
    map->mapInfo.charLocations[temp.rowNum][temp.colNum] = GameCharacter();
    map->mapInfo.charLocations[newPos.rowNum][newPos.colNum] = *this;

    return map->mapArr[newPos.rowNum][newPos.colNum];
}

/**
 * THIS IS DEPRECATED AND NO LONGER USED
 * @brief Calculates cost of a move by the player
 * 
 * @param moveType The type of move
 * @return The cost of the move
 */
int costOfPlayerMove(char moveType){
    if(moveType == ':'){
        return 20;
    }
    else{
        return 10;
    }

}

/**
 * @brief Hanldes taking in player input. Interfaces for the trainer list and buildings are run from here. Returns the type of the move the player made
 * 
 * @param mapInfo The info struct for the current map tile
 * @return Type of move made
 */
playerMoves_t getInput(NPCMapInfo mapInfo){

    int inputEnded = 0;
    playerMoves_t chosenMove;


    while(inputEnded == 0){
        char playerMove = getch();
        switch (playerMove)
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
            chosenMove = ENTER_BUILDING;
            inputEnded = 1;
            break;
        //List Trainers
        case 't':
            listTrainers(mapInfo);
            break;
        //Fly
        case 'f':
            chosenMove = FLY;
            inputEnded = 1;
            break;
        //Quit Game
        case 'q':
        case 'Q':
            chosenMove = QUIT;
            inputEnded = 1;
            break;
        
        }

    }
    return chosenMove;
}

/**
 * @brief Handles the play actions when inside a building
 * 
 */
void inBuilding(){
    //Display Message
    move(0,0);
    clrtoeol();

    printw("Welcome Inside. Press < to exit");
    char action;

    while(action != '<'){
        action =  getch();
    }

    //Clear Message
    move(0,0);
    clrtoeol();

}




/**
 * @brief Displays a navigatable list of trainers
 * 
 * @param mapInfo Info struct for the current map tile
 */
void listTrainers(NPCMapInfo mapInfo){
    //Make a list to the trainers in
    GameCharacter NPCList[mapInfo.numNPCs];
    int placeTracker = 0;
    
    //Gets location of all trainers from the location array add them to the list 
    for(int i=0; i < 21; i++){
        for(int j = 0; j < 80; j++){
            if(mapInfo.charLocations[i][j].type != 'X' && mapInfo.charLocations[i][j].type != '@'){
                Point temp;
                temp.rowNum = i;
                temp.colNum = j;

                NPCList[placeTracker] = GameCharacter(temp,mapInfo.charLocations[i][j].type,0);

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
        for(int i = pageTracker; i < mapInfo.numNPCs && i < (pageTracker + 4); i++){
            GameCharacter currChar = NPCList[i];

            if(currChar.type == '@'){
                continue;
            }

            //Set up relative location
            //Gets the location difference for each direction
            int vertDiff = mapInfo.playerLocation.rowNum - currChar.getRowNum();
            int horiDiff = mapInfo.playerLocation.colNum - currChar.getColNum();

            //Setuip std::strings to hold the cardinal directions
            std::string vertStr = "South";
            std::string horiStr = "West";

            //Flips the sign and cardinal direction if the difference is negative
            if(vertDiff < 0){
                vertStr = "North";
                vertDiff *= -1;
            }

            if(horiDiff < 0){
                horiStr = "East";
                horiDiff *= -1;
            }

            printw("%c: %d %s %d %s ",currChar.type,vertDiff,vertStr.c_str(),horiDiff,horiStr.c_str());
        }
    
        //Wait for player input
        int action = getch();

        if(action == KEY_UP && (pageTracker - 4) >= 0){
            pageTracker -= 4;
        }
        else if(action == KEY_DOWN && (pageTracker + 4) < mapInfo.numNPCs){
            pageTracker += 4;
        }
        else if(action == 27){
            escPressed = 1;
        }

    
    }

    //Clear Message
    move(0,0);
    clrtoeol();
  

}

/**
 * @brief Displays an error when the player tries to make an illegal move
 * 
 * @param move The square the player tried to move into
 */
void displayPlayerMoveError(char moveType){
    std::string moveStr;

    if(moveType == '%'){
        moveStr = "Mountain";
    }
    else if(moveType == '\"'){
         moveStr = "Forest";
    }
    else if(moveType == '~'){
        moveStr = "Water";
    }

    //Display Message
    move(0,0);
    clrtoeol();

    printw("You cannot move into a %s tile. Make a different move",moveStr.c_str());
}

void fly(Player* player){
    //Display Error Message
    ::move(0,0);
    clrtoeol();
    printw("Enter the coordinates you are flying to - Seperate the numbers with a space and press enter afterwards:");
    
    int flyRow = 0;
    int flyCol = 0;

    ::noraw();

    scanw("%d %d",&flyRow,&flyCol);

    ::raw();

    flyRow += 200;
    flyCol += 200;

    //I'm sending the coords to fly to in the player's location attributes
    //This is a really jankly way of doing it but its what im going with
    player->setRowNum(flyRow);
    player->setColNum(flyCol);
}

GameCharacter* Player::clone(){
    Player* temp = new Player(Point(this->rowNum,this->colNum));
    return temp;
}
