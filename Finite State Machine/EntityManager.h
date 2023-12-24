#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <cassert>
#include <string>
#include <map>

#define Manager EntityManager::Instance()

class BaseGameEntity;

//A singleton class that represents the manager of the game entities.
class EntityManager{
	
private:
	//Entities map.
	std::map<int, BaseGameEntity*> entitiesMap;

	//Various constructors made private to create a singleton.
	EntityManager(){};
	EntityManager(const EntityManager&);
	EntityManager& operator=(const EntityManager&);

public:
	//A getter method for the instance of this singleton class.
	static EntityManager* Instance();
	//A method that adds a new entity.
	void AddEntity(BaseGameEntity* entityToAdd);
	//A method that removes an exisiting entity.
	void RemoveEntity(BaseGameEntity* entityToRemove);
	//A method that retrieves a BaseGameEntity* from the entities map by a given ID. 
	BaseGameEntity* GetEntityByID(int id);

};

#endif