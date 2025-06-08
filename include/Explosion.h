#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "GameLogic.h"
#include <vector>

// Klasa wybuchu, dziedziczy po GameObject
class Explosion : public GameObject {
public:
    // Typ wybuchu (do zmiany kolorów)
    enum class ExplosionColorType {
        Normal,
        Lucky,
        Unlucky
    };

    // Konstruktor, przyjmuje pozycjê wybuchu i typ koloru
    explicit Explosion(sf::Vector2f pos, ExplosionColorType type = ExplosionColorType::Normal);

    // Aktualizuje stan wybuchu (ko³a i fragmenty)
    void update(float deltaTime) override;

    // Rysuje wybuch na ekranie
    void render(sf::RenderWindow& window) override;

private:
    // Struktura opisuj¹ca pojedyncze ko³o efektu wybuchu
    struct CircleEffect {
        sf::CircleShape shape;
        float maxRadius;
        float currentRadius;
        float growthRate;
    };

    // Struktura opisuj¹ca fragment meteorytu
    struct Fragment {
        sf::ConvexShape shape;
        sf::Vector2f velocity;
    };

    float lifetime;                 // Czas ¿ycia wybuchu
    static constexpr float MAX_LIFETIME = 0.7f;  // Maksymalny czas trwania efeku

    //Fragmenty animacji
    CircleEffect yellowCircle;
    CircleEffect redCircle;
    CircleEffect grayCircle;

    std::vector<Fragment> fragments;

    ExplosionColorType colorType;

    // Pomocnicze funkcje do aktualizacji i tworzenia efektów
    void updateCircle(CircleEffect& circle, float deltaTime);
    void updateFragments(float deltaTime);
    void createFragments(int count);
};
