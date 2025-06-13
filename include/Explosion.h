#pragma once

// Standardowe biblioteki C++ 
#include <vector>

// Biblioteki zewnętrzne (SFML)
#include <SFML/Graphics.hpp>

// Własne nagłówki
#include "GameObject.h"
#include "GameLogic.h"

// Klasa wybuchu 
class Explosion : public GameObject {
public:
    // Typ wybuchu (do zmiany kolorów)
    enum class ExplosionColorType {
        Normal,
        Lucky,
        Unlucky
    };

    // Konstruktor klasy wybuchu
    explicit Explosion(sf::Vector2f pos, ExplosionColorType type = ExplosionColorType::Normal);

    // Główna metoda aktualizująca logikę wybuchu
    void update(float deltaTime) override;

     // Renderuje wybuch na ekranie
    void render(sf::RenderWindow& window) override;

private:
    // Struktura opisująca pojedyncze koło efektu wybuchu
    struct CircleEffect {
        sf::CircleShape shape;
        float maxRadius;
        float currentRadius;
        float growthRate;
    };

    // Struktura opisująca fragment asteroidy
    struct Fragment {
        sf::ConvexShape shape;
        sf::Vector2f velocity;
    };

    float lifetime;                
    static constexpr float MAX_LIFETIME = 0.7f;  

    // Fragmenty animacji
    CircleEffect yellowCircle;
    CircleEffect redCircle;
    CircleEffect grayCircle;

    // Fragmenty eksplozji (odłamki)
    std::vector<Fragment> fragments;

    // Kolor efektu wybuchu
    ExplosionColorType colorType;

    // Pomocnicze funkcje do aktualizacji i tworzenia efektów
    void updateCircle(CircleEffect& circle, float deltaTime);
    void updateFragments(float deltaTime);
    void createFragments(int count);
};
