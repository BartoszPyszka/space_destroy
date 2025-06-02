#include "GameLogic.h"
#include "Asteroid.h"
#include "Player.h"

std::vector<GameObject*> GameLogic::objects{};  
std::list<std::vector<GameObject*>::const_iterator> GameLogic::toRemoveList{};
std::list<GameObject*> GameLogic::toAddList{};
float GameLogic::asteroidSpawnTime{};

void GameLogic::begin() {
    objects.push_back(new Player());
    asteroidSpawnTime = ASTEROID_SPAWN_TIME;
}

void GameLogic::update(sf::RenderWindow& window, float deltaTime) {
    
    window.clear(sf::Color::Black);

    GameLogic::toAddList.clear();
    GameLogic::toRemoveList.clear();

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
}
    
