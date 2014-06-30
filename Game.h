/**
    2014/06/29
    Game.h
    Purpose: 
		
    @author Enrique Ojeda Lara <enriqueojedalara@gmail.com>
    @version 0.1 
*/
#include "Board.h" 

const int COLS = 12;
const int ROWS = 12;

class Game {

	public:
		Board board;

		Game();
		Game(int, int);

		void init();
		void handle_input(SDLKey);

	private:
		Uint32 last_tick;
		Uint32 tick;
		int window_w, window_h;
		bool running;
};