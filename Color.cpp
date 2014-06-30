/**
    2014/06/29
    Color.cpp
    Purpose: Generate random colors used in the game
		
    @author Enrique Ojeda Lara <enriqueojedalara@gmail.com>
    @version 0.1 
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Color.h"

/**
    Return a random color

    @param void
    @return A random color in HEX (Integet).
*/
int Color::random_color(){
	int color;
	int colors[6];

	srand (rand() % rand());
	srand (rand() % rand());
	color = rand() % 4;
	
	colors[0] = Color::RED;
	colors[1] = Color::YELLOW;
	colors[2] = Color::GREEN;
	colors[3] = Color::MAGENTA;
	colors[4] = Color::BLUE;
	colors[5] = Color::GRAY;

	return colors[color];
}
