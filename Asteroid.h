#pragma once
#include "GameObject.h"
#include "Globals.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>

constexpr float ASTEROID_SPIN = 40.0f;       // Pr�dko�� obrotu asteroidy
constexpr float ASTEROID_SPEED = 200.0f;     // Pr�dko�� ruchu asteroidy
constexpr float ASTEROID_W = 20.0f;          // Szeroko�� asteroidy
constexpr float ASTEROID_H = 20.0f;          // Wysoko�� asteroidy
constexpr float ASTEROID_SPAWN_TIME = 2.0f;  // Interwa� generowania asteroid

class Asteroid : public GameObject {
public:
    Asteroid(sf::Vector2f direction = getRandomDirection(), sf::Vector2f position = getRandomPosition());

    void update(float deltaTime) override;

    static sf::Vector2f getRandomDirection();

    static sf::Vector2f getRandomPosition();

    void render(sf::RenderWindow& window) override;

private:
    sf::VertexArray shape;
    float life;
    sf::Vector2f direction;
    sf::SoundBuffer bounceBuffer;
    sf::Sound bounceSound;
};
