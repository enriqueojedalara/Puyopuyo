#include "Board.h"
#include "Color.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

Board::Board(){	
}

void Board::reset(){
	reset(this->cols, this->rows);
}

void Board::reset(const int cols, const int rows){
	current_state = STARTING;
	this->cols = cols;
	this->rows = rows;
	board = new Block*[cols];
	for(int i = 0; i < cols; i++){
		board[i] = new Block[rows];
	}

	for(int x = 0;x < cols; x++){
		for(int y = 0;y < rows; y++){
			board[x][y].x = x;
			board[x][y].y = y;
			board[x][y].reset();
		}
	}

	gameover = false;
	falling = true;
	score = 0;
	keyboard = true;
}

//Initialize board properties
Board::Board(const int cols, const int rows){
	reset(cols, rows);
}

// Method to calculate the window size in pixels 
int* Board::window_size(){
	int *size = new int[2];
	size[0] = (MARGIN * 2) + (PUYO_WIDTH * (cols + 3));
	size[1] = (MARGIN * 2) + (PUYO_HEIGHT * (rows + 1) + PUYO_HEIGHT);

	return size;
}

void Board::init(SDL_Surface *screen) {
	this->screen = screen;
	//Calculate screen size in pixels
	calculate_screen_size();

	//Draw game screen
	draw_screen_title();
	draw_screen_board();
	draw_screen_scores();
}

void Board::draw_screen_board(){
	SDL_Rect sdl_board = {MARGIN,  PUYO_HEIGHT + MARGIN, (PUYO_WIDTH * cols), (PUYO_HEIGHT * rows)};
	SDL_FillRect(this->screen , &sdl_board , Color::BLACK);

	TTF_Font* font = TTF_OpenFont("arial.ttf", 18);
	SDL_Color foregroundColor = { 255, 255, 255 }; 
    SDL_Color backgroundColor = { 51, 51, 51 };
	SDL_Rect textLocation = { (PUYO_WIDTH * cols) / 2, MARGIN * 2, 0, 0 }; 
	SDL_Surface* textSurface = TTF_RenderText_Shaded(font, "Puyo puyo", foregroundColor, backgroundColor);
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
}

void Board::draw_screen_title(){
	SDL_Rect sdl_title = {MARGIN, MARGIN, (PUYO_WIDTH * cols) + (PUYO_WIDTH * 3), PUYO_HEIGHT};
	SDL_FillRect(this->screen , &sdl_title , Color::GRAY);

	TTF_Font* font = TTF_OpenFont("arial.ttf", 18);
	SDL_Color foregroundColor = { 255, 255, 255 }; 
    SDL_Color backgroundColor = { 51, 51, 51 };
	SDL_Rect textLocation = { (PUYO_WIDTH * cols) / 2, MARGIN * 2, 0, 0 }; 
	SDL_Surface* textSurface = TTF_RenderText_Shaded(font, "Puyo puyo", foregroundColor, backgroundColor);
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
}

void Board::draw_screen_scores(){
	SDL_Rect sdl_scores = {(PUYO_WIDTH * cols + MARGIN), PUYO_HEIGHT + MARGIN, (PUYO_WIDTH * 3), (PUYO_HEIGHT * rows)};
	SDL_FillRect(this->screen , &sdl_scores , Color::GRAY);

	TTF_Font* font = TTF_OpenFont("arial.ttf", 21);
	SDL_Color foregroundColor = { 255, 255, 255 }; 
    SDL_Color backgroundColor = { 51, 51, 51 };
	SDL_Rect textLocation = { (PUYO_WIDTH * cols + PUYO_WIDTH), PUYO_HEIGHT + MARGIN, 0, 0 }; 
	SDL_Surface* textSurface = TTF_RenderText_Shaded(font, "SCORE", foregroundColor, backgroundColor);
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
}

void Board::refresh_score(int score){
	stringstream ss;
	ss << score;
	std::string result =  ss.str();
	const char * str_score = result.c_str();
	TTF_Font* font = TTF_OpenFont("arial.ttf", 21);
	SDL_Color foregroundColor = { 255, 255, 255 }; 
    SDL_Color backgroundColor = { 51, 51, 51 };
	SDL_Rect textLocation = { (PUYO_WIDTH * cols + PUYO_WIDTH), 2 * PUYO_HEIGHT + MARGIN, 0, 0 }; 
	SDL_Surface* textSurface = TTF_RenderText_Shaded(font, str_score, foregroundColor, backgroundColor);
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
}

