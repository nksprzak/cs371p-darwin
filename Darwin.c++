#include "Darwin.h"





//  std::ostream& operator << (std::ostream& os, Darwin& d)
//  {
//  	d.printGrid(os);
// 	return os;
// }


int Darwin::forward_x(int direction, int x)
{
	if(direction%2 == 0)
		return x + direction - 1;

}

int Darwin::forward_y(int direction, int y)
{
	if(direction%2 == 1)
		return y + direction - 2;
	return y;
}

void Darwin::printGrid()
{
	cout << " ";
	for(int i =0; i < row; i++)
	{
		cout << i%10;
	}
	cout << endl;
	for(int j = 0; j < col; j++)
	{
		cout << j%10;
		for(int k = 0; k < row; k++)
		{
			if(grid[j][k] == nullptr)
			{
				cout << ".";
			}
			else cout << (*grid[j][k]);
		}
		cout << endl;
	}
}

void Darwin::addCreature(Creature* c, int x, int y)
{
	grid[y][x] = c;
}

bool Darwin::is_empty(int x, int y)
{
	 if(!is_wall_at(x, y))
	 	return grid[y][x] == nullptr;
	return false;
}

bool Darwin::is_wall_at(int x, int y)
{

	return (x < 0 || x >= col || y < 0 || y >= row);
}



void Darwin::infect(Species* sp, Creature* c, int x, int y)
{
	if(!is_wall_at(x, y))
	{
		if(is_enemy(c, x,y)) //should be is_enemy
			grid[y][x]->infect(sp);
	}
	// Creature* to_infect = grid[y][x];

	// if(c->sp != to_infect->sp)
	// {
	// 	to_infect->sp = c->sp;
	// }
}

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

void Darwin::run(int x)
{

	cout << "Turn = 0." << endl;
	printGrid();
	cout << endl;

	for(int i = 1; i < x; i++)
	{
		cout << "Turn = " << i << "." << endl;
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
		printGrid();
		cout << endl;
	}
}


Darwin::Darwin(int x, int y)
{
	this->row = x;
	this->col = y;
	vector<vector<Creature *>> grida(y+10,vector<Creature *>(x+10,nullptr));

	this->grid = grida;
		
}

Species::Species(char l) 
{
	letter = l;
}

void Species::addInstruction(string i)
{
	instructions.push_back(i);
}



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

void Creature::turn_left()
{
	direction --;
	if(direction < 0) direction = 3;
}
void Creature::turn_right()
{
	direction++;
	direction %=4;
}
void Creature::turn(Darwin* d, int x, int y, bool turn)
{
	//cout << "turn " << (turn == seen) << endl;
	if(turn == seen)
	{
		// string check = sp->instructions[program_counter];
		// vector<string> parsed;
		// istringstream iss(check);
		// string word;
		// while(iss >> word)
		// {
		// 	parsed.push_back(word);
		// }
		program_counter = sp->execute(d,this,program_counter,direction,x,y);

		//if(parsed[0] == "go" && seen == false) program_counter = sp->execute(d,this,program_counter,direction,x,y);

		seen = !seen;	
	}
	
}

void Creature::infect(Species* newsp)
{
	program_counter = 0;
	sp = newsp;
}


