/**
    2014/06/29
    Game.cpp
    Purpose: 
		
    @author Enrique Ojeda Lara <enriqueojedalara@gmail.com>
    @version 0.1 
*/
#include "Game.h"
#include <iostream>
using namespace std;

Game::Game(int cols, int rows){
	board = Board(cols, rows);
	int* size = board.window_size();
	window_w = size[0];
	window_h = size[1];
}

void Game::init(){
	//Variable to control the main while (If false the program finish)
	int running = true;

	//Variable to control PAUSEs
	bool pause = false;

	//Ticks
	tick = 1000;

	//Init SDL
	SDL_Init( SDL_INIT_VIDEO );

	//Create main screen using width and height calculated
	SDL_Surface* screen = SDL_SetVideoMode(window_w, window_h, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Puyo puyo Game", 0);
	SDL_Event event;

	//Init TTF Fonts
	TTF_Init();

	//Getting the first tick
	last_tick = SDL_GetTicks();

	//Main iteration (State machine)
	while (running)
	{
		//Read key from keyboard
		SDLKey key_pressed;
		key_pressed = SDLK_f;
		if (SDL_PollEvent(&event)){
			//Quit
			if (event.type == SDL_QUIT) {
				board.current_state = EXIT;
			}
			//Reading the key pressed
			if (event.type == SDL_KEYDOWN){
				key_pressed = event.key.keysym.sym;
				
				//Quit id key pressed is ESC
				if (key_pressed == SDLK_ESCAPE){
					board.current_state = EXIT;
				}
				else if (key_pressed == SDLK_SPACE){
					if (pause == false){
						board.saved_state = board.current_state;
						board.current_state = PAUSE;
						pause = true;
					}
					else{
						board.init(screen);
						board.current_state = board.saved_state;
						pause = false;
					}
				}
			}
		}

		//Start State machine
		switch(board.current_state){
			//First state (Init all in the game)
			case STARTING:
				//Init screen (Draw board, title, score, etc...)
				board.init(screen);
				board.falling_new_block();
				board.draw_blocks();
				board.current_state = FALLING_BLOCK;
				break;
			case FALLING_BLOCK:
				board.update_falling();
				board.current_state = WAITING;
				break;

			case WAITING:
			case PRESSING_KEY:
				if (key_pressed == SDLK_ESCAPE){
					board.current_state = EXIT;
				}

				//board.keyboard is a flag to disable user keyboard events
				if (board.keyboard){
					board.key_press(key_pressed);
				}
				else{
					//Move faster blocks when is falling automatic (one block in stead of two)
					last_tick = 0;
				}

				//Waiting 1 second between each automatic movement (Move block down)
				if(SDL_GetTicks() - last_tick > tick && board.current_state != DELETING_BLOCKS){
					//As the automatic movement is always to down (The key_press(DOWN) is sent)
					board.key_press(SDLK_s);
					last_tick = SDL_GetTicks();
				}
				break;

			case SORTING_BLOCKS:
				if (!board.keyboard){
					last_tick = 0;
				}
				if(SDL_GetTicks() - last_tick > 300){
					if (!board.update_falling2()){
						board.current_state = DELETING_BLOCKS;
						board.search_puyos();
					}
					last_tick = SDL_GetTicks();
				}
				break;

			case DELETING_BLOCKS:
				if (board.clear_connected_blocks()){
					board.current_state = SORTING_BLOCKS;
				}
				else{
					board.falling_new_block();
					board.current_state = WAITING;
				}
				break;


			case EXIT:
				running = false;
				break;

			case GAMEOVER:
				board.draw_screen_gameover();
				if (key_pressed == SDLK_RETURN || key_pressed == SDLK_KP_ENTER){
					board.current_state = STARTING;
					board.reset();
				}
				break;

			case PAUSE:
				board.draw_screen_pause();
				break;
		}

		if (board.current_state != GAMEOVER && board.current_state != PAUSE){
			board.draw_blocks();
		}

		SDL_Flip(screen);
	}
}


void Game::handle_input(SDLKey key_pressed){
	if(key_pressed == SDLK_d){
		int i = 0;
	}
	
}
