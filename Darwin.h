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
//private:
public: 
	int program_counter;
	int direction;

	bool seen;

	Species *sp;
public:

	Creature(Species *s, int direction) {
		sp = s;
		this->direction = direction;
		program_counter = 0;
		seen = false;
	}

	void turn(Darwin* d, int x, int y, bool turn);

	void turn_left();
	void turn_right();
	void go(int x);
	void infect(Species* newsp);
//	string control(string contr, int pc_change);

};


class Darwin {
// private:
public:
	//vector<vector<Creature > > grid;

	vector < vector <Creature *> >  grid;
	

	int row;
	int col;

	int forward_x(int direction, int x);
	int forward_y(int direction, int y);

	bool cur_turn = false;
public:

	Darwin(int x, int y);

	void printGrid();

	void addCreature(Creature *c, int x , int y);

	void infect(Species *s, int x, int y);

	bool enemy(Species* sp, int x,int y);

	bool empty(int x, int y);

	void run(int x);

	// void creature_turn(Creature *c, int x, int y);

	void hop(int new_x, int new_y, int old_x, int old_y);

	bool is_wall_at(int x, int y);

	bool is_empty(int x, int y);

	bool is_enemy(int x, int y, Creature* c);

	Creature* creature_at(int direction, int x, int y);


};




#endif // Darwin_h