/**
    2014/06/29
    Block.cpp
    Purpose: Add behaivor and define the structure of each block
		
    @author Enrique Ojeda Lara <enriqueojedalara@gmail.com>
    @version 0.1 
*/
#include "Block.h"
#include "Color.h"


/**
    Constructor
*/
Block::Block(){
	x = 0;
	y = 0;
	color = Color::BLACK;
	free = true;
	moving = false;
	readed = false;
	falling = false;
	pivot = false;
}


/**
    Reset the block to the default values

	@param void
    @return void
*/
void Block::reset(){
	color = Color::BLACK;
	free = true;
	moving = false;
	readed = false;
	falling = false;
	pivot = false;
}


/**
    Copy properties from a block (Clone)

	@param Block (A Block class)
    @return void
*/
void Block::clone(Block block){
	color = block.color;
	free = block.free;
	moving = block.moving;
	pivot = block.pivot;
	readed = block.readed;
	falling = block.falling;
}