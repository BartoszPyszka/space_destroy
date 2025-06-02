#pragma once
#include <SFML/Graphics.hpp>


class GameObject {
public:
    GameObject(sf::Vector2f pos, float ang)
        : position(pos), angle(ang) {
    }

    virtual ~GameObject() {}

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    sf::Vector2f position;   // Pozycja obiektu
    float angle;             // K¹t obrotu obiektu
};

