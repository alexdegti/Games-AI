#ifndef ENTITY_NAMES_H
#define ENTITY_NAMES_H

#include <string>

//An enumeration that represents the entities in the game.
enum{
	entityElf = 1,
	entityCentaur = 2,
	entityDwarf = 3
};

//A function that returns a string representation of an entity's name.
inline std::string GetNameOfEntity(int entity){

	switch(entity){
		case 1:{
			return "Verexia the elf";
		}
		case 2:{
			return "Baku the centaur";
		}
		case 3:{
			return "Isgrid the dwarf";
		}
		default:{
			return "Unknown entity";
		}
	}

}

#endif