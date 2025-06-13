#pragma once

// Standardowe biblioteki C++ 
#include <memory> 

// Własne nagłówki
#include "GameObject.h"  
#include "GameLogic.h"   
#include "Physics.h"     
#include "Player.h"      
#include "Asteroid.h"    
#include "Explosion.h"
       
// Parametry pocisków
constexpr float BULLET_SPEED = 700.0f;       
constexpr float BULLET_LIFE = 3.0f;          

// Klasa pocisku wystrzeliwanego przez gracza
class Bullet : public GameObject {
public:
    // Konstruktor pocisku
    Bullet(sf::Vector2f startPos, sf::Vector2f dir);

     // Główna metoda aktualizująca logikę pocisku
    void update(float deltaTime) override;

    // Renderuje pocisk na ekranie
    void render(sf::RenderWindow& window) override;

private:
    sf::CircleShape shape;     
    sf::Vector2f direction;     
    float lifetime;             
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    bool exploding = false;
};
