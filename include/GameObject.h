#pragma once

// Biblioteki zewnętrzne (SFML)
#include <SFML/Graphics.hpp>

// Klasa bazowa dla wszystkich obiektów gry 
class GameObject {
public:
    // Konstruktor obiektów 
    GameObject(sf::Vector2f pos, float ang);

    // Wirtualny destruktor – umożliwia poprawne 
    // niszczenie obiektów pochodnych
    virtual ~GameObject() {}

    // Metoda wirtualna – każda klasa dziedzicząca 
    // musi zaimplementować logikę aktualizacji
    virtual void update(float deltaTime) = 0;

    // Metoda wirtualna – każda klasa dziedzicząca 
    // musi zaimplementować logikę renderowania
    virtual void render(sf::RenderWindow& window) = 0;

    sf::Vector2f position;   
    float angle;             
};



