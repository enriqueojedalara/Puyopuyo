/**
    2014/06/29
    Color.h
    Purpose: Generate random colors used in the game, the colors have to be defined in HEX
		
    @author Enrique Ojeda Lara <enriqueojedalara@gmail.com>
    @version 0.1 
*/

#ifndef COLOR_H_
#define COLOR_H_

class Color{
	public:
		static const int WHITE = 0xFFFFFF;
		static const int BLACK = 0x000000;
		static const int RED = 0xFF0000;
		static const int GREEN = 0x00CC00;
		static const int MAGENTA = 0x99FFFF;
		static const int YELLOW = 0xFFFF00;
		static const int BLUE = 0x000099;
		static const int GRAY = 0x333333;

		static int random_color();
};
#endif