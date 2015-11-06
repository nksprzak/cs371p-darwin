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

#include "gtest/gtest.h"


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
	FRIEND_TEST(TestSpeciesAdd, add1);
	FRIEND_TEST(TestSpeciesAdd, add2);
	FRIEND_TEST(TestSpeciesAdd, add3);
	FRIEND_TEST(TestSpeciesConstructor,con1);
	FRIEND_TEST(TestSpeciesConstructor,con2);
	FRIEND_TEST(TestSpeciesConstructor,con3);
public:
	Species(char);

	int execute(Darwin* darwin, Creature* creature, int pc, int direction, int x, int y);
	
	void addInstruction(string i);


	/**
	 *allows a ostream representation of the Species, which is the letter of its species.
	 *@param os, ostream& 
	 *@param sp, species being written to os
	 *@return os, with sp's letter added
	 */
	friend std::ostream& operator << (std::ostream& os, const Species& sp)
	{
		os << sp.letter;
		return os;
	}


};

/**
 *Creatures populate the grid in Darwin. They contain a program counter, which determines
 *which instruction in species to execute.
 */
class Creature {

private: 
	/**
	 *next line in the instructions to execute.
	 */
	int program_counter;
	/**
	 *direction a creature is facing in the grid;
	 *0 = west
	 *1 = north
	 *2 = east
	 *3 = south
	 */
	int direction;

	/**
	 *keeps track of if the creature has taken its turn this round of darwin
	 */
	bool seen;

	/**
	 *pointer to the species the creature belongs to. A creature's behaviour
	 *is determined by its species.
	 */
	Species *sp;

	FRIEND_TEST(TestCreatureTurn, turn1);
	FRIEND_TEST(TestCreatureTurn, turn2);
	FRIEND_TEST(TestCreatureTurn, turn3);
	FRIEND_TEST(TestCreatureRight, right1);
	FRIEND_TEST(TestCreatureRight, right2);
	FRIEND_TEST(TestCreatureRight, right3);
	FRIEND_TEST(TestCreatureLeft, left1);
	FRIEND_TEST(TestCreatureLeft, left2);
	FRIEND_TEST(TestCreatureLeft, left3);
	FRIEND_TEST(TestCreatureInfect, infect1);
	FRIEND_TEST(TestCreatureInfect, infect2);
	FRIEND_TEST(TestCreatureInfect, infect3);
	FRIEND_TEST(TestCreatureEquals, equal1);
	FRIEND_TEST(TestCreatureEquals, equal2);
	FRIEND_TEST(TestCreatureEquals, equal3);


public:
	/**
	 *default constructor for creature
	 */
	Creature() {};

	/**
	 *Constructor for creature
	 *@param s pointer to species for which this creature belongs
	 *@param direction starting direction for the creature
	 */
	Creature(Species *s, int direction) {
		sp = s;
		this->direction = direction;
		program_counter = 0;
		seen = false;
	}

	void turn(Darwin* d, int x, int y, bool turn);
	void turn_left();
	void turn_right();
	void infected(Species* newsp);

	/**
	 *comparison between two Creatures.
	 *@param lhs Creature& being compared
	 *@param rhs Creature& being compared
	 *@return bool true if each creature's species is the same, false otherwise.
	 */
	friend bool operator == (const Creature& lhs, const Creature& rhs)
	{
		return lhs.sp == rhs.sp;
	}

	/**
	 *allows a ostream representation of the Creature, which is the letter of its species.
	 *@param os, ostream& 
	 *@param cr, creature being written to os
	 *@return os, with cr's letter added
	 */
	friend ostream& operator << (std::ostream& os, const Creature& cr)
	{
		os << (*cr.sp);
		return os;
	}


};


class Darwin {
private:
	/**
	 *Grid in which creatures are held onto.
	 */
	vector < vector <Creature *> >  grid;

	vector < Creature * > creatures;
	/**
	 *number of rows in Darwin's grid
	 */
	int row;
	/**
	 *number of columns in Darwin's grid
	 */
	int col;

	/**
	 *Current turn for darwin. Each round it alternates between true and false.
	 *used to determine if a creature has already taken its turn.
	 */
	bool cur_turn = false;

	FRIEND_TEST(TestDarwinHop,hop1);
	FRIEND_TEST(TestDarwinHop,hop2);
	FRIEND_TEST(TestDarwinHop,hop3);

public:
	Darwin(int x, int y);

	void run(int x);
	void hop(int new_x, int new_y, int old_x, int old_y);
	void addCreature(Creature *c, int x , int y);
	void infect(Species *s, Creature* c, int x, int y);
	bool is_wall_at(int x, int y);
	bool is_empty(int x, int y);	
	bool is_enemy(Creature* c, int x, int y);
	std::vector<Creature*>::iterator begin();
	std::vector<Creature*>::iterator end();
	Creature*& at(size_t n);
	
	/**
	 *writes a representation of darwin's graph to the ostream
	 *@param os, ostream& 
	 *@param d, darwin whose graph is being written to os
	 *@return os, with d's graph added
	 */
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