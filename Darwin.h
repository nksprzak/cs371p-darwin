// --------
// includes
// --------

#include <cassert>    // assert
#include <cstddef>    // ptrdiff_t, size_t
#include <new>        // bad_alloc, new
#include <stdexcept>  // invalid_argument


#ifndef Darwin_h
#define Darwin_h

using namespace std;

class Creature {
public:
	Species sp;
	int loc_x;
	int loc_y;
	int program_counter;
	int direction;
	Darwin* world

	Creature(Darwin* d, Species s, int direction, int x, int y) {
		world = d;
		sp = s;
		this.direction = direction;
		loc_y = y;
		loc_x = x;
		program_counter = 0;
	}


private:
	void if_empty(int pc);
	void if_wall(int pc);
	void if_random(int pc){
		if(rand()%2)
			program_counter = pc; 
	}
	void if_enemy(int pc);
	void hop();
	void right();
	void left();
	void infect(Creature i);
};

class Species {
private:
	vector<string> instructions;
public:
	char letter;

	Species();

	void addInstruction(string i);
};

class Darwin {
public:
	//Creature* grid;
	vector<vector<Creature>> grid;
	

	Darwin(int x, int y);

	void printGrid();

	bool is_wall_at(int x, int y);

	Creature creature_at(int x, int y);


};




#endif // Darwin_h