#include "Darwin.h"

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
			//assert(grid[j][k]);
			if(grid[j][k] == nullptr)
			{
				cout << ".";
			}
			else cout << grid[j][k]->sp->letter;
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



void Darwin::infect(Species* sp, int x, int y)
{
	if(!is_wall_at(x, y))
	{
		if(is_empty(x,y)) //should be is_enemy
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
		
	// int x_fwd, y_fwd;
	// if(direction%2 == 0)
	// {
	// 	x_fwd = x + direction - 1;
	// 	y_fwd = y;
	// }
	// else 
	// {
	// 	x_fwd = x;
	// 	y_fwd = y + direction - 2;
	// }


	// cout << x_fwd << " " << y_fwd << endl;
	// if(y_fwd == row || x_fwd == col) cout << "";


	// else if( !(y_fwd < 0 || x_fwd < 0 || x_fwd >= col || y_fwd <=row) grid[y_fwd][x_fwd] == 0)
	// {
	// 	grid[y_fwd][x_fwd] = grid[y][x];
	// 	grid[y][x] = nullptr;
	// }
	
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
					cout << j << " " << k << endl;
					
					grid[j][k]->turn(this,k,j, cur_turn);
					//grid[j][k]->seen = true;
				} 
			}
		}
		cur_turn = !cur_turn;
		// for(int j = 0; j < row; j++)
		// {
		// 	for(int k = 0; k < col; k++)
		// 	{
		// 		if(grid[j][k])
		// 		{
		// 			grid[j][k]->seen = false;
		// 		}		// 	}
		// }
		printGrid();
		cout << endl;
	}
}

bool Darwin::is_enemy(int x, int y, Creature* c)
{
	return false;
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


/*string Creature::control(string contr, int pc_change)
{
	if(contr == "go")
	{
		program_counter = pc_change;
	}
}*/


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
			cout << word << endl;
		}

		//cout << creature->program_counter;
		if(exe_parsed[0] == "go")
		{
			pc = stoi(exe_parsed[1]);
			//exe = stoi(instructions[exe_parsed[1]]);
		}

		if(exe_parsed[0] == "if_enemy")
		{
			cout << "enemy check" << endl;
			if(darwin->is_enemy(x_fwd, y_fwd, creature))
				pc = stoi(exe_parsed[1]);
			else ++pc;
			//return 
		}
		if(exe_parsed[0] == "if_empty")
		{
			cout << "empty check" << endl;
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
			darwin->infect(this,x_fwd,y_fwd);
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


int main()
{
	Darwin z = Darwin(8,8);

	Species food = Species('f');
	food.addInstruction("left");
	food.addInstruction("go 0");

	Species hopper = Species('h');
	hopper.addInstruction("hop");
	hopper.addInstruction("go 0");

	Species rover = Species('r');
	rover.addInstruction("if_enemy 9");
	rover.addInstruction("if_empty 7");
	rover.addInstruction("if_random 5");
	rover.addInstruction("left");
	rover.addInstruction("go 0");
	rover.addInstruction("right");
	rover.addInstruction("go 0");
	rover.addInstruction("hop");
	rover.addInstruction("go 0");
	rover.addInstruction("infect");
	rover.addInstruction("go 0");

	Species trap = Species('t');
	trap.addInstruction("if_enemy 3");
	trap.addInstruction("left");
	trap.addInstruction("go 0");
	trap.addInstruction("infect");
	trap.addInstruction("go 0");


	Creature f1 = Creature(&food,2);
	Creature h1 = Creature(&hopper,1);
	Creature h2 = Creature(&hopper,2);
	Creature h3 = Creature(&hopper,3);
	Creature h4 = Creature(&hopper,0);
	Creature f2 = Creature(&food,1);

	z.addCreature(&f1,0,0);
	z.addCreature(&h1,3,3);
	z.addCreature(&h2,4,3);
	z.addCreature(&h3,4,4);
	z.addCreature(&h4,3,4);
	z.addCreature(&f2,7,7);
	//z.run(5);




	Darwin z2 = Darwin(9,7);
	Creature t1 = Creature(&trap,3);
	Creature t2 = Creature(&trap,0);
	Creature r1 = Creature(&rover,1);

	z2.addCreature(&t1,0,0);
	z2.addCreature(&h2,2,3);
	z2.addCreature(&r1,4,5);
	z2.addCreature(&t2,8,6);

	z2.run(5);

	//z.addCreature(Creature(&food,2)0,0);


	/*Creature test = Creature(&food,0);
	Creature test1 = Creature(&food,0);


	z.addCreature(&test,0,0);
	z.addCreature(&test1,1,0);


	z.run(3);
	z.hop(2,0,0);
	z.printGrid();*/
	return 0;
}