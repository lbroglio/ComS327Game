#ifndef CHARACTER_H
#define CHARACTER_H

#include"../Map/map.h"
#include"NPCMapInfo.h"
#include"../Data-Structures/priorityQueue.h"

/**
 * @brief Stores information about the a character. 
 * A default base GameCharacter is a sentry. 
 */
class GameCharacter : public IDable{
    protected:
        /** Row this character is in*/
        int rowNum;
        /** Columns this character is in*/
        int colNum;
        /** Unique id used for indexing this character*/
        int id;
    public:
        /** Char represneting what type of NPC (or player character) this character is*/
        char type;

        /**
         * @brief Creates a new character struct
         * 
         * @param startLoc point the character is at
         * @param type The type of character it is
         * @param id The id to assign it
         */
        GameCharacter(Point startLoc, char type, int id);
        /**
         * @brief Default Constructor - returns the 'Empty' character
         * 
         * 
         */
        GameCharacter();

        /**
         * @brief Destroy the Game Character object
         * 
         */
        virtual ~GameCharacter(){}

        /**
         * @brief Creates a copy of this Character
         * Includes memory allocation returned to the user 
         * 
         * @return A pointer to the created copy
         */
        virtual GameCharacter* clone();

        /**
         * @brief Returns the ID of a given character 
         * 
         * @return The ID
         */
        int getID(){return id;};
        
        /**
         * @brief Gets the row this character is in
         * 
         * @return The row number
         */
        int getRowNum(){return rowNum;}

        /**
         * @brief Gets the column this character is in
         * 
         * @return The column number
         */
        int getColNum(){return colNum;}

        /**
         * @brief Performs the move action for this character
         * 
         * @param map The map the character is on 
         * @return char 
         */
        virtual char move(mapTile_t* map){return '%';}
        /**
         * @brief Set the row number to the provided value
         * 
         * @param newNum The new row number
         */
        void setRowNum(int newNum){rowNum = newNum;}
        /**
         * @brief Set the column number to the provided value
         * 
         * @param newNum The new column number
         */
        void setColNum(int newNum){colNum = newNum;}


        operator GameCharStorage(){return GameCharStorage(this->id,this->type);}
        
};

/**
 * @brief A Wayfinder is a character which moves around the map semi randomly according to preset rules 
 * 
 */
class Wayfinder : public GameCharacter{
    protected:
        /** Stores the current direction this character is moving in as a unit vector.*/
        Point direction;
    public:
        Wayfinder(Point startLoc, char type, int id);
        /**
         * @brief Virutal destructor to Destroy the Wayfinder object
         * 
         */
        virtual ~Wayfinder(){}

        /**
         * @brief Moves this character. Uses character type to determine the next legal move. Also handles engaging player battles. 
         * 
         * @param map The map this character is on
         * @return Char for the type of move (What biome) 
         */
        char move(mapTile_t* map);

        /**
         * @brief Handles the logic for determining if the character can continue moving in the current direction. If not finds the next desirable direction
         * 
         * @param map The map this character is on
         * @return The direction to move in. 
         */
        virtual Point checkDirection(mapTile_t* map) = 0;

        /**
         * @brief Creates a copy of this Character
         * Includes memory allocation returned to the user 
         * 
         * @return A pointer to the created copy
         */
        //virtual GameCharacter* clone(){return GameCharacter::clone();};
};

/**
 * @brief A Pacer is a character which moves forwards until can't anymore and then turns around
 * 
 */
class Pacer : public Wayfinder
{
    public:
        /**
         * @brief Construct a new Pacer object
         * 
         * @param startLoc The location this pacer spawned at
         * @param id The unique ID for this character
         * @param direction The direction this character will start moving in
         */
        Pacer(Point startLoc, int id) :  Wayfinder(startLoc,'p', id) {}

        /**
         * @brief Virutal destructor to Destroy the Pacer object
         * 
         */
        virtual ~Pacer(){}

        /**
         * @brief Handles the logic for determining if the character can continue moving in the current direction. If not finds the next desirable direction
         * 
         * @param map The map this character is on
         * @return The direction to move in. 
         */
        Point checkDirection(mapTile_t* map);

        GameCharacter* clone();
};

/**
 * @brief A Wanderer is a character which moves around and randoml;y changes direction when it find terrain it can't cross. It can't leave its spawn biome
 * 
 */
class Wanderer : public Wayfinder
{   
    private:
        /** Stores the biome this character spawned in.*/
        char spawnBiome;
    protected:
        /**
         * @brief Recusive call for this Characters direction function
         * 
         * @param map The map this chracter is on
         * @param moveOptions Array of possible moves this character could make (As unit vecotrs)
         * @param numOptions The length of move options
         * @return The chosen move
         */
        virtual Point checkDirectionRec(mapTile_t* map, Point moveOptions[], int numOptions);

    public:
        /**
         * @brief Construct a new Wanderer object
         * 
         * @param startLoc The location this Wanderer spawned at
         * @param id The unique ID for this character
         * @param direction The direction this character will start moving in
         */
        Wanderer(Point startLoc, int id,char spawnBiome) :  Wayfinder(startLoc,'w', id){this->spawnBiome = spawnBiome;}
        /**
         * @brief Virutal destructor to Destroy the Wanderer object
         * 
         */
        virtual ~Wanderer(){}

        /**
         * @brief Handles the logic for determining if the character can continue moving in the current direction. If not finds the next desirable direction
         * 
         * @param map The map this character is on
         * @return The direction to move in. 
         */
         Point checkDirection(mapTile_t* map);

         GameCharacter* clone();
};

/**
 * @brief An Explorer is a character which moves around and randomly changes direction when it find terrain it can't cross.
 * 
 */
class Explorer : public Wayfinder
{   
    private:
        /**
         * @brief Recusive call for this Characters direction function
         * 
         * @param map The map this chracter is on
         * @param moveOptions Array of possible moves this character could make (As unit vecotrs)
         * @param numOptions The length of move options
         * @return The chosen move
         */
         Point checkDirectionRec(mapTile_t* map,Point moveOptions[], int numOptions);

    public:
        /**
         * @brief Construct a new Explorer object
         * 
         * @param startLoc The location this Explorer spawned at
         * @param id The unique ID for this character
         * @param direction The direction this character will start moving in
         */
        Explorer(Point startLoc, int id) :  Wayfinder(startLoc,'e', id){}
        /**
         * @brief Virutal destructor to Destroy the Explorer object
         * 
         */
        virtual ~Explorer(){}
        /**
         * @brief Handles the logic for determining if the character can continue moving in the current direction. If not finds the next desirable direction
         * 
         * @param map The map this character is on
         * @return The direction to move in. 
         */
         Point checkDirection(mapTile_t* map);

        
        /**
         * @brief Creates a copy of this Character
         * Includes memory allocation returned to the user 
         * 
         * @return A pointer to the created copy
         */
        virtual GameCharacter* clone();
};

/**
 * @brief A Swimmer is a character which moves around and randomly changes direction when it find terrain it can't cross but it can't move out of the water
 */
class Swimmer : public Wayfinder
{   
    private:
        /**
         * @brief Recusive call for this Characters direction function only applies in wander mode
         * 
         * @param map The map this chracter is on
         * @param moveOptions Array of possible moves this character could make (As unit vecotrs)
         * @param numOptions The length of move options
         * @return The chosen move
         */
         Point checkDirectionRec(mapTile_t* map,Point moveOptions[], int numOptions);
        
        /**
         * @brief Moves the swimmer towards the player. Applies when in charge mod
         * 
         * @param map The map this chracter is on
         * @return The chosen move 
         */
         Point checkDirectionCharge(mapTile_t* map);

    public:
        /**
         * @brief Construct a new Explorer object
         * 
         * @param startLoc The location this Explorer spawned at
         * @param id The unique ID for this character
         * @param direction The direction this character will start moving in
         */
        Swimmer(Point startLoc, int id) :  Wayfinder(startLoc,'m', id){}
        /**
         * @brief Virutal destructor to Destroy the Swimmer object
         * 
         */
        virtual ~Swimmer(){}
        /**
         * @brief Handles the logic for determining if the character can continue moving in the current direction. If not finds the next desirable direction
         * 
         * @param map The map this character is on
         * @return The direction to move in. 
         */
        Point checkDirection(mapTile_t* map);

        GameCharacter* clone();
};

/***
 * @brief A Pathfinder is a character which follows the optimum path to reach the player
 * 
 */
class Pathfinder : public GameCharacter
{
    private:
        //NOTE TO SELF MAYBE REDO THIS WITH VECTOR LATER ***************
        /**
         * @brief Gets all possible moves a Pathfinder Character could make and stores them in an array sorted by distance
         * 
         * @param mapInfo The map the NPC is on 
         * @param possible_moves The array to store the possible moves in
         * @return The number of possible moves
         */
        int getPossibleMoves(mapTile_t map, Point* possibleMoves);
    public:
        Pathfinder(Point startLoc, char type, int id) : GameCharacter(startLoc,type,id){}
        /**
         * @brief Virutal destructor to Destroy the Pathfinder object
         * 
         */
        virtual ~Pathfinder(){}

        /**
         * @brief Moves this character. Uses character type to determine the next legal move. Also handles engaging player battles. 
         * 
         * @param map The map this character is on
         * @return Char for the type of move (What biome) 
         */
        char move(mapTile_t* map);

        /**
         * @brief Creates a copy of this Character
         * Includes memory allocation returned to the user 
         * 
         * @return A pointer to the created copy
         */
        virtual GameCharacter* clone();

        
};




/**
 * @brief Performs the next move in the game. - Takes the given character and handles the logic for moving it
 * 
 * @param toMove Pointer to the character to move 
 * @param time The time of the current move
 * @param player Pointer to the struct containing the information about the player
 * @param map The map tile that the player is currently on
 * @return The cost of the move the npc made
 */

int moveGameChar(GameCharacter* toMove, int time, GameCharacter* player, mapTile_t* map);


/**
 * @brief Checks to see if the trainer with the given ID has been defeated
 * 
 * @param id The id of the trainer to check
 * @param mapInfo The info struct for the current map
 * 
 * @return 0 if the trainer is not defeated. 1 if it is
 */
int checkTrainerDefeated(int id,NPCMapInfo mapInfo);

#endif
