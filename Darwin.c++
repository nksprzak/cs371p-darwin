#include "Darwin.h"
/*
Creature::if_empty(int pc){

	int x_fwd = (!this.direction%2)? this. x + this.direction - 1 : this. x;
	int y_fwd = (this.direction%2)? this. y + this.direction - 2 : this. y;

	if(!this.world->is_wall_at(x_fwd, y_fwd) && !this.world->creature_at(x_fwd, y_fwd))
		this.program_counter = pc;

}

Creature::if_wall(int pc){

	int x_fwd = (!this.direction%2)? this. x + this.direction - 1 : this. x;
	int y_fwd = (this.direction%2)? this. y + this.direction - 2 : this. y;

	if(this.world->is_wall_at(x_fwd, y_fwd))
		this.program_counter = pc;

}

Creature::if_enemy(int pc){

	int x_fwd = (!this.direction%2)? this. x + this.direction - 1 : this. x;
	int y_fwd = (this.direction%2)? this. y + this.direction - 2 : this. y;

	if(!this.world->is_wall_at(x_fwd, y_fwd)){
		Creature c = this.world->creature_at(x_fwd, y_fwd);
		if(!c && c.sp.letter != this.sp.letter)
			this.program_counter = pc;
	}

}*/
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
				if(grid[j][k]) grid[j][k]->turn(this,k,j);
			}
		}
		printGrid();
		cout << endl;
	}
}


int Species::execute(Darwin* darwin, Creature* creature, int pc, int direction, int x, int y)
{
	string exe = instructions[pc];


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
		darwin->hop(direction,x,y);
		return ++pc;
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

	grid[y_fwd][x_fwd] = grid[y][x];
	grid[y][x] = nullptr;
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
void Creature::turn(Darwin* d, int x, int y)
{
	program_counter = sp->execute(d,this,program_counter,direction,x,y);

}

int main()
{
	Darwin z = Darwin(11,11);
	Species food = Species('f');
	food.addInstruction("left");
	food.addInstruction("go 0");
	Creature test = Creature(&food,0);
	z.addCreature(&test,0,0);
	z.run(3);
	z.hop(2,0,0);
	z.printGrid();
	return 0;
}