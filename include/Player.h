#pragma once

// Standardowe biblioteki C++ 
#include <memory>

// Własne nagłówki
#include "GameObject.h"
#include "Globals.h"
#include "Bullet.h"
#include "GameLogic.h"
#include "Asteroid.h"
#include "Physics.h"

// Parametry gracza
constexpr float PLAYER_W = 4.0f;             
constexpr float PLAYER_H = 4.0f;             
constexpr float TURN_SPEED = 300.0f;         
constexpr float PLAYER_SPEED = 200.0f;       
constexpr float SHOOT_DELAY = 0.5f;          

// Klasa reprezentująca gracza 
class Player : public GameObject {
public:
    // Konstruktor inicjujący podstawowe wartości gracza
    Player(sf::Texture& texture);

    // Wygląd i animacja
    sf::Texture boostTexture;
    sf::Texture* originalTexture;
    sf::Sprite Playersprite;
    sf::Vector2i PlayerframeSize;
    int PlayercurrentFrame;
    int PlayertotalFrames = 4; 
    float PlayerframeTime;     // Ile czasu między klatkami
    float PlayerframeTimer;    // Licznik czasu

    // Typy bonusów
    enum class BonusType { None, FastShoot, FastMove, Invincible }; 

    // Bonusy i ich efekty
    BonusType currentBonus = BonusType::None;
    float bonusTimer = 0.0f;  // Ile jeszcze trwa bonus
    float shootDelayBase = SHOOT_DELAY;     
    float playerSpeedBase = PLAYER_SPEED;
    bool invincible = false;

    // Główna metoda aktualizująca logikę gracza
    void update(float deltaTime) override;

    // Renderuje gracza na ekranie
    void render(sf::RenderWindow& window) override;

private:
    sf::VertexArray shape;
    float shootTimer;
    sf::SoundBuffer bonusBuffer;
    sf::Sound bonusSound;

};
