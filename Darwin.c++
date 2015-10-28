#include "Darwin.h"

Creature::if_empty(int pc){

	int x_fwd = (!this.direction%2)? this.loc_x + this.direction - 1 : this.loc_x;
	int y_fwd = (this.direction%2)? this.loc_y + this.direction - 2 : this.loc_y;

	if(!this.world->is_wall_at(x_fwd, y_fwd) && !this.world->creature_at(x_fwd, y_fwd))
		this.program_counter = pc;

}

Creature::if_wall(int pc){

	int x_fwd = (!this.direction%2)? this.loc_x + this.direction - 1 : this.loc_x;
	int y_fwd = (this.direction%2)? this.loc_y + this.direction - 2 : this.loc_y;

	if(this.world->is_wall_at(x_fwd, y_fwd))
		this.program_counter = pc;

}

Creature::if_enemy(int pc){

	int x_fwd = (!this.direction%2)? this.loc_x + this.direction - 1 : this.loc_x;
	int y_fwd = (this.direction%2)? this.loc_y + this.direction - 2 : this.loc_y;

	if(!this.world->is_wall_at(x_fwd, y_fwd)){
		Creature c = this.world->creature_at(x_fwd, y_fwd);
		if(!c && c.sp.letter != this.sp.letter)
			this.program_counter = pc;
	}

}