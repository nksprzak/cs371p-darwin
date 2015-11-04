// --------
// includes
// --------

#include <cassert>    // assert
#include <cstddef>    // ptrdiff_t, size_t
#include <new>        // bad_alloc, new
#include <stdexcept>  // invalid_argument
#include <iostream>
#include <vector>
#include <cstdlib>


#ifndef Darwin_h
#define Darwin_h

using namespace std;

class Darwin;
class Creature;

class Species {
private:
	vector<string> instructions;
public:
	char letter;

	Species(char);

	int execute(Darwin* darwin, Creature* creature, int pc, int direction, int x, int y);

	void addInstruction(string i);
};


class Creature {
public:
	Species *sp;
	int program_counter;
	int direction;

	Creature(Species *s, int direction) {
		sp = s;
		this->direction = direction;
		program_counter = 0;
	}

	void turn(Darwin* d, int x, int y);

	void turn_left();
	void turn_right();

/*private:
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
	void infect(Creature i);*/
};


class Darwin {
public:
	//vector<vector<Creature > > grid;

	vector < vector <Creature *> >  grid;
	

	int row;
	int col;

	Darwin(int x, int y);

	void printGrid();

	void addCreature(Creature *c, int x , int y);

	void run(int x);

	void hop(int direction, int x, int y);

	bool is_wall_at(int x, int y);

	Creature creature_at(int x, int y);


};




#endif // Darwin_h