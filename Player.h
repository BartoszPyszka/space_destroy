#pragma once
#include "GameObject.h"
#include "Globals.h"
#include "Bullet.h"
#include "GameLogic.h"
#include "Asteroid.h"
#include "Physics.h"

constexpr float PLAYER_W = 4.0f;             // Szeroko�� gracza
constexpr float PLAYER_H = 4.0f;             // Wysoko�� gracza
constexpr float TURN_SPEED = 200.0f;         // Pr�dko�� obrotu gracza (stopnie/sek)
constexpr float PLAYER_SPEED = 1000.0f;      // Pr�dko�� gracza (piksele/sek)
constexpr float SHOOT_DELAY = 0.2f;          // Odst�p mi�dzy strza�ami

class Player : public GameObject {
public:
    Player();
        
    void update(float deltaTime) override;

    void render(sf::RenderWindow& window) override;

private:
    sf::VertexArray shape;
    float shootTimer;
};
