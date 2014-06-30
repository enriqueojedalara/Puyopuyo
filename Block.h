
class Block {
	public:
		int x, y;
		int color;
		bool free;
		bool moving;
		bool readed;
		bool falling;
		bool pivot;
		Block();
		void reset();
		void clone(Block);
};