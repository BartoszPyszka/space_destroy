#include "Explosion.h"
#include <cstdlib>
#include <vector>                
#include <list>                  
#include <memory>                
#include <fstream>               
#include <string>                
#include <cstdio>               
#include <functional>            
#include <algorithm>  
#include <cmath>

// Funkcja pomocnicza do losowania float�w z zakresu [min, max]
static float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

// Konstruktor wybuchu
Explosion::Explosion(sf::Vector2f pos, ExplosionColorType type)
    : GameObject(pos, 0.0f),
    lifetime(MAX_LIFETIME),
    colorType(type)
{
    sf::Color yellow = sf::Color::Yellow;
    sf::Color red = sf::Color::Red;
    sf::Color gray = sf::Color(128, 128, 128);

    // Zmieniamy kolory zale�nie od typu wybuchu
    switch (colorType) {
    case ExplosionColorType::Lucky:
        yellow = sf::Color(100, 200, 255); // niebieski
        red = sf::Color(150, 200, 255);
        gray = sf::Color(180, 220, 255);
        break;
    case ExplosionColorType::Unlucky:
        yellow = sf::Color(255, 255, 100); // ��ty intensywny
        red = sf::Color(255, 180, 50);
        gray = sf::Color(200, 200, 100);
        break;
    default:
        break;
    }

    // Ustawiamy 1 kolos
    yellowCircle.shape.setFillColor(yellow);
    yellowCircle.maxRadius = 40.f;      // maksymalny rozmiar ko�a
    yellowCircle.currentRadius = 10.f;  // pocz�tkowy promie�
    yellowCircle.growthRate = 60.f;     // jak szybko ko�o ro�nie
    yellowCircle.shape.setOrigin(yellowCircle.currentRadius, yellowCircle.currentRadius); // �rodek ko�a
    yellowCircle.shape.setRadius(yellowCircle.currentRadius);
    yellowCircle.shape.setPosition(position);

    // Ustawiamy 2 kolo
    redCircle.shape.setFillColor(red);
    redCircle.maxRadius = 30.f;
    redCircle.currentRadius = 8.f;
    redCircle.growthRate = 40.f;
    redCircle.shape.setOrigin(redCircle.currentRadius, redCircle.currentRadius);
    redCircle.shape.setRadius(redCircle.currentRadius);
    redCircle.shape.setPosition(position);

    // Ustawiamy 3 kolos
    grayCircle.shape.setFillColor(gray);
    grayCircle.maxRadius = 20.f;
    grayCircle.currentRadius = 5.f;
    grayCircle.growthRate = 20.f;
    grayCircle.shape.setOrigin(grayCircle.currentRadius, grayCircle.currentRadius);
    grayCircle.shape.setRadius(grayCircle.currentRadius);
    grayCircle.shape.setPosition(position);

    createFragments(80);  // Deklaracja ile fragmentow chcemy mozna zmiejszyc jak ktos ma slaby pc XD
}

// Funkcja tworz�ca fragmenty meteoryt�ww
void Explosion::createFragments(int count) {
    fragments.clear();

    for (int i = 0; i < count; ++i) {
        Fragment frag;

        // Tworzymy tr�jk�t jako fragment
        frag.shape.setPointCount(3);

        // Losujemy pozycje punkt�w tr�jk�ta, �eby nie by� idealny
        frag.shape.setPoint(0, sf::Vector2f(0.f, 0.f));
        frag.shape.setPoint(1, sf::Vector2f(randomFloat(5.f, 12.f), randomFloat(-3.f, 3.f)));
        frag.shape.setPoint(2, sf::Vector2f(randomFloat(3.f, 7.f), randomFloat(5.f, 10.f)));

        frag.shape.setFillColor(sf::Color(100, 100, 100)); // szary kolor fragmentu

        // Ustawiamy fragment na �rodku wybuchu
        frag.shape.setPosition(position);

        // Ustawiamy punkt obrotu na �rodek
        frag.shape.setOrigin(3.f, 3.f);

        // Losujemy kierunek i pr�dko�� ruchu fragmentu
        float angle = randomFloat(0.f, 2.f * 3.14159f);
        float speed = randomFloat(50.f, 120.f);
        frag.velocity = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);

        fragments.push_back(frag);
    }
}

// Funkcja aktualizuj�ca pojedyncze ko�o (rosn�ce i znikaj�ce)
void Explosion::updateCircle(CircleEffect& circle, float deltaTime)
{
    circle.currentRadius += circle.growthRate * deltaTime;
    if (circle.currentRadius > circle.maxRadius) circle.currentRadius = circle.maxRadius;

    circle.shape.setRadius(circle.currentRadius);
    circle.shape.setOrigin(circle.currentRadius, circle.currentRadius);

    float alpha = 255.f * (lifetime / MAX_LIFETIME);
    sf::Color color = circle.shape.getFillColor();
    color.a = static_cast<sf::Uint8>(alpha);
    circle.shape.setFillColor(color);

    circle.shape.setPosition(position);
}

// Aktualizacja fragment�w-zanimowanie ich
void Explosion::updateFragments(float deltaTime)
{
    float alpha = 255.f * (lifetime / MAX_LIFETIME);

    for (auto& frag : fragments) {
        frag.shape.move(frag.velocity * deltaTime);
        frag.shape.rotate(90.f * deltaTime);
        sf::Color color = frag.shape.getFillColor();
        color.a = static_cast<sf::Uint8>(alpha);
        frag.shape.setFillColor(color);
    }
}

// G��wna funkcja update wybuchu, wywo�ywana co klatk�
void Explosion::update(float deltaTime)
{
    // Zmniejszamy czas �ycia wybuchu
    lifetime -= deltaTime;
    if (lifetime < 0.0f) lifetime = 0.0f;

    // Aktualizujemy ko�a i fragmenty
    updateCircle(yellowCircle, deltaTime);
    updateCircle(redCircle, deltaTime);
    updateCircle(grayCircle, deltaTime);
    updateFragments(deltaTime);

    // Je�li czas �ycia min��, oznaczamy wybuch do usuni�cia z gry
    if (lifetime <= 0.0f) {
        for (size_t i = 0; i < GameLogic::objects.size(); ++i) {
            if (GameLogic::objects[i].get() == this) {
                GameLogic::toRemoveIndices.push_back(i);
                break;
            }
        }
    }
}

// Rysowanie wybuchu na ekranie
void Explosion::render(sf::RenderWindow& window)
{
    // Rysujemy ko�a w kolejno�ci rosprzeszczenienia sie wybuchu
    window.draw(grayCircle.shape);
    window.draw(redCircle.shape);
    window.draw(yellowCircle.shape);

    // Rysujemy wszystkie fragmenty meteorytoww
    for (auto& frag : fragments) {
        window.draw(frag.shape);
    }
}
