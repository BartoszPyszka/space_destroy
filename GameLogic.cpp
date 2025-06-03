#include "GameLogic.h"
#include "Asteroid.h"
#include "Player.h"

std::vector<GameObject*> GameLogic::objects{};  
std::list<std::vector<GameObject*>::const_iterator> GameLogic::toRemoveList{};
std::list<GameObject*> GameLogic::toAddList{};
float GameLogic::asteroidSpawnTime{};
size_t GameLogic::score{};
size_t GameLogic::highScore{};
sf::Text GameLogic::scoreText{};
sf::Font GameLogic::font{}; 
sf::Text GameLogic::gameOverText{};
sf::Text GameLogic::continueText{};
GameLogic::State GameLogic::state{};
sf::Text GameLogic::exitText{};
sf::Text GameLogic::titleText{};
sf::Text GameLogic::playText{};
sf::Text GameLogic::menuText{};
sf::Text GameLogic::highScoreText{};


void GameLogic::init()
{
    font.loadFromFile("font.ttf");

    scoreText.setFont(font);
    scoreText.setPosition(sf::Vector2f(10, 10));
    scoreText.setCharacterSize(40);

    gameOverText.setFont(font);
    gameOverText.setPosition(sf::Vector2f(250, 200));
    gameOverText.setCharacterSize(80);
    gameOverText.setString("Game Over!");

    continueText.setFont(font);
    continueText.setPosition(sf::Vector2f(180, 500));
    continueText.setCharacterSize(30);
    continueText.setString("Press B to continue...");

    titleText.setFont(font);
    titleText.setPosition(sf::Vector2f(250, 200));
    titleText.setCharacterSize(80);
    titleText.setString("Space Destroy!!!");

    playText.setFont(font);
    playText.setPosition(sf::Vector2f(400, 500));
    playText.setCharacterSize(20);
    playText.setString("Press P to play");

    exitText.setFont(font);
    exitText.setPosition(sf::Vector2f(10, 10));
    exitText.setCharacterSize(30);
    exitText.setString("Press Esc to exit");

    menuText.setFont(font);
    menuText.setPosition(sf::Vector2f(140, 540));
    menuText.setCharacterSize(30);
    menuText.setString("Press E to return to menu");

    highScoreText.setFont(font);
    highScoreText.setPosition(sf::Vector2f(10, 850));
    highScoreText.setCharacterSize(30);
    highScoreText.setString("High Score: " + std::to_string(highScore));

    state = MENU;

}

void GameLogic::begin() {

    state = PLAYING;
    objects.push_back(new Player());
    asteroidSpawnTime = ASTEROID_SPAWN_TIME;
    score = 0;
}

void GameLogic::update(sf::RenderWindow& window, float deltaTime) {

    if (state == MENU)
    {
        window.draw(playText);
        window.draw(titleText);
        window.draw(exitText);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            begin();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        return;
    }

    toAddList.clear();
    toRemoveList.clear();

    asteroidSpawnTime -= deltaTime;

    // Aktualizacja i rysowanie obiektów
    for (GameObject* obj : GameLogic::objects) {
        obj->update(deltaTime);
        obj->render(window);
    }

    // Usuwanie
    for (const auto& it : GameLogic::toRemoveList) {
        delete* it;
        GameLogic::objects.erase(it);
    }

    // Dodawanie
    for (GameObject* obj : GameLogic::toAddList) {
        GameLogic::objects.push_back(obj);
    }

    // Dodanie nowej asteroidy co jakiœ czas
    if (asteroidSpawnTime <= 0.0f) {
        GameLogic::objects.push_back(new Asteroid());
        asteroidSpawnTime = ASTEROID_SPAWN_TIME;
    }

    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && state == PLAYING)
    {
        state = MENU;
    }

    if (state == GAME_OVER)
    {
        objects.clear();
        window.draw(gameOverText);
        window.draw(continueText);
        window.draw(menuText);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            begin();

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            state = MENU;
        }
    }
}

void GameLogic::gameOver()
{
    state = GAME_OVER;
}
    
