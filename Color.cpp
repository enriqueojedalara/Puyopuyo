#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Color.h"

int Color::random_color(){
	srand (rand() % 50000);
	srand (rand() % 45235);
	int color = rand() % 4;
	int colors[6];
	colors[0] = Color::RED;
	colors[1] = Color::YELLOW;
	colors[2] = Color::GREEN;
	colors[3] = Color::MAGENTA;
	colors[4] = Color::BLUE;
	colors[5] = Color::GRAY;

	return colors[color];
}
