#pragma once

// Nag³ówki zwi¹zane z obs³ug¹ obiektów gry i fizyki
#include "GameObject.h"
#include "Globals.h"
#include "Bullet.h"
#include "GameLogic.h"
#include "Asteroid.h"
#include "Physics.h"
#include <memory>

// Podstawowe parametry gracza
// (wartoœci dobrane eksperymentalnie dla odpowiedniego balansu rozgrywki)
constexpr float PLAYER_W = 4.0f;             // Szerokoœæ hitboxu gracza w jednostkach œwiata gry
constexpr float PLAYER_H = 4.0f;             // Wysokoœæ hitboxu gracza w jednostkach œwiata gry
constexpr float TURN_SPEED = 200.0f;         // Wra¿liwoœæ sterowania - im wy¿sza wartoœæ, tym szybsze obroty
constexpr float PLAYER_SPEED = 200.0f;       // Bazowa prêdkoœæ poruszania siê statku (przy pe³nym przyœpieszeniu)
constexpr float SHOOT_DELAY = 0.5f;          // Czas wymagany miêdzy kolejnymi strza³ami (limit szybkostrzelnoœci)

// Klasa gracza - statku kosmicznego sterowanego przez gracza
// Dziedziczy po GameObject, wykorzystuj¹c podstawowe mechaniki poruszania i kolizji
class Player : public GameObject {
public:
    // Konstruktor inicjuj¹cy podstawowe wartoœci gracza
    Player(sf::Texture& texture);
    sf::Sprite Playersprite;
    sf::Vector2i PlayerframeSize;
    int PlayercurrentFrame;
    int PlayertotalFrames = 4; // Ustaw odpowiedni¹ liczbê
    float PlayerframeTime;     // Ile czasu miêdzy klatkami
    float PlayerframeTimer;    // Licznik czasu

    // G³ówna metoda aktualizuj¹ca logikê gracza co klatkê:
    // - obs³uga wejœcia
    // - ruch i obroty
    // - strzelanie
    // - aktualizacja timerów
    void update(float deltaTime) override;

    // Metoda odpowiedzialna za wizualn¹ reprezentacjê gracza:
    // - przygotowanie kszta³tu statku
    // - uwzglêdnienie aktualnej rotacji
    // - renderowanie do okna gry
    void render(sf::RenderWindow& window) override;

private:
    // Reprezentacja graficzna statku jako zestaw po³¹czonych wierzcho³ków
    sf::VertexArray shape;

    // Licznik kontroluj¹cy opóŸnienie miêdzy strza³ami
    float shootTimer;
};