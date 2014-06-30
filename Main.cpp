/**
    2014/06/29
    Main.cpp
    Purpose: Main file (What can I say, it is the main!)
		
    @author Enrique Ojeda Lara <enriqueojedalara@gmail.com>
    @version 0.1 
*/
#include <iostream>
#include "Game.h"

using namespace std;

/**
    Main function (Starting point)

*/
int main(int argc, char *argv[]) {

	//Board columns (It is dynamic, so it could be changed, it is not validated)
	int COLS = 7;

	//Board rows (It is dynamic, so it could be changed, it is not validated)
	int ROWS = 12;

	//Start Game
	Game game(COLS, ROWS);

	//Initialize everything to start
	game.init();

    return 0;    
}