#pragma once
#include <SFML/Graphics.hpp>

// Klasa bazowa dla wszystkich obiektów gry 
// (np. gracza, pocisków, asteroid). Udostêpnia wspólne 
// w³aœciwoœci, takie jak pozycja i k¹t obrotu,
// oraz metody wirtualne do aktualizacji i renderowania
class GameObject {
public:
    // Konstruktor inicjalizuj¹cy pozycjê i k¹t obrotu obiektu
    GameObject(sf::Vector2f pos, float ang);

    // Wirtualny destruktor – umo¿liwia poprawne 
    // niszczenie obiektów pochodnych
    virtual ~GameObject() {}

    // Metoda wirtualna – ka¿da klasa dziedzicz¹ca 
    // musi zaimplementowaæ logikê aktualizacji
    virtual void update(float deltaTime) = 0;

    // Metoda wirtualna – ka¿da klasa dziedzicz¹ca 
    // musi zaimplementowaæ logikê renderowania
    virtual void render(sf::RenderWindow& window) = 0;

    sf::Vector2f position;   // Pozycja obiektu w przestrzeni gry
    float angle;             // K¹t obrotu obiektu (w stopniach)
};



