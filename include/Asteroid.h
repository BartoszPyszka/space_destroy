#pragma once

// Nag³ówki niezbêdne do dzia³ania klasy Asteroid
#include "GameObject.h"  // Bazowa klasa dla obiektów gry
#include "Globals.h"     // Sta³e globalne i ustawienia
#include <SFML/Audio.hpp> // Efekty dŸwiêkowe
#include <random>        // Generowanie losowych wartoœci

// Parametry asteroid
constexpr float ASTEROID_SPIN = 40.0f;       // Prêdkoœæ obrotu (stopnie/sekundê)
constexpr float ASTEROID_SPEED = 200.0f;     // Bazowa prêdkoœæ ruchu (piksele/sekundê)
constexpr float ASTEROID_W = 20.0f;          // Podstawowa szerokoœæ hitboxu
constexpr float ASTEROID_H = 20.0f;          // Podstawowa wysokoœæ hitboxu
constexpr float ASTEROID_SPAWN_TIME = 2.0f;  // Czêstotliwoœæ pojawiania siê asteroid (sekundy)
constexpr float ASTEROID_HIT_TIME = 0.2f;    // Czas klatek nieœmiertelnoœci gracza
constexpr float ASTEROID_DELAY = 0.2f;       // OpóŸnienie przed ponownym zadawaniem obra¿eñ

// Klasa reprezentuj¹ca asteroidê w grze
// Dziedziczy po GameObject, wykorzystuj¹c podstawowe mechaniki pozycji i kolizji
class Asteroid : public GameObject {
public:
    // Konstruktor z domyœlnymi losowymi wartoœciami:
    // direction - kierunek ruchu (domyœlnie losowy)
    // position - pozycja startowa (domyœlnie losowa na krawêdzi ekranu)
    Asteroid(sf::Vector2f direction = getRandomDirection(),
        sf::Vector2f position = getRandomPosition());

    // G³ówna metoda aktualizuj¹ca logikê asteroidy
    void update(float deltaTime) override;

    // Generuje losowy wektor kierunku ruchu (znormalizowany)
    static sf::Vector2f getRandomDirection();

    // Generuje losow¹ pozycjê startow¹ na krawêdziach ekranu
    static sf::Vector2f getRandomPosition();

    // Zwraca referencjê do kszta³tu asteroidy (dla detekcji kolizji)
    const sf::VertexArray& getVertexArray() const;

    // Renderuje asteroidê na ekranie
    void render(sf::RenderWindow& window) override;

    // Zwraca czas ¿ycia od ostatniego uderzenia
    float getLife();

    // Aktualizuje stan asteroidy po uderzeniu
    bool updateAsteroid(float deltaTime);

    // Sprawdza czy asteroida jest "szczêœliwa" (dodatkowe punkty)
    bool isLucky();

    // Sprawdza czy asteroida jest "pechowa" (karna)
    bool isUnlucky();
    // Funkcja do za³adowania tekstur
    static bool loadTextures();

    // Flagi stanu asteroidy:
    bool can_damage;  // Czy mo¿e zadawaæ obra¿enia
    bool alive;       // Czy asteroida jest aktywna
    bool lucky;       // Czy to specjalna "szczêœliwa" asteroida
    bool unlucky;     // Czy to specjalna "pechowa" asteroida

private:
    sf::VertexArray shape;  // Kszta³t asteroidy (dla renderowania i kolizji)
    float life;             // Czas od ostatniego uderzenia
    float timer;            // Licznik czasu ogólnego przeznaczenia
    sf::Vector2f direction; // Kierunek ruchu (znormalizowany wektor)
    sf::Sprite sprite;    // Sprite nak³adany na asteroidê
    static sf::Texture textures[3]; // Tekstury wspó³dzielone przez wszystkie asteroidy
};