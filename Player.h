#pragma once
#include "GameObject.h"
#include "Globals.h"
#include "Bullet.h"
#include "GameLogic.h"
#include "Asteroid.h"
#include "Physics.h"

constexpr float PLAYER_W = 4.0f;             // Szerokoœæ gracza
constexpr float PLAYER_H = 4.0f;             // Wysokoœæ gracza
constexpr float TURN_SPEED = 200.0f;         // Prêdkoœæ obrotu gracza (stopnie/sek)
constexpr float PLAYER_SPEED = 1000.0f;      // Prêdkoœæ gracza (piksele/sek)
constexpr float SHOOT_DELAY = 0.2f;          // Odstêp miêdzy strza³ami

class Player : public GameObject {
public:
    Player();
        
    void update(float deltaTime) override;

    void render(sf::RenderWindow& window) override;

private:
    sf::VertexArray shape;
    float shootTimer;
};
