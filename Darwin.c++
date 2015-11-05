#include "Darwin.h"

void Darwin::printGrid()
{
	cout << " ";
	for(int i =0; i < row; i++)
	{
		cout << i%10;
	}
	cout << endl;
	for(int j = 0; j < row; j++)
	{
		cout << j%10;
		for(int k = 0; k < col; k++)
		{
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

Species::Species(char l) 
{
	letter = l;
}

void Species::addInstruction(string i)
{
	instructions.push_back(i);
}

Darwin::Darwin(int x, int y)
{
	this->row = x;
	this->col = y;
	vector<vector<Creature *>> grida(y,vector<Creature *>(x,nullptr));

	this->grid = grida;
		
}

void Darwin::run(int x)
{
	for(int i = 0; i < x; i++)
	{
		cout << "Turn = " << i << "." << endl;
		for(int j = 0; j < row; j++)
		{
			for(int k = 0; k < col; k++ )
			{
				if(grid[j][k]) creature_turn(grid[j][k],j,k);
			}
		}
		printGrid();
		cout << endl;
	}
}


void Darwin::creature_turn(Creature* c, int x, int y)
{
	int pc = c->program_counter;
	cout << c->sp->instructions[pc] << endl;
	c->program_counter = pc++;
}

void Creature::go(int x)
{
	program_counter = x;
}


/*int Species::execute(Darwin* darwin, Creature* creature, int pc, int direction, int x, int y)
{
	string exe = instructions[pc];
	vector<string> exe_parsed;
	istringstream iss(exe);
	string word;
	int x_fwd, y_fwd;
	if(direction%2 == 0)
	{
		x_fwd = x + direction - 1;
		y_fwd = y;
	}
	else 
	{
		x_fwd = x;
		y_fwd = y + direction - 2;
	}

	while(iss >> word)
	{
		exe_parsed.push_back(word);
		//cout << word << endl;
	}
	//cout << exe_parsed[1];
	if(exe_parsed[0] == "go")
	{
		creature->go(stoi(exe_parsed[1]));
		return 0;
	}
	if(exe == "left")
	{	
		//cout << "afdsaf";
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
		darwin->hop(direction,x,y);
		return ++pc;
	}
	if(exe == "infect")
	{
		darwin->infect(creature,x_fwd,y_fwd);
		return ++pc;
	}

	
}*/

void Darwin::infect(Creature *c, int x, int y)
{
	Creature* to_infect = grid[y][x];

	if(c->sp != to_infect->sp)
	{
		to_infect->sp = c->sp;
	}
}

void Darwin::hop(int direction, int x, int y)
{
	int x_fwd, y_fwd;
	if(direction%2 == 0)
	{
		x_fwd = x + direction - 1;
		y_fwd = y;
	}
	else 
	{
		x_fwd = x;
		y_fwd = y + direction - 2;
	}
	if(grid[y_fwd][x_fwd] == 0 && (y_fwd > 0 || x_fwd > 0))
	{
		grid[y_fwd][x_fwd] = grid[y][x];
		grid[y][x] = nullptr;
	}
	
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
/*void Creature::turn(Darwin* d, int x, int y)
{
	program_counter = sp->execute(d,this,program_counter,direction,x,y);
}*/

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
	/*z.addCreature(&h2,3,4);
	z.addCreature(&h3,4,4);
	z.addCreature(&h4,4,3);
	z.addCreature(&f2,7,7);*/
	z.run(4);

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