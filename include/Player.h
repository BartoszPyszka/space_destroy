#pragma once

// Nag��wki zwi�zane z obs�ug� obiekt�w gry i fizyki
#include "GameObject.h"
#include "Globals.h"
#include "Bullet.h"
#include "GameLogic.h"
#include "Asteroid.h"
#include "Physics.h"
#include <memory>

// Podstawowe parametry gracza
// (warto�ci dobrane eksperymentalnie dla odpowiedniego balansu rozgrywki)
constexpr float PLAYER_W = 4.0f;             // Szeroko�� hitboxu gracza w jednostkach �wiata gry
constexpr float PLAYER_H = 4.0f;             // Wysoko�� hitboxu gracza w jednostkach �wiata gry
constexpr float TURN_SPEED = 200.0f;         // Wra�liwo�� sterowania - im wy�sza warto��, tym szybsze obroty
constexpr float PLAYER_SPEED = 200.0f;       // Bazowa pr�dko�� poruszania si� statku (przy pe�nym przy�pieszeniu)
constexpr float SHOOT_DELAY = 0.5f;          // Czas wymagany mi�dzy kolejnymi strza�ami (limit szybkostrzelno�ci)

// Klasa gracza - statku kosmicznego sterowanego przez gracza
// Dziedziczy po GameObject, wykorzystuj�c podstawowe mechaniki poruszania i kolizji
class Player : public GameObject {
public:
    // Konstruktor inicjuj�cy podstawowe warto�ci gracza
    Player(sf::Texture& texture);
    sf::Sprite Playersprite;
    sf::Vector2i PlayerframeSize;
    int PlayercurrentFrame;
    int PlayertotalFrames = 4; // Ustaw odpowiedni� liczb�
    float PlayerframeTime;     // Ile czasu mi�dzy klatkami
    float PlayerframeTimer;    // Licznik czasu

    // G��wna metoda aktualizuj�ca logik� gracza co klatk�:
    // - obs�uga wej�cia
    // - ruch i obroty
    // - strzelanie
    // - aktualizacja timer�w
    void update(float deltaTime) override;

    // Metoda odpowiedzialna za wizualn� reprezentacj� gracza:
    // - przygotowanie kszta�tu statku
    // - uwzgl�dnienie aktualnej rotacji
    // - renderowanie do okna gry
    void render(sf::RenderWindow& window) override;

private:
    // Reprezentacja graficzna statku jako zestaw po��czonych wierzcho�k�w
    sf::VertexArray shape;

    // Licznik kontroluj�cy op�nienie mi�dzy strza�ami
    float shootTimer;
};