#pragma once
#include <vector>
#include <list>
#include "GameObject.h"

class GameLogic
{
public: 
	static void begin();
	static void update(sf::RenderWindow& window, float deltaTime);

	static std::vector<GameObject*> objects;  // G³ówna lista obiektów
	static std::list<std::vector<GameObject*>::const_iterator> toRemoveList; // Obiekty do usuniêcia
	static std::list<GameObject*> toAddList; // Obiekty do dodania
private:
	static float asteroidSpawnTime;
};

