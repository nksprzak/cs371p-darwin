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
#include <sstream>


#ifndef Darwin_h
#define Darwin_h

using namespace std;

class Darwin;
class Creature;

class Species {
public:
	vector<string> instructions;

	char letter;

	Species(char);

	int execute(Darwin* darwin, Creature* creature, int pc, int direction, int x, int y);

	void addInstruction(string i);
};


class Creature {

public:
	int program_counter;
	int direction;

	bool seen;

	Species *sp;

	Creature(Species *s, int direction) {
		sp = s;
		this->direction = direction;
		program_counter = 0;
		seen = false;
	}

	void turn(Darwin* d, int x, int y);

	void turn_left();
	void turn_right();
	void go(int x);
};


class Darwin {
private:
	//vector<vector<Creature > > grid;

	vector < vector <Creature *> >  grid;
	

	int row;
	int col;
public:

	Darwin(int x, int y);

	void printGrid();

	void addCreature(Creature *c, int x , int y);

	void infect(Creature *c, int x, int y);

	bool enemy(Species* sp, int x,int y);

	bool empty(int x, int y);

	void run(int x);

	void creature_turn(Creature *c, int x, int y);

	void hop(int direction, int x, int y);

	bool is_wall_at(int x, int y);

	Creature creature_at(int x, int y);


};




#endif // Darwin_h