void Board::draw_screen_gameover(){
	SDL_Rect sdl_board = {0, 0, width_px, heigth_px};
	SDL_FillRect(this->screen , &sdl_board , Color::BLACK);

	TTF_Font* font = TTF_OpenFont("arial.ttf", 30);
	SDL_Color foregroundColor = { 255, 255, 255 }; 
    SDL_Color backgroundColor = { 255, 00, 00 };
	SDL_Rect textLocation = { (PUYO_WIDTH * cols) / 2, (PUYO_HEIGHT * rows) / 2, 0, 0 }; 
	SDL_Surface* textSurface = TTF_RenderText_Shaded(font, "GAME OVER", foregroundColor, backgroundColor);
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);

	TTF_Font* font2 = TTF_OpenFont("arial.ttf", 19);
	SDL_Rect textLocation2 = { (PUYO_WIDTH * cols) / 2 - PUYO_WIDTH / 2, (PUYO_HEIGHT * rows) / 2 + MARGIN * 3, 0, 0 }; 
	SDL_Surface* textSurface2 = TTF_RenderText_Shaded(font2, "Press ENTER to continue...", foregroundColor, backgroundColor);
	SDL_BlitSurface(textSurface2, NULL, screen, &textLocation2);
}

void Board::draw_screen_pause(){
	SDL_Rect sdl_board = {0, 0, width_px, heigth_px};
	SDL_FillRect(this->screen , &sdl_board , Color::BLACK);

	TTF_Font* font = TTF_OpenFont("arial.ttf", 30);
	SDL_Color foregroundColor = { 255, 255, 255 }; 
    SDL_Color backgroundColor = { 0, 0, 150 };
	SDL_Rect textLocation = { (PUYO_WIDTH * cols) / 2, (PUYO_HEIGHT * rows) / 2, 0, 0 }; 
	SDL_Surface* textSurface = TTF_RenderText_Shaded(font, "GAME PAUSED", foregroundColor, backgroundColor);
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);

	TTF_Font* font2 = TTF_OpenFont("arial.ttf", 19);
	SDL_Rect textLocation2 = { (PUYO_WIDTH * cols) / 2 - PUYO_WIDTH / 2, (PUYO_HEIGHT * rows) / 2 + MARGIN * 3, 0, 0 }; 
	SDL_Surface* textSurface2 = TTF_RenderText_Shaded(font2, "Press SPACE BAR to continue...", foregroundColor, backgroundColor);
	SDL_BlitSurface(textSurface2, NULL, screen, &textLocation2);
}

void Board::calculate_screen_size(){
	width_px = (MARGIN * 2) + (PUYO_WIDTH * (cols + 3) + PUYO_WIDTH);
	heigth_px = (MARGIN * 2) + (PUYO_HEIGHT * (rows + 1) + PUYO_HEIGHT);
}

void Board::falling_new_block(){
	if (board[cols/2][0].free == false|| board[cols/2 + 1][0].free == false){
		current_state = GAMEOVER;
		return;
	}

	if (!is_block_falling() && !gameover){
		if (board[cols/2][0].free && board[cols/2 + 1][0].free){
			board[cols/2][0].color = Color::random_color();
			board[cols/2][0].falling = true;
			board[cols/2][0].moving = true;
			board[cols/2][0].free = false;
			board[cols/2][0].pivot = true;

			board[cols/2 + 1][0].color = Color::random_color();
			board[cols/2 + 1][0].falling = true;
			board[cols/2 + 1][0].moving = true;
			board[cols/2 + 1][0].free = false;
			board[cols/2 + 1][0].pivot = false;

			current_blocks.push_back(board[cols/2][0]);
			current_blocks.push_back(board[cols/2 + 1][0]);
		}
	}
	current_state = WAITING;
}

bool Board::is_block_falling(){
	for(int x = 0; x < cols; x++){
		for(int y = 0; y < rows; y++){
			if (board[x][y].moving){
				return true;
			}
		}
	}
	return false;
}

bool Board::update_falling(){
	bool flag = false;
	for(int x = 0; x < cols; x++){
		for(int y=rows - 1; y >= 0; y--){
			if (y <= 0){
				continue;
			}
			if (board[x][y].falling && !board[x][y].free){
				move(board[x][y], DOWN);
				flag = true;
			}
		}
	}

	return flag;
}

bool Board::update_falling2(){
	bool flag = false;
	for(int x = 0; x < cols; x++){
		for(int y = rows - 2; y >= 0; y--){
			if (board[x][y].free){
				continue;
			}
			if (board[x][y + 1].free){
				move(board[x][y], DOWN);
				flag = true;
			}
		}
	}
	return flag;
}


