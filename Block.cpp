#include "Block.h"
#include "Color.h"

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

void Block::reset(){
	color = Color::BLACK;
	free = true;
	moving = false;
	readed = false;
	falling = false;
	pivot = false;
}


void Block::clone(Block block){
	color = block.color;
	free = block.free;
	moving = block.moving;
	pivot = block.pivot;
	readed = block.readed;
	falling = block.falling;
}