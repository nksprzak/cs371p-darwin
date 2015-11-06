#include "Darwin.h"

/**
 *adds a Creature* to darwin's grid
 * @param c Creature* to be added
 * @param x x position on the grid
 * @param y y position on the grid 
 */
void Darwin::addCreature(Creature* c, int x, int y)
{
	grid[y][x] = c;
}

/**
 *checks to see if a location on the grid contains a Creature*
 *@param x x position on the grid
 *@param y y position on the grid
 *@return bool true if the grid's location is nullptr, false otherwise
 */
bool Darwin::is_empty(int x, int y)
{
	 if(!is_wall_at(x, y))
	 	return grid[y][x] == nullptr;
	return false;
}

/**
 *checks to see if a location on the grid is a wall. Walls are defined as
 *locations off the grid
 *@param x x position on the grid
 *@param y y position on the grid
 *@return bool true if the grid's location is invalid, false otherwise
 */
bool Darwin::is_wall_at(int x, int y)
{

	return (x < 0 || x >= col || y < 0 || y >= row);
}


/**
 *infects Creature on a given position of the grid. Infected creatures have
 *their species changed to the infecting creature, and their program_counter reset to 0.
 *@param sp Species* for the Creature to be infected by
 *@param c Creature* of Creature infecting position on the grid
 *@param x x position on the grid
 *@param y y position on the grid
 */
void Darwin::infect(Species* sp, Creature* c, int x, int y)
{
	if(!is_wall_at(x, y))
	{
		if(is_enemy(c, x,y)) //should be is_enemy
			grid[y][x]->infected(sp);
	}
	// Creature* to_infect = grid[y][x];

	// if(c->sp != to_infect->sp)
	// {
	// 	to_infect->sp = c->sp;
	// }
}

/**
 *moves a creature one position forward on the grid. Hop will fail
 *if a creature would move off the grid, or move into another creature
 *@param new_x x position hopping to on the grid
 *@param new_y y position hopping to on the grid
 *@param old_x x position hopping from on the grid
 *@param old_y y position hopping from on the grid
 */
void Darwin::hop(int new_x, int new_y, int old_x, int old_y)
{
	if(!is_wall_at(new_x,new_y))
	{
		
		if(is_empty(new_x, new_y))
		{
		 	grid[new_y][new_x] = grid[old_y][old_x];
			grid[old_y][old_x] = nullptr;
		}
		
	}
	
}

/**
 *Simulates the darwin grid for x turns, priting for the first 10 turns,
 *then every 100 after
 *@param x number of turns 
 */
void Darwin::run(int x)
{

	cout << "Turn = 0." << endl;
	cout << *this << endl;
	cout << endl;

	for(int i = 1; i < x; i++)
	{

		for(int j = 0; j < row; j++)
		{
			for(int k = 0; k < col; k++ )
			{
				//assert(grid[j][k]->seen);
				if(grid[j][k])
				{	
					grid[j][k]->turn(this,k,j, cur_turn);
				} 
			}
		}
		cur_turn = !cur_turn;
		if(i < 10 || !((i+1)%100))
		{
			cout << "Turn = " << i << "." << endl;
			cout << *this << endl;
			cout << endl;	
		}
	}
}

/**
 *constructor for a Darwin object
 *@param x number of collumns in the grid.
 *@param y number of rows in the grid.
 */
Darwin::Darwin(int x, int y)
{
	this->row = x;
	this->col = y;
	vector<vector<Creature *>> grida(y+10,vector<Creature *>(x+10,nullptr));

	this->grid = grida;
		
}

/**
 *Constructor for species. Species starts with an empty instruction vector.
 *@param l char used to represent a given species on the grid.
 */
Species::Species(char l) 
{
	letter = l;
	
}

/**
 *Adds an instruction to the Species. instructions are added to the back of the vector.
 *@param i String containing the instruction to be added.
 */
void Species::addInstruction(string i)
{
	instructions.push_back(i);
}


/** 
 *Checks if the creature at the x,y location on the grid is an enemy of a given creature.
 * Enemys are any creatures that have a different species.
 * @param c Creature* that the creature at the given grid location is compared to
 * @param x x location on the grid
 * @param y y location on the grid
 */