void Board::move(Block block, int direction){
	if (direction == DOWN){
		if (block.y + 1 < rows && board[block.x][block.y + 1].free){
			redraw_block(block, board[block.x][block.y + 1]);
		}
		else{
			board[block.x][block.y].falling = false;
			board[block.x][block.y].moving = false;
		}
	}
	else if (direction == LEFT){
		if (!keyboard){
			return;
		}
		if (block.x - 1 >= 0 && board[block.x - 1][block.y].free){
			redraw_block(block, board[block.x - 1][block.y]);
		}
	}
	else if (direction == RIGHT){
		if (!keyboard){
			return;
		}
		if (block.x + 1 < cols && board[block.x + 1][block.y].free){
			redraw_block(block, board[block.x + 1][block.y]);
		}
	}
	else if (direction == FLIP){
		if (current_blocks.size() >= 2){
			Block block1 = current_blocks[0];
			Block block2 = current_blocks[1];

		}
	}
}

bool Board::redraw_block(Block block_begin, Block block_end){
	if (!block_end.free){
		return false;
	}
	if (block_end.x < cols && block_end.x >= 0 && block_end.y < rows){
		board[block_end.x][block_end.y].clone(board[block_begin.x][block_begin.y]);
		board[block_begin.x][block_begin.y].reset();

		if (block_end.y >= rows || board[block_end.x][block_end.y].free == false){
			block_end.falling = false;
			block_end.moving = false;
		}
		return true;
	}
}

void Board::render_block(Block block, int color){
	int x = (PUYO_WIDTH) * block.x;
	int y = (PUYO_HEIGHT) * block.y + MARGIN;
	SDL_Rect Rect = {x + MARGIN, y + PUYO_HEIGHT, PUYO_WIDTH, PUYO_HEIGHT};
	SDL_FillRect(this->screen , &Rect , 0x00000);

	SDL_Rect Rect2 = {x + MARGIN + 2, y + PUYO_HEIGHT + 2, PUYO_WIDTH - 4 , PUYO_HEIGHT - 4};
	SDL_FillRect(this->screen , &Rect2 , color);
}

void Board::key_press(SDLKey key_pressed){
	Block block;
	bool flag = false;

	current_blocks.clear();
	for(int x = 0; x < cols; x++){
		for(int y = 0; y < rows; y++){
			if (board[x][y].moving){
				current_blocks.push_back(board[x][y]);
			}
		}
	}

	keyboard = current_blocks.size() == 1 ? false : true;

	if (current_blocks.size() > 0){
		if (key_pressed == SDLK_s){
			if (current_blocks.size() >= 2){
				Block block1 = current_blocks[0];
				Block block2 = current_blocks[1];
				if (block1.y > block2.y){
					move(block1, DOWN);
					move(block2, DOWN);
				}
				else{
					move(block2, DOWN);
					move(block1, DOWN);
				}
			}
			else{
				for each(Block block in current_blocks) {
					move(block, DOWN);
				}
			}
		}
		else if (key_pressed == SDLK_a){
			Block block;
			if (current_blocks.size() > 0){
				block = current_blocks[0];
			}
			move(block, LEFT);
			if (current_blocks.size() > 1){
				block = current_blocks[1];
				move(block, LEFT);
			}
		}
		else if (key_pressed == SDLK_d){
			Block block;
			if (current_blocks.size() > 1){
				block = current_blocks[1];
				move(block, RIGHT);
			}
			block = current_blocks[0];
			move(block, RIGHT);
		}
		else if (key_pressed == SDLK_w){
			if (current_blocks.size() >= 2){
				Block block2;
				Block block1;
				if (current_blocks[0].pivot){
					block1 = current_blocks[0];
					block2 = current_blocks[1];
				}
				else{
					block1 = current_blocks[1];
					block2 = current_blocks[0];
				}

				//Right
				if(block1.x < block2.x && block1.y == block2.y){
					redraw_block(board[block2.x][block2.y], board[block2.x - 1][block2.y - 1]);
				}
				//Left
				else if(block1.x > block2.x && block1.y == block2.y){
					redraw_block(board[block2.x][block2.y], board[block2.x + 1][block2.y + 1]);
				}
				//Up
				else if(block1.x == block2.x && block1.y > block2.y){
					if (block2.x - 1 >= 0){
						redraw_block(board[block2.x][block2.y], board[block2.x - 1][block2.y + 1]);
					}
				}
				//Down
				else{
					if (block2.x + 1 < cols){
						redraw_block(board[block2.x][block2.y], board[block2.x + 1][block2.y - 1]);
					}
				}
			}
		}
	}
	else{

		if (search_puyos()){
			current_state = DELETING_BLOCKS;
		}
		else{
			falling_new_block();
			if (current_state != GAMEOVER)
				current_state = WAITING;
		}
	}
}

void Board::draw_blocks(){
	for(int x = 0; x < cols; x++){
		for(int y = 0; y < rows; y++){
			render_block(board[x][y], board[x][y].color);
		}
	}
}

void Board::init(){
	init(screen);
}

void Board::render(){
	update_falling();
	falling_new_block();
	draw_blocks();
}

void Board::update_board(){
	for(int x = 0; x < cols; x++){
		for(int y=rows - 1; y >= 0; y--){
			if (board[x][y].free){
				continue;
			}
			board[x][y].falling = true;
		}
	}
}

bool Board::is_gameover(int x, int y){
	if (y == 1 && board[x][y+1].free == false){
		return true;
	}
	return false;
}

void Board::moving_blocks_falling(){
	for(int x = 0; x < cols; x++){
		for(int y=rows - 1; y >= 0; y--){
			if (!board[x][y].falling){
				continue;
			}
		}
	}
}

void Board::sorting_blocks(){
	for(int x = 0; x < cols; x++){
		for(int y=rows - 1; y >= 0; y--){
			if (!board[x][y + 1].free){
				continue;
			}
		}
	}
}

bool Board::search_puyos()
{
	bool delete_puyos = false;
	int connecteds = 0;
	for(int x=0;x < cols; x++){
		for(int y=rows; y >= 0; y--){
			if (board[x][y].free == false){
				int connecteds = find_connected(board[x][y]);
				if (blocks_connected.size() >= 4){
					delete_puyos = true;
					blocks_erase.push_back(blocks_connected);
				}
				else{
					std::vector<Block>::iterator it;
					for each(Block b in blocks_connected) {
						board[b.x][b.y].readed = false;
					}
				}
				blocks_connected.clear();
				if (connecteds >= 4){
					//Clear
					//Render
				}
			}
		}
	}
	return delete_puyos;
}

int Board::find_connected(Block &block){
	int connecteds = 0;

	if (!board[block.x][block.y].readed){
		board[block.x][block.y].readed = true;
		blocks_connected.push_back(board[block.x][block.y]);
	}

	if (block.x - 1 > 0 && board[block.x-1][block.y].free == false && !board[block.x-1][block.y].readed){
		if (block.color == board[block.x-1][block.y].color){
			board[block.x-1][block.y].readed = true;
			blocks_connected.push_back(board[block.x-1][block.y]);
			find_connected(board[block.x-1][block.y]);
		}
		//connecteds += find_connected(board[block.x-1][block.y]);
	}

	if (block.y + 1 < rows && board[block.x][block.y + 1].free == false && !board[block.x][block.y + 1].readed){
		if (block.color == board[block.x][block.y + 1].color){
			board[block.x][block.y + 1].readed = true;
			blocks_connected.push_back(board[block.x][block.y + 1]);
			find_connected(board[block.x][block.y + 1]);
		}
	}

	if (block.x + 1 < cols && board[block.x + 1][block.y].free == false && !board[block.x + 1][block.y].readed){
		if (block.color == board[block.x + 1][block.y].color){
			board[block.x + 1][block.y].readed = true;
			blocks_connected.push_back(board[block.x + 1][block.y]);
			find_connected(board[block.x + 1][block.y]);
		}
	}

	if (block.y - 1 > 0 && board[block.x][block.y - 1].free == false && !board[block.x][block.y - 1].readed){
		if (block.color == board[block.x][block.y - 1].color){
			board[block.x][block.y - 1].readed = true;
			blocks_connected.push_back(board[block.x][block.y - 1]);
			find_connected(board[block.x][block.y - 1]);
		}
	}
	return connecteds;
}

bool Board::clear_connected_blocks(){
	bool flag = false;
	bool reorder_blocks = false;
	score = score + blocks_erase.size();
	if (blocks_erase.size() > 0){
		std::vector<Block> blocks = blocks_erase.back();
		blocks_erase.pop_back();
		std::vector<Block>::iterator it;

		score += blocks.size();
		for each(Block b in blocks) {
			for(int i=0;i<rows;i++){
				if (board[b.x][i].free == false){
					board[b.x][i].falling = true;
					reorder_blocks = true;
					flag = true;
				}
			}
			board[b.x][b.y].reset();
		}
	}

	refresh_score(score);

	return flag;
}
