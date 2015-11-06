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

/**
 *The species contains the set of instructions that define a creatures
 *individual behaviour. The valid instructions are as follows:
 * Actions:
 *   hop     moves one space forward
 *   left    changes direction to the left
 *   right   changes direction to the right
 *   infect  infects enemies directly in front
 * Controls:
 *   go x    go to line x
 *   if_empty x go to line x if the place in front is empty
 *   if_enemy x go to line x if the position in front is occupied by an enemy
 *   if_wall x go to line x if the position in front is a wall
 *   if_random x 50% chance that the pc will go to line x. 
 */
class Species {
private:
	/**
	 *vector of instructions the species takes. Each instruction is taken as a string.
	 */
	vector<string> instructions;

	/**
	 *letter that determines a Creature's representation on a grid.
	 */	
	char letter;
public:
	Species(char);

	int execute(Darwin* darwin, Creature* creature, int pc, int direction, int x, int y);
	
	void addInstruction(string i);

	friend std::ostream& operator << (std::ostream& os, const Species& sp)
	{
		os << sp.letter;
		return os;
	}
};

class Creature {

private: 
	int program_counter;
	int direction;

	bool seen;

	Species *sp;
public:

	Creature() {};

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
	void infected(Species* newsp);

	friend bool operator == (const Creature& lhs, const Creature& rhs)
	{
		return lhs.sp == rhs.sp;
	}

	friend ostream& operator << (std::ostream& os, const Creature& cr)
	{
		os << (*cr.sp);
		return os;
	}

};


class Darwin {
private:
	vector < vector <Creature *> >  grid;

	int row;
	int col;

	int forward_x(int direction, int x);
	int forward_y(int direction, int y);

	bool cur_turn = false;
public:
	Darwin(int x, int y);

	void run(int x);
	void hop(int new_x, int new_y, int old_x, int old_y);
	void printGrid();
	void addCreature(Creature *c, int x , int y);
	void infect(Species *s, Creature* c, int x, int y);


	bool enemy(Species* sp, int x,int y);
	bool empty(int x, int y);
	bool is_wall_at(int x, int y);
	bool is_empty(int x, int y);	
	bool is_enemy(Creature* c, int x, int y);

	friend ostream& operator << (std::ostream& os, const Darwin& d)
	{
		os << " ";
		for(int i =0; i < d.row; i++)
		{
			os << i%10;
		}
		os << endl;
		for(int j = 0; j < d.col; j++)
		{
			os << j%10;
			for(int k = 0; k < d.row; k++)
			{
				if(d.grid[j][k] == nullptr)
				{
					os << ".";
				}
				else os << (*d.grid[j][k]);
			}
			os << endl;
		}
		return os;
	}
};




#endif // Darwin_h