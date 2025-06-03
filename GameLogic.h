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

	static std::vector<GameObject*> objects;  // G³ówna lista obiektów
	static std::list<std::vector<GameObject*>::const_iterator> toRemoveList; // Obiekty do usuniêcia
	static std::list<GameObject*> toAddList; // Obiekty do dodania

	static size_t score;

private:
	static float asteroidSpawnTime;
	static sf::Text scoreText;
	static size_t highScore;
	static sf::Text highScoreText;
	static sf::Font font;
	static sf::Text gameOverText;
	static sf::Text continueText;
	static sf::Text exitText;
	static sf::Text titleText;
	static sf::Text playText;
	static sf::Text menuText;

	static enum State { MENU, PLAYING, GAME_OVER, ENTERING_NAME } state;

};