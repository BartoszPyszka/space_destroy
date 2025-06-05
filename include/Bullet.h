#pragma once

// Nag��wki niezb�dne do dzia�ania klasy Bullet
#include "GameObject.h"  // Bazowa klasa dla obiekt�w gry
#include "GameLogic.h"   // Logika gry i zarz�dzanie obiektami
#include "Physics.h"     // Detekcja kolizji
#include "Player.h"      // Klasa gracza (potrzebna do relacji strzelania)
#include "Asteroid.h"    // Cel pocisk�w
#include <memory>        // Wska�niki inteligentne

// Parametry pocisk�w
constexpr float BULLET_SPEED = 700.0f;       // Sta�a pr�dko�� pocisku w pikselach/sekund�
constexpr float BULLET_LIFE = 3.0f;          // Maksymalny czas istnienia pocisku w sekundach

// Klasa reprezentuj�ca pocisk wystrzeliwany przez gracza
// Dziedziczy po GameObject, wykorzystuj�c podstawowe mechaniki pozycji i kolizji
class Bullet : public GameObject {
public:
    // Konstruktor inicjuj�cy pocisk:
    // startPos - pozycja startowa (zazwyczaj pozycja statku gracza)
    // dir - znormalizowany wektor kierunku ruchu
    Bullet(sf::Vector2f startPos, sf::Vector2f dir);

    // Aktualizuje stan pocisku co klatk�:
    // - ruch zgodnie z kierunkiem
    // - sprawdzanie czasu �ycia
    // - detekcja kolizji z asteroidami
    void update(float deltaTime) override;

    // Renderuje pocisk na ekranie
    void render(sf::RenderWindow& window) override;

private:
    sf::CircleShape shape;      // Okr�g�y kszta�t pocisku (prosta reprezentacja wizualna)
    sf::Vector2f direction;     // Znormalizowany wektor kierunku ruchu
    float lifetime;             // Pozosta�y czas �ycia pocisku w sekundach
};