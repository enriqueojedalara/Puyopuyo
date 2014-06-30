/**
    2014/06/29
    Block.h
    Purpose: Definitions of Block
		
    @author Enrique Ojeda Lara <enriqueojedalara@gmail.com>
    @version 0.1 
*/
class Block {
	public:
		int x, y, color;
		bool free;
		bool moving;
		bool readed;
		bool falling;
		bool pivot;

		// Constructor
		Block();

		//Reset the block to the default values
		void reset();

		//Copy properties from a block (Clone)
		void clone(Block);
};