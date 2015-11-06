#include <algorithm>  // count
#include <memory>     // allocator
#include <typeinfo>

#include "gtest/gtest.h"

#include "Darwin.h"

TEST(TestSpeciesConstructor,con1)
{
	Species food = Species('f');
	ASSERT_EQ(0,food.instructions.size());
}
TEST(TestSpeciesConstructor,con2)
{
	Species hopper = Species('h');
	ASSERT_EQ(0,hopper.instructions.size());
}

TEST(TestSpeciesConstructor,con3)
{
	Species rover = Species('r');
	ASSERT_EQ(0,rover.instructions.size());
}


TEST(TestSpeciesExecute, execute1)
{
	Species food = Species('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Darwin world = Darwin(2,2);
    Creature test = Creature(&food,0);

    int t = food.execute(&world,&test,0,0,0,0);
	ASSERT_EQ(t,1);
}

TEST(TestSpeciesExecute, execute2)
{
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

    Darwin world = Darwin(2,2);
    Creature test = Creature(&hopper,0);

    hopper.execute(&world,&test,0,0,0,0);
    int t = hopper.execute(&world,&test,0,0,0,0);
	ASSERT_EQ(t,1);
}

TEST(TestSpeciesExecute, execute3)
{
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
    Darwin world = Darwin(2,2);
    Creature test = Creature(&rover,0);

    int t = rover.execute(&world,&test,0,0,0,0);
	ASSERT_EQ(t,6);
}

TEST(TestSpeciesAdd, add1)
{
	Species food = Species('f');
    food.addInstruction("left");
    ASSERT_EQ(food.instructions[0],"left");
}
TEST(TestSpeciesAdd, add2)
{
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    ASSERT_EQ(hopper.instructions[1],"go 0");
}
TEST(TestSpeciesAdd, add3)
{
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
    ASSERT_EQ(rover.instructions[2],"if_random 5");
}

TEST(TestSpeciesPrint, print1)
{
	Species food = Species('f');
    ostringstream o;  
    o << food;
    ASSERT_EQ(o.str(),"f");
}

TEST(TestSpeciesPrint, print2)
{
	Species rover = Species('r');
    ostringstream o;  
    o << rover;
    ASSERT_EQ(o.str(),"r");
}

TEST(TestSpeciesPrint, print3)
{
	Species hopper = Species('h');
    ostringstream o;  
    o << hopper;
    ASSERT_EQ(o.str(),"h");
}

TEST(TestCreatureConstr,con1)
{
	Species food = Species('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    Creature test = Creature(&food,0);

    ASSERT_EQ(test.sp,&food);

}
TEST(TestCreatureConstr,con2)
{
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

    Creature test = Creature(&hopper,1);
    ASSERT_EQ(test.direction,1);
}
TEST(TestCreatureConstr,con3)
{
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

    Creature test = Creature(&rover,0);
    ASSERT_EQ(test.sp,&rover);
}


TEST(TestCreatureTurn, turn1)
{
	Species food = Species('f');
    food.addInstruction("left");
    food.addInstruction("go 0");
    Creature test = Creature(&food,0);
    Darwin world = Darwin(2,2);
    test.turn(&world,0,0,false);
    ASSERT_TRUE(test.seen);
}


TEST(TestCreatureTurn, turn2)
{
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Darwin world = Darwin(2,2);
    Creature test = Creature(&hopper,0);
    test.turn(&world,0,0,true);
    ASSERT_FALSE(test.seen);
}
TEST(TestCreatureTurn, turn3)
{
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
    Darwin world = Darwin(2,2);
    Creature test = Creature(&rover,0);
    test.turn(&world,0,0,false);
    ASSERT_TRUE(test.seen);
}

TEST(TestCreatureRight, right1)
{
	Species food = Species('f');
    food.addInstruction("left");
    food.addInstruction("go 0");
    Creature test = Creature(&food,0);
    Darwin world = Darwin(2,2);

    test.turn_right();
    ASSERT_EQ(1,test.direction);
}
TEST(TestCreatureRight, right2)
{
	Species food = Species('f');
    food.addInstruction("left");
    food.addInstruction("go 0");
    Creature test = Creature(&food,3);
    Darwin world = Darwin(2,2);

    test.turn_right();
    ASSERT_EQ(0,test.direction);
}
TEST(TestCreatureRight, right3)
{
	Species food = Species('f');
    food.addInstruction("left");
    food.addInstruction("go 0");
    Creature test = Creature(&food,2);
    Darwin world = Darwin(2,2);

    test.turn_right();
    ASSERT_EQ(3,test.direction);
}
TEST(TestCreatureLeft, left1)
{
	Species food = Species('f');
    food.addInstruction("left");
    food.addInstruction("go 0");
    Creature test = Creature(&food,0);
    Darwin world = Darwin(2,2);

    test.turn_left();
    ASSERT_EQ(3,test.direction);
}
TEST(TestCreatureLeft, left2)
{
	Species food = Species('f');
    food.addInstruction("left");
    food.addInstruction("go 0");
    Creature test = Creature(&food,3);
    Darwin world = Darwin(2,2);

    test.turn_left();
    ASSERT_EQ(2,test.direction);
}
TEST(TestCreatureLeft, left3)
{
	Species food = Species('f');
    food.addInstruction("left");
    food.addInstruction("go 0");
    Creature test = Creature(&food,1);
    Darwin world = Darwin(2,2);

    test.turn_left();
    ASSERT_EQ(0,test.direction);
}

TEST(TestCreatureInfect, infect1)
{
	Species food = Species('f');
	Species hop = Species('h');
	Creature one = Creature(&food,0);
	Creature two = Creature(&hop,0);

	two.infected(&food);

	ASSERT_EQ(two.sp,one.sp);
}

TEST(TestCreatureInfect, infect2)
{
	Species food = Species('f');
	Species hop = Species('h');
	Creature two = Creature(&hop,0);

	two.infected(&food);

	ASSERT_EQ(two.program_counter,0);
}

TEST(TestCreatureInfect, infect3)
{
	Species food = Species('f');
	Species hop = Species('h');
	Creature one = Creature(&food,0);
	Creature two = Creature(&hop,0);

	one.infected(&hop);

	ASSERT_EQ(two.sp,one.sp);
}

TEST(TestCreatureEquals, equal1)
{
	Species food = Species('f');
	Species hop = Species('h');
	Creature one = Creature(&food,0);
	Creature two = Creature(&hop,0);

	ASSERT_NE(one.sp,two.sp);
}
TEST(TestCreatureEquals, equal2)
{
	Species food = Species('f');
	Species hop = Species('h');
	Creature one = Creature(&food,0);
	Creature two = Creature(&food,0);

	ASSERT_EQ(one.sp,two.sp);
}
TEST(TestCreatureEquals, equal3)
{
	Species food = Species('f');
	Species rover = Species('r');
	Creature one = Creature(&food,0);
	Creature two = Creature(&rover,0);

	ASSERT_NE(one.sp,two.sp);
}

TEST(TestCreaturePrint, print1)
{
	Species food = Species('f');
	Creature creat = Creature(&food,0);
    ostringstream o;  
    o << creat;
    ASSERT_EQ(o.str(),"f");
}
TEST(TestCreaturePrint, print2)
{
	Species hop = Species('h');
	Creature creat = Creature(&hop,0);
    ostringstream o;  
    o << creat;
    ASSERT_EQ(o.str(),"h");
}
TEST(TestCreaturePrint, print3)
{
	Species rover = Species('r');
	Creature creat = Creature(&rover,0);
    ostringstream o;  
    o << creat;
    ASSERT_EQ(o.str(),"r");
}

TEST(TestDarwinRun, run1)
{
	Darwin w = Darwin(1,1);
	w.run(1);
	ostringstream o;
	o << w;
	ASSERT_EQ(o.str()," 0\n0.\n");
}
TEST(TestDarwinRun, run2)
{
	Darwin w = Darwin(2,1);
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature test = Creature(&hopper,0);
    w.addCreature(&test,0,0);
    w.run(1);
	ostringstream o;
	o << w;
	ASSERT_EQ(o.str()," 01\n0h.\n");
}
TEST(TestDarwinRun, run3)
{
	Darwin w = Darwin(2,3);
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature test = Creature(&hopper,0);
    w.addCreature(&test,0,0);
    w.run(2);
	ostringstream o;
	o << w;
	ASSERT_EQ(o.str()," 01\n0h.\n1..\n2..\n");
}

TEST(TestDarwinHop,hop1)
{
	Darwin w = Darwin(2,2);
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature test = Creature(&hopper,0);
    w.addCreature(&test,0,0);
    w.hop(0,1,0,0);
    ASSERT_EQ(w.grid[1][0],&test);
}
TEST(TestDarwinHop,hop2)
{
	Darwin w = Darwin(3,3);
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature test = Creature(&hopper,0);
    w.addCreature(&test,0,1);
    w.hop(0,2,0,1);
    ASSERT_EQ(w.grid[2][0],&test);
}
TEST(TestDarwinHop,hop3)
{
	Darwin w = Darwin(4,4);
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature test = Creature(&hopper,0);
    w.addCreature(&test,1,1);
    w.hop(0,1,1,1);
    ASSERT_EQ(w.grid[1][0],&test);
}

TEST(TestDarwinAdd,add1)
{
	Darwin w = Darwin(4,4);
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature test = Creature(&hopper,0);
    w.addCreature(&test,0,0);
    ASSERT_EQ(w.grid[0][0],&test);
}
TEST(TestDarwinAdd,add2)
{
	Darwin w = Darwin(4,4);
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature test = Creature(&hopper,0);
    w.addCreature(&test,1,1);
    ASSERT_EQ(w.grid[1][1],&test);
}

TEST(TestDarwinAdd,add3)
{
	Darwin w = Darwin(4,4);
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature test = Creature(&hopper,0);
    w.addCreature(&test,3,2);
    ASSERT_EQ(w.grid[2][3],&test);
}

TEST(TestDarwinInfect, infect1)
{
	Darwin w = Darwin(4,4);
	Species hopper = Species('h');
	Species trap = Species('t');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature att = Creature(&hopper,0);
    Creature vic = Creature(&trap,1);
    w.addCreature(&vic,0,0);
    w.infect(&hopper,&att,0,0);

    ASSERT_EQ(vic.sp,att.sp);
}
TEST(TestDarwinInfect, infect2)
{
	Darwin w = Darwin(4,4);
	Species hopper = Species('h');
	Species trap = Species('t');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature att = Creature(&hopper,0);
    Creature vic = Creature(&trap,1);
    w.addCreature(&vic,0,0);
    w.infect(&hopper,&att,0,0);

    ASSERT_EQ(vic.program_counter,0);
}
TEST(TestDarwinInfect, infect3)
{
	Darwin w = Darwin(4,4);
	Species hopper = Species('h');
	Species trap = Species('t');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature att = Creature(&trap,0);
    Creature vic = Creature(&hopper,1);
    w.addCreature(&vic,0,0);
    w.infect(&trap,&att,0,0);

    ASSERT_EQ(vic.sp,att.sp);
}

TEST(TestDarwinWalls, wall1)
{
	Darwin w = Darwin(4,4);
	ASSERT_FALSE(w.is_wall_at(0,0));
}
TEST(TestDarwinWalls, wall2)
{
	Darwin w = Darwin(4,4);
	ASSERT_TRUE(w.is_wall_at(5,5));
}
TEST(TestDarwinWalls, wall3)
{
	Darwin w = Darwin(3,3);
	ASSERT_TRUE(w.is_wall_at(4,4));
}

TEST(TestDarwinEmpty, empty1)
{
	Darwin w = Darwin(2,2);
	ASSERT_TRUE(w.is_empty(0,0));
}
TEST(TestDarwinEmpty, empty2)
{
	Darwin w = Darwin(2,2);
	Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Creature test = Creature(&hopper,0);
    w.addCreature(&test,0,0);
	ASSERT_FALSE(w.is_empty(0,0));
}

TEST(TestDarwinEmpty, empty3)
{
	Darwin w = Darwin(1,2);
	ASSERT_TRUE(w.is_empty(0,0));
}

TEST(TestDarwinEnemy, enemy1)
{
	Darwin w = Darwin(4,4);
	Species hopper = Species('h');
	Species trap = Species('t');
	Creature att = Creature(&trap,0);
    Creature vic = Creature(&hopper,1);
    w.addCreature(&vic,0,0);
    w.addCreature(&att,1,0);

    ASSERT_TRUE(w.is_enemy(&vic,1,0));
}
TEST(TestDarwinEnemy, enemy2)
{
	Darwin w = Darwin(4,4);
	Species trap = Species('t');
	Creature att = Creature(&trap,0);
    Creature vic = Creature(&trap,1);
    w.addCreature(&vic,0,0);
    w.addCreature(&att,1,0);

    ASSERT_FALSE(w.is_enemy(&vic,1,0));
}

TEST(TestDarwinEnemy, enemy3)
{
	Darwin w = Darwin(4,4);
	Species hopper = Species('h');
	Species trap = Species('t');
	Creature att = Creature(&trap,0);
    Creature vic = Creature(&hopper,1);
    w.addCreature(&vic,1,0);
    w.addCreature(&att,2,0);

    ASSERT_TRUE(w.is_enemy(&vic,2,0));
}

TEST(TestDarwinPrints, print1)
{
	Darwin w = Darwin(4,4);
	ostringstream o;
	o << w;
	ASSERT_EQ(o.str()," 0123\n0....\n1....\n2....\n3....\n");
}
TEST(TestDarwinPrints, print2)
{
	Darwin w = Darwin(4,4);
	Species hopper = Species('h');
	Species trap = Species('t');
	Creature att = Creature(&trap,0);
    Creature vic = Creature(&hopper,1);
    w.addCreature(&vic,0,0);
    w.addCreature(&att,1,0);
    ostringstream o;
	o << w;
	ASSERT_EQ(o.str()," 0123\n0ht..\n1....\n2....\n3....\n");
}
TEST(TestDarwinPrints, print3)
{
	Darwin w = Darwin(5,5);
	ostringstream o;
	o << w;
	ASSERT_EQ(o.str()," 01234\n0.....\n1.....\n2.....\n3.....\n4.....\n");
}

TEST(TestDarwinConstru, con1)
{
	Darwin w = Darwin(2,2);
	ASSERT_EQ(w.row,2);
}
TEST(TestDarwinConstru, con2)
{
	Darwin w = Darwin(2,2);
	ASSERT_EQ(w.col,2);
}
TEST(TestDarwinConstru, con3)
{
	Darwin w = Darwin(11,11);
	ASSERT_EQ(w.row,11);
}

TEST(TestDarwinIterator, it1)
{
    Darwin w = Darwin(4,4);
    ASSERT_EQ(w.begin(),w.end());
}

TEST(TestDarwinIterator, it2)
{
    Darwin w = Darwin(4,4);
    Species hopper = Species('h');
    Creature c = Creature(&hopper, 1);
    w.addCreature(&c,0,0);
    vector<Creature*>::iterator it = w.begin();
    ostringstream o;
    o << **it;
    ASSERT_EQ("h", o.str());
}

TEST(TestDarwinIterator, it4)
{
    Darwin w = Darwin(4,4);
    Species hopper = Species('h');
    Species rover = Species('r');
    Creature c = Creature(&hopper, 1);
    Creature c2 = Creature(&rover,1);
    w.addCreature(&c,0,0);
    w.addCreature(&c2,0,1);
    vector<Creature*>::iterator it = w.begin();
    ostringstream o;
    o << **it;
    ASSERT_EQ("h", o.str());
}

TEST(TestDarwinIterator, it5)
{
    Darwin w = Darwin(4,4);
    Species hopper = Species('h');
    Species rover = Species('r');
    Creature c = Creature(&hopper, 1);
    Creature c2 = Creature(&rover,1);
    w.addCreature(&c,0,0);
    w.addCreature(&c2,0,1);
    ostringstream o;
    for(vector<Creature*>::iterator it = w.begin(); it != w.end(); ++it)
    {
        o << **it;
    }
    ASSERT_EQ("hr", o.str());
}

TEST(TestDarwinAt, at1)
{
    Darwin w = Darwin(4,4);
    Species hopper = Species('h');
    Creature c = Creature(&hopper, 1);
    w.addCreature(&c,0,0);
    ASSERT_EQ(w.at(0),&c);

}

TEST(TestDarwinIterator, at2)
{
    Darwin w = Darwin(4,4);
    Species hopper = Species('h');
    Species rover = Species('r');
    Creature c = Creature(&hopper, 1);
    Creature c2 = Creature(&rover,1);
    w.addCreature(&c,0,0);
    w.addCreature(&c2,0,1);
    ASSERT_EQ(w.at(1),&c2);
}