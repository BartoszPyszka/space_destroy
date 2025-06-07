#pragma once

// Nag��wki niezb�dne do dzia�ania klasy Asteroid
#include "GameObject.h"  // Bazowa klasa dla obiekt�w gry
#include "Globals.h"     // Sta�e globalne i ustawienia
#include <SFML/Audio.hpp> // Efekty d�wi�kowe
#include <random>        // Generowanie losowych warto�ci

// Parametry asteroid
constexpr float ASTEROID_SPIN = 40.0f;       // Pr�dko�� obrotu (stopnie/sekund�)
constexpr float ASTEROID_SPEED = 200.0f;     // Bazowa pr�dko�� ruchu (piksele/sekund�)
constexpr float ASTEROID_W = 20.0f;          // Podstawowa szeroko�� hitboxu
constexpr float ASTEROID_H = 20.0f;          // Podstawowa wysoko�� hitboxu
constexpr float ASTEROID_SPAWN_TIME = 2.0f;  // Cz�stotliwo�� pojawiania si� asteroid (sekundy)
constexpr float ASTEROID_HIT_TIME = 0.2f;    // Czas klatek nie�miertelno�ci gracza
constexpr float ASTEROID_DELAY = 0.2f;       // Op�nienie przed ponownym zadawaniem obra�e�

// Klasa reprezentuj�ca asteroid� w grze
// Dziedziczy po GameObject, wykorzystuj�c podstawowe mechaniki pozycji i kolizji
class Asteroid : public GameObject {
public:
    // Konstruktor z domy�lnymi losowymi warto�ciami:
    // direction - kierunek ruchu (domy�lnie losowy)
    // position - pozycja startowa (domy�lnie losowa na kraw�dzi ekranu)
    Asteroid(sf::Vector2f direction = getRandomDirection(),
        sf::Vector2f position = getRandomPosition());

    // G��wna metoda aktualizuj�ca logik� asteroidy
    void update(float deltaTime) override;

    // Generuje losowy wektor kierunku ruchu (znormalizowany)
    static sf::Vector2f getRandomDirection();

    // Generuje losow� pozycj� startow� na kraw�dziach ekranu
    static sf::Vector2f getRandomPosition();

    // Zwraca referencj� do kszta�tu asteroidy (dla detekcji kolizji)
    const sf::VertexArray& getVertexArray() const;

    // Renderuje asteroid� na ekranie
    void render(sf::RenderWindow& window) override;

    // Zwraca czas �ycia od ostatniego uderzenia
    float getLife();

    // Aktualizuje stan asteroidy po uderzeniu
    bool updateAsteroid(float deltaTime);

    // Sprawdza czy asteroida jest "szcz�liwa" (dodatkowe punkty)
    bool isLucky();

    // Sprawdza czy asteroida jest "pechowa" (karna)
    bool isUnlucky();
    // Funkcja do za�adowania tekstur
    static bool loadTextures();

    // Flagi stanu asteroidy:
    bool can_damage;  // Czy mo�e zadawa� obra�enia
    bool alive;       // Czy asteroida jest aktywna
    bool lucky;       // Czy to specjalna "szcz�liwa" asteroida
    bool unlucky;     // Czy to specjalna "pechowa" asteroida

private:
    sf::VertexArray shape;  // Kszta�t asteroidy (dla renderowania i kolizji)
    float life;             // Czas od ostatniego uderzenia
    float timer;            // Licznik czasu og�lnego przeznaczenia
    sf::Vector2f direction; // Kierunek ruchu (znormalizowany wektor)
    sf::Sprite sprite;    // Sprite nak�adany na asteroid�
    static sf::Texture textures[3]; // Tekstury wsp�dzielone przez wszystkie asteroidy
};