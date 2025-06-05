#pragma once

// Nag³ówki niezbêdne do dzia³ania klasy Bullet
#include "GameObject.h"  // Bazowa klasa dla obiektów gry
#include "GameLogic.h"   // Logika gry i zarz¹dzanie obiektami
#include "Physics.h"     // Detekcja kolizji
#include "Player.h"      // Klasa gracza (potrzebna do relacji strzelania)
#include "Asteroid.h"    // Cel pocisków
#include <memory>        // WskaŸniki inteligentne

// Parametry pocisków
constexpr float BULLET_SPEED = 700.0f;       // Sta³a prêdkoœæ pocisku w pikselach/sekundê
constexpr float BULLET_LIFE = 3.0f;          // Maksymalny czas istnienia pocisku w sekundach

// Klasa reprezentuj¹ca pocisk wystrzeliwany przez gracza
// Dziedziczy po GameObject, wykorzystuj¹c podstawowe mechaniki pozycji i kolizji
class Bullet : public GameObject {
public:
    // Konstruktor inicjuj¹cy pocisk:
    // startPos - pozycja startowa (zazwyczaj pozycja statku gracza)
    // dir - znormalizowany wektor kierunku ruchu
    Bullet(sf::Vector2f startPos, sf::Vector2f dir);

    // Aktualizuje stan pocisku co klatkê:
    // - ruch zgodnie z kierunkiem
    // - sprawdzanie czasu ¿ycia
    // - detekcja kolizji z asteroidami
    void update(float deltaTime) override;

    // Renderuje pocisk na ekranie
    void render(sf::RenderWindow& window) override;

private:
    sf::CircleShape shape;      // Okr¹g³y kszta³t pocisku (prosta reprezentacja wizualna)
    sf::Vector2f direction;     // Znormalizowany wektor kierunku ruchu
    float lifetime;             // Pozosta³y czas ¿ycia pocisku w sekundach
};