# This is a playable Pokemonesque Roguelike game I made as part of my ComS 327 class.

## Features
In the game you can explore a randomly generated map while catching, levelling up, and battling with many different Pokemon.
Map tiles feature a variety of biomes and certain maptiles can favor different landscapes.
The game is written in C++ with the use of the ncurses library to make in playable in the terminal.

## How to play
###Compile and Run
Compile the game using the provided Makefile by typing 'make' into the terminal of a machine with Make and GCC installed.
This will produce the poke327 executable file which can be run with ./poke327

### Controls
You can control the game with the standard Rogueliek controls or the Numpad
The controls map as:
    7 or y - Move diagnolly to the upper left space
    8 or k - Move up one space
    9 or u - Move diagnolly to the upper right space
    6 or l - Move one space to the right.
    3 or n - Move diagnolly to the lower right space.
    2 or j - Move up one space.
    1 or b - Move diagnolly to the lower left.
    4 or h - Move one space to the left 
    > - If on a building (Building's are represented with eother a 'C' or an 'M') enter the building
    < - Exit a building 
    5 or spacebar or . - Rest for a turn. NPCs still move.
    t - Display a list of trainers on the map and their position relative to the player
        The list can be scrolled with the up and down arrows. Exit the list with the 'esc' key
    Q Quit the game. 

    
