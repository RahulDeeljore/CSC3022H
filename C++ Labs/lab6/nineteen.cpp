/**
 Inheritance and polymorphic calls
 This minitut is based around implementing an object hierarchy to be used in your own game engine:
       game_object
         +
         +---drawable_game_object
                +
                +---moving_game_object
                        +
                        +---simple_player_interface
                                 +
                                 +---dark_elf
 
 Each successive object extends the core functionality of the object it inherits. Don't concern yourself too much with
 the different attributes of each class here, simply take it that one class adds attributes and behaviour to its parent.
 
 The only real concern is that here the update method accumulates the behaviour of the child and all its predecessors. Calling
 dark_elf's update() should invoke moving_game_object's update(), in turn invoking drawable_game_object's update() all the way up to
 game_object's update(). Each overridden update method will add a bit of functionality after calling update on its parent.

 However, we additionally need to loop over all the game objects, calling the most recently implemented update method. This
 is polymorphism at work (if you don't recall this from first year look at http://www.cplusplus.com/doc/tutorial/polymorphism/)

 Tasks 1-3 are included at the bottom of this cpp file. Compile the code using make and run it using ./tut -s.
*/
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <ostream>
#define CATCH_CONFIG_MAIN //So that catch will define a main method
#include "catch.hpp"

typedef unsigned int uint;
class game_object {
	public:
		uint _ticks_since_creation;
		game_object():
			_ticks_since_creation(0){}
		virtual ~game_object(){}
		virtual void update(){
			++_ticks_since_creation;
		}
};
class drawable_game_object:public game_object {
	public:
		uint _sprite_index;
		uint _num_sprites;
		std::string _texture_atlas_name;
		int _x,_y;
		drawable_game_object(uint num_sprites, const std::string & texture_atlas_name, int x, int y):
			_sprite_index(0),
			_num_sprites(num_sprites),
			_texture_atlas_name(texture_atlas_name),
			_x(x),
			_y(y){}
		~drawable_game_object(){}
		virtual void update(){
			game_object::update();
			_sprite_index = (_sprite_index + 1) % _num_sprites;
		}
		void draw(){
			//STUB:: draw the sprite here
		}
};
enum DIRECTION {EAST, NORTH, WEST, SOUTH};
class moving_drawable_game_object:public drawable_game_object {
	public:
		DIRECTION _direction;
		moving_drawable_game_object(uint num_sprites, const std::string & texture_atlas_name, int x, int y, DIRECTION direction):
			drawable_game_object(num_sprites, texture_atlas_name, x, y),
			_direction(direction){}
		~moving_drawable_game_object(){}
		virtual void update(){
			drawable_game_object::update();
			_x += (_direction == DIRECTION::EAST) ? 1 : (_direction == DIRECTION::WEST) ? -1 : 0;
			_y += (_direction == DIRECTION::NORTH) ? 1 : (_direction == DIRECTION::SOUTH) ? -1 : 0;
		}

};
class simple_player_interface: public moving_drawable_game_object {
	public:
		std::string _name;
		void attack(std::ostream & output, simple_player_interface & obj){
			output << " simple player interface does not know how to attack ";
		}
		simple_player_interface(uint num_sprites, const  std::string & texture_atlas_name, int x, int y, DIRECTION direction, const std::string &character_name):
			_name(character_name),
			moving_drawable_game_object(num_sprites,texture_atlas_name,x,y,direction){}
		~simple_player_interface(){}
	
};

// TASK 1 (See below): Uncomment, fix the constructor and override attack call of the simple_player_interface

class dark_elf: public simple_player_interface {
	public:
                dark_elf(uint num_sprites, const std::string & texture_atlas_name, int x, int y, DIRECTION direction, const std::string &character_name):
                simple_player_interface(num_sprites, texture_atlas_name, x, y, direction, character_name){}
                ~dark_elf(){}
				void attack (std::ostream& output, simple_player_interface& obj) {
					output << _name << " is attacking " << obj._name;
				}
};

TEST_CASE("TESTS",""){
	SECTION("FIX ELF CLASS")
        {
		/**
		 TASK 1: Fix the compilation errors:
		 a: There are no default constructors for the simple_player_interface. How would you call
		 the argument constructor of the parent?
		 b: Override the attack method of the simple player interface and let it print out _name "is attacking" obj._name.
		*/
		
                dark_elf erebath(3,"atlas.bmp",10,-5,DIRECTION::NORTH,"Erebath the Necromancer");
                dark_elf zirkan(3,"atlas2.bmp",10,-4,DIRECTION::SOUTH,"Zirkan the Betrayer");
                std::stringstream stream;
                erebath.attack(stream,zirkan);
                REQUIRE(stream.str() == "Erebath the Necromancer is attacking Zirkan the Betrayer");
				
        }
	SECTION("Test update calls to base classes")
	{
		/**
		 TASK 2: In both the drawable_game_object and moving_drawable_game_object call the update method
		 of the parent class.
		 
		 Goal: if moving_drawable_game_object.update() is called all updates higher up the class hierarchy should be invoked as well.
		*/
		moving_drawable_game_object o(3,"atlas.bmp",0,0,DIRECTION::WEST);
		o.update();
		REQUIRE(o._x == -1);
		o._direction = DIRECTION::EAST;
		o.update();
		REQUIRE(o._x == 0);
		o._direction = DIRECTION::NORTH;
		o.update();
		REQUIRE(o._y == 1);
		o._direction = DIRECTION::SOUTH;
		o.update();
		REQUIRE(o._y == 0);
		REQUIRE(o._sprite_index == 1);
		REQUIRE(o._ticks_since_creation == 4);		
	}
	SECTION("Test polymorphic calls")
	{
		/**
		 TASK 3: Ensure polymorphic calls work. Can you remember what modifier "update" requires to ensure the latest definition is invoked
		 if you only have a base-class-typed pointer?
		 
		 Can you see why polymorphism is useful from the code shown below?
		 In C++11 how can you ensure that polymorphic calls will work on an overridden method? Add this keyword to each update!
		*/
		std::vector<game_object *> obj_list;
		moving_drawable_game_object animal(3,"atlas1.bmp",0,0,DIRECTION::WEST);
		drawable_game_object background(3,"atlas2.bmp",50,0);
		obj_list.push_back(&animal);
		obj_list.push_back(&background);
		//simulate an update loop over all "game objects" (this can range from an animal to the backdrop image):
		for (auto i = obj_list.begin(); i != obj_list.end(); ++i){
			(*i)->update();
		}
		//test if both objects have moved even though we called update on a pointer of type game_object:
		REQUIRE(animal._x == -1); //this one should have moved west
		REQUIRE(background._sprite_index == 1); //the sprite index should have been updated in the drawable object
	}
}

