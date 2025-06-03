#pragma once
#include <vector>
#include <list>
#include "GameObject.h"

class GameLogic
{
public: 
	static void init();
	static void begin();
	static void update(sf::RenderWindow& window, float deltaTime);

	static void gameOver();

	static std::vector<GameObject*> objects;  // G��wna lista obiekt�w
	static std::list<std::vector<GameObject*>::const_iterator> toRemoveList; // Obiekty do usuni�cia
	static std::list<GameObject*> toAddList; // Obiekty do dodania

	static size_t score;

private:
	static float asteroidSpawnTime;
	static sf::Text scoreText;
	static sf::Font font;
	static bool isGameOver;
};