bool Darwin::is_enemy(Creature *c, int x, int y)
{
	Creature& cr = *c;

	if(!is_wall_at(x, y))
		if(!is_empty(x,y))
		{
			Creature& n = *grid[y][x];
			return !(cr == n);
		}
	return false;
}

/**
 *determines which instruction to execute given a pc. Will cycle through instructions
 *until an action (hop, turn_left, turn_right, infect) is executed. 
 *@param darwin Darwin* containing the creature on the grid
 *@param creature Creature pointer to the creature whose instructions are being executed.
 *@param pc integer determining which instruction to execute
 *@param direction integer describing the current facing direction of the creature
 *@param x x position of the creature on the grid.
 *@param y y position of the creature on the grid.
 *@return integer for the next pc to execute.
 */
int Species::execute(Darwin* darwin, Creature* creature, int pc, int direction, int x, int y)
{
	int x_fwd;
	int y_fwd;
	if(direction%2 == 0)
	{
		x_fwd = x + direction - 1;
		y_fwd = y;
	}
	else
	{
		y_fwd = y + direction - 2;
		x_fwd = x;
	}

	string exe = instructions[pc];
	vector<string> exe_parsed;

	string word;
	while(true)
	{
		exe = instructions[pc];
		istringstream iss(exe);
		//cout << exe << endl;
		if(exe_parsed.size())
		{
			exe_parsed.clear();
		}
		while(iss >> word)
		{
			exe_parsed.push_back(word);
			//cout << word << endl;
		}

		//cout << creature->program_counter;
		if(exe_parsed[0] == "go")
		{
			pc = stoi(exe_parsed[1]);
			//exe = stoi(instructions[exe_parsed[1]]);
		}

		if(exe_parsed[0] == "if_enemy")
		{
			//cout << "enemy check" << endl;
			if(darwin->is_enemy(creature, x_fwd, y_fwd))
				pc = stoi(exe_parsed[1]);
			else ++pc;
			//return 
		}
		if(exe_parsed[0] == "if_empty")
		{
			//cout << "empty check" << endl;
			if(darwin->is_empty(x_fwd, y_fwd))
				pc = stoi(exe_parsed[1]);
			else ++pc;
		}
		if(exe_parsed[0] == "if_random")
		{
			if(rand()%2)
				pc = stoi(exe_parsed[1]);
			else ++pc;
		}
		//cout << exe_parsed[1];
		if(exe == "left")
		{
			creature->turn_left();
			return ++pc;
		}
		if(exe == "right")
		{
			creature->turn_right();
			return ++pc;
		}
		if(exe == "hop")
		{
			darwin->hop(x_fwd,y_fwd,x,y);
			return ++pc;
		}
		if(exe == "infect")
		{
			darwin->infect(this, creature, x_fwd,y_fwd);
			return ++pc;
		}	
	}
	

	//return 0;
	
}

/**
 *Changes the creatures direction to the left.
 */
void Creature::turn_left()
{
	direction --;
	if(direction < 0) direction = 3;
}
/**
 *Changes the creatures direction to the right.
 */
void Creature::turn_right()
{
	direction++;
	direction %=4;
}

/**
 *Tell the creature to take its turn. Creatures can only take on turn per round
 * of Darwin.
 * @param d pointer to the Darwin the creature is inside.
 * @param x x position of the creature on the grid.
 * @param y y position of the creature on the grid.
 * @bool turn. Creatures will take a turn only if turn == Creature::seen. Seen alternates every time a creature takes a turn.
 */
void Creature::turn(Darwin* d, int x, int y, bool turn)
{
	if(turn == seen)
	{
		program_counter = sp->execute(d,this,program_counter,direction,x,y);
		seen = !seen;	
	}
}

/**
 *Makes a creature "infected." Infected creatures have their species changed,
 *and their program counter reset.
 *@param newsp new species for the creature.
 **/
void Creature::infected(Species* newsp)
{
	program_counter = 0;
	sp = newsp;
}




