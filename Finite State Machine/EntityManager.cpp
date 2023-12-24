#include "EntityManager.h"
#include "BaseGameEntity.h"

EntityManager* EntityManager::Instance(){

	static EntityManager instance;

	return &instance;

}

void EntityManager::AddEntity(BaseGameEntity* entityToAdd){entitiesMap.insert(std::make_pair(entityToAdd->GetEntityID(), entityToAdd));}

void EntityManager::RemoveEntity(BaseGameEntity* entityToRemove){entitiesMap.erase(entitiesMap.find(entityToRemove->GetEntityID()));}

BaseGameEntity* EntityManager::GetEntityByID(int id){

	assert((entitiesMap.find(id) != entitiesMap.end()) && "<EntityManager::GetEntityByID>: The received id is not bound to any BaseGameEntity*.");

	return entitiesMap.find(id)->second;

}