#pragma once
#include <SFML/Graphics.hpp>

// Klasa bazowa dla wszystkich obiekt�w gry 
// (np. gracza, pocisk�w, asteroid). Udost�pnia wsp�lne 
// w�a�ciwo�ci, takie jak pozycja i k�t obrotu,
// oraz metody wirtualne do aktualizacji i renderowania
class GameObject {
public:
    // Konstruktor inicjalizuj�cy pozycj� i k�t obrotu obiektu
    GameObject(sf::Vector2f pos, float ang);

    // Wirtualny destruktor � umo�liwia poprawne 
    // niszczenie obiekt�w pochodnych
    virtual ~GameObject() {}

    // Metoda wirtualna � ka�da klasa dziedzicz�ca 
    // musi zaimplementowa� logik� aktualizacji
    virtual void update(float deltaTime) = 0;

    // Metoda wirtualna � ka�da klasa dziedzicz�ca 
    // musi zaimplementowa� logik� renderowania
    virtual void render(sf::RenderWindow& window) = 0;

    sf::Vector2f position;   // Pozycja obiektu w przestrzeni gry
    float angle;             // K�t obrotu obiektu (w stopniach)
};



