#include <iostream>
#include "Game.h"

using namespace std;


int main(int argc, char *argv[])
{
	int COLS = 7;
	int ROWS = 12;

	Game game(COLS, ROWS);
	game.init();

    return 0;    
}