#pragma once

// Standardowe biblioteki C++ 
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <list>
#include <memory>
#include <random>
#include <string>
#include <vector>

// Biblioteki zewnętrzne (SFML)
#include <SFML/Audio.hpp>

// Własne nagłówki
#include "GameObject.h"  // Bazowa klasa dla obiektów gry
#include "Globals.h"     // Stałe globalne i ustawienia

// Parametry asteroid
constexpr float ASTEROID_SPIN = 40.0f;       // Prędkość obrotu 
constexpr float ASTEROID_SPEED = 200.0f;     // Bazowa prędkość ruchu 
constexpr float ASTEROID_W = 20.0f;          // Podstawowa szerokość hitboxu
constexpr float ASTEROID_H = 20.0f;          // Podstawowa wysokość hitboxu
constexpr float ASTEROID_SPAWN_TIME = 2.0f;  // Częstotliwość pojawiania się asteroid (sekundy)
constexpr float ASTEROID_HIT_TIME = 0.2f;    // Czas klatek nieśmiertelności gracza
constexpr float ASTEROID_DELAY = 0.2f;       // Opóźnienie przed ponownym zadawaniem obrażeń

// Klasa reprezentująca asteroidę w grze
class Asteroid : public GameObject {
public:
    // Konstruktor asteroidy
    Asteroid(sf::Vector2f direction = getRandomDirection(),
        sf::Vector2f position = getRandomPosition());

    // Główna metoda aktualizująca logikę asteroidy
    void update(float deltaTime) override;

    // Generacja losowego kierunku ruchu i pozycji startowej
    static sf::Vector2f getRandomDirection();
    static sf::Vector2f getRandomPosition();

    // Zwraca kształt asteroidy (dla detekcji kolizji)
    const sf::VertexArray& getVertexArray() const;

    // Renderuje asteroidę na ekranie
    void render(sf::RenderWindow& window) override;

    // Zwraca czas życia od ostatniego uderzenia
    float getLife();

    // Aktualizuje stan asteroidy po uderzeniu
    bool updateAsteroid(float deltaTime);

    // Rodzaj asteroidy
    bool isLucky();
    bool isUnlucky();

    // Funkcja do załadowania tekstur
    static bool loadTextures();

    // Flagi stanu asteroidy:
    bool can_damage;  
    bool alive;       // Czy asteroida jest aktywna
    bool lucky;       
    bool unlucky;     

private:
    sf::VertexArray shape;  
    float life;             // Czas od ostatniego uderzenia
    float timer;            // Licznik czasu ogólnego przeznaczenia
    sf::Vector2f direction; 
    sf::Sprite sprite;    
    static sf::Texture textures[3]; 
};
