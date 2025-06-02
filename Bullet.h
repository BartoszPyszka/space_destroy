#pragma once
#include "GameObject.h"
#include "GameLogic.h"

constexpr float BULLET_SPEED = 400.0f;       // Prêdkoœæ pocisku
constexpr float BULLET_LIFE = 3.0f;          // Czas ¿ycia pocisku

class Bullet : public GameObject {
public:
    Bullet(sf::Vector2f startPos, sf::Vector2f dir);
        
    void update(float deltaTime) override;

    void render(sf::RenderWindow& window) override;

private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    float lifetime;
};
