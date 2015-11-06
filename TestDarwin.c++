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

	two.infect(&food);

	ASSERT_EQ(two.sp,one.sp);
}

TEST(TestCreatureInfect, infect2)
{
	Species food = Species('f');
	Species hop = Species('h');
	Creature two = Creature(&hop,0);

	two.infect(&food);

	ASSERT_EQ(two.program_counter,0);
}

TEST(TestCreatureInfect, infect3)
{
	Species food = Species('f');
	Species hop = Species('h');
	Creature one = Creature(&food,0);
	Creature two = Creature(&hop,0);

	one.infect(&hop);

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
	/*Darwin w = Darwin(1,1);
	
	ostringstream o;
	o << w;*/

	//ASSERT_EQ();
}
TEST(TestDarwinRun, run2)
{
	
}
TEST(TestDarwinRun, run3)
{
	
}