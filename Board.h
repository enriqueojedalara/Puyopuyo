/**
    2014/06/29
    Board.h
    Purpose: 
		
    @author Enrique Ojeda Lara <enriqueojedalara@gmail.com>
    @version 0.1 
*/
#include "SDL.h" 
#include "SDL_TTF.h"
#include "Block.h"
#include "Color.h"
#include <iostream>
#include <vector>

using namespace std;

static const int MARGIN = 10;
static const int PUYO_WIDTH = 48;
static const int PUYO_HEIGHT = 48;

enum Direction{ LEFT = 0, RIGHT, UP, DOWN, FLIP};
enum State{ STARTING=0, FALLING_BLOCK, DELETETING, ORDERING, PAUSE, GAMEOVER, EXIT, WAITING, PRESSING_KEY, SORTING_BLOCKS, DELETING_BLOCKS};

class Board{
	public:
		int* active_blocks;
		State current_state;
		State saved_state;
		bool gameover;
		bool moving;
		bool falling;
		int score;
		bool keyboard;

		void draw_screen_title();
		void draw_screen_board();
		void draw_screen_scores();
		void draw_screen_gameover();
		void draw_screen_pause();
		void calculate_screen_size();
		void refresh_score(int);

		void reset(const int, const int);
		void reset();

		bool search_puyos();
		int find_connected(Block &);



		Board();
		Board(int, int);
		int* window_size();

		void init();
		void init(SDL_Surface*);
		void render_block(Block, int);
		void key_press(SDLKey);
		void draw_blocks();
		void paint();
		void render();
		void reach_bottom(int, int);
		void sorting_blocks();
		
		void falling_new_block();

		bool is_outofmargins(int, int);
		bool blocking_pieces(int, int);
		bool is_gameover(int, int);

		bool clear_connected_blocks();
		

		void update_board();
		void moving_blocks_falling();

		bool update_falling();
		void move(Block, int);
		bool redraw_block(Block, Block);

		bool update_falling2();
		

	private:
		
		
		int width_px, heigth_px, cols, rows;
		std::vector<Block> current_blocks;
		std::vector<Block> blocks_connected;
		std::vector< std::vector<Block> > blocks_erase;
		SDL_Surface* screen;
		Block **board;

		bool is_block_falling();
		
		
};