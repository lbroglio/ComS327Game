#include<curses.h>
#include<string.h>
#include<string>
#include "playerMovement.h"
#include "gameCharacter.h"
#include "../Map/map.h"
#include "../Battles/battles.h"

//Function Prototypes
playerMoves_t getInput(NPCMapInfo mapInfo);
int costOfPlayerMove(char moveType);
int movePlayer(playerMoves_t playerMove, GameCharacter* player, mapTile_t map,NPCMapInfo* mapInfo);
void displayPlayerMoveError(char moveType);
void listTrainers(NPCMapInfo mapInfo);
void inBuilding();

int playerTurn(GameCharacter* player, mapTile_t map,NPCMapInfo* mapInfo){
    
    while(1 == 1){
        playerMoves_t playerMove = getInput(*mapInfo);
        if(playerMove == QUIT){
            return -1;
        }
        else if(playerMove == REST){ 
            return costOfPlayerMove(map.mapArr[mapInfo->playerLocation.rowNum][mapInfo->playerLocation.colNum]);
        }   
        else if(playerMove == ENTER_BUILDING){
            if(map.mapArr[mapInfo->playerLocation.rowNum][mapInfo->playerLocation.colNum] == 'M' || map.mapArr[mapInfo->playerLocation.rowNum][mapInfo->playerLocation.colNum] == 'C'){
                inBuilding();
                return 10;
            }
           else{
               //Display Error Message
                move(0,0);
                clrtoeol();
                printw("You cannot enter as you aren't at a building");
           }
        }
        else{
            int cost = movePlayer(playerMove,player,map,mapInfo);
            if(cost != -1){
                return cost;
            }
        }
    }
}

/**
 * @brief Moves the player character on the map based on user input
 * 
 * @param move The move to make
 * @param player The player struct
 * @param map The map to move on
 * @param mapInfo The maps corresponding info struct
 * @return The cost of the move
 */
int movePlayer(playerMoves_t playerMove, GameCharacter* player, mapTile_t map,NPCMapInfo* mapInfo){
    Point newPos;

    switch (playerMove)
    {
    case UP_LEFT:
        newPos = Point(player->rowNum -1,player->colNum -1);
        break;
    case UP:
        newPos = Point(player->rowNum -1,player->colNum);
        break;
    case UP_RIGHT:
        newPos = Point(player->rowNum -1,player->colNum +1);
        break;
    case RIGHT:
        newPos = Point(player->rowNum,player->colNum +1);
        break;
    case DOWN_RIGHT:
        newPos = Point(player->rowNum +1,player->colNum +1);
        break;
    case DOWN:
        newPos = Point(player->rowNum +1,player->colNum);
        break;
    case DOWN_LEFT:
        newPos = Point(player->rowNum +1,player->colNum -1);
        break;
    case LEFT:
        newPos = Point(player->rowNum,player->colNum -1);
        break;
    default:
        break;

    }


    
    std::string illegalChars = "%%\"~";

    //If theres a trainer at the location to move to
    if(mapInfo->charLocations[newPos.rowNum][newPos.colNum].type != 'X'){
        if(checkTrainerDefeated(mapInfo->charLocations[newPos.rowNum][newPos.colNum].id,*mapInfo) ==  0){
             trainerBattle(mapInfo->charLocations[newPos.rowNum][newPos.colNum],mapInfo);
        }
        return costOfPlayerMove(map.mapArr[newPos.rowNum][newPos.colNum]);
    }
    //If the move is illegal
    else if(illegalChars.find(map.mapArr[newPos.rowNum][newPos.colNum]) != std::string::npos){
        displayPlayerMoveError(map.mapArr[newPos.rowNum][newPos.colNum]);
        return -1;
    }

    //Hold player location
    Point temp = Point(player->rowNum,player->colNum);

    //Changes the player's location within its struct
    player->rowNum = newPos.rowNum; 
    player->colNum = newPos.colNum;

    //Moves the player inside the character location array
    mapInfo->charLocations[temp.rowNum][temp.colNum] = GameCharacter();
    mapInfo->charLocations[newPos.rowNum][newPos.colNum] = *player;

    return costOfPlayerMove(map.mapArr[newPos.rowNum][newPos.colNum]);
}

/**
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
            if(mapInfo.charLocations[i][j].type != 'X'){
                Point temp;
                temp.rowNum = i;
                temp.colNum = j;

                NPCList[placeTracker] = GameCharacter(temp,mapInfo.charLocations[i][j].type,0,'.');

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
            int vertDiff = mapInfo.playerLocation.rowNum - currChar.rowNum;
            int horiDiff = mapInfo.playerLocation.colNum - currChar.colNum;

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

            printw("%c: %d %s %d %s ",currChar.type,vertDiff,vertStr,horiDiff,horiStr);
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
