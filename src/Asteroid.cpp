// Standardowe biblioteki C++ 
#include <vector>                
#include <list>                  
#include <memory>                
#include <fstream>               
#include <string>                
#include <cstdio>               
#include <functional>            
#include <algorithm>  
#include <cmath>

// Własne nagłówki
#include "Asteroid.h"

sf::Texture Asteroid::textures[3];

// Konstruktor asteroidy 
Asteroid::Asteroid(sf::Vector2f direction, sf::Vector2f position)
    : GameObject(position, 0.0f),  
    direction(direction),        
    shape(sf::TrianglesFan, 6),  
    life(0.0f)                  
{
    // Domyślne ustawienia stanu asteroidy
    can_damage = false;
    alive = true;
    timer = 0.0f;

    // Definicja kształtu asteroidy
    shape[0].position = { 0, 30 };
    shape[1].position = { 30, 15 };
    shape[2].position = { 30, -15 };
    shape[3].position = { 0, -30 };
    shape[4].position = { -30, -15 };
    shape[5].position = { -30, 15 };

    // Wypełnienie przezroczystym kolorem
    for (size_t i = 0; i < shape.getVertexCount(); i++) {
        shape[i].color = sf::Color::Transparent;
    }

    // Sprawdzenie czy asteroida jest "szczęśliwa" lub "pechowa"
    lucky = isLucky();
    if (!lucky) {
        unlucky = isUnlucky();
    }
    else {
        unlucky = false;
    }

    // Nakładanie sprite'a graficznego
    int textureIndex = 0;               // 0 - zwykła
    if (lucky) textureIndex = 1;        // 1 - szczęśliwa
    else if (unlucky) textureIndex = 2; // 2 - pechowa

    sprite.setTexture(textures[textureIndex]);

    // Skalowanie do ok. 60x60 (bo grafika ma 512x512)
    float targetSize = 60.0f;
    float scale = targetSize / 512.0f;
    sprite.setScale(scale, scale);

    // Ustaw środek na środek tekstury
    sprite.setOrigin(256.0f, 256.0f);
}

// Załadowanie tekstur
bool Asteroid::loadTextures()
{
    return textures[0].loadFromFile("Assets\\graphics\\asteroid1.png") &&
        textures[1].loadFromFile("Assets\\graphics\\asteroid2.png") &&
        textures[2].loadFromFile("Assets\\graphics\\asteroid3.png");
}

// Sprawdza czy asteroida jest "szczęśliwa" (dodatkowe punkty)
bool Asteroid::isLucky() {
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10); // 1 na 10 szans

    bool luckyRoll = (dist(gen) == 1); 

    return luckyRoll;
}

// Sprawdza czy asteroida jest "pechowa" 
bool Asteroid::isUnlucky() {
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100); // 1 na 100 szans

    bool unluckyRoll = (dist(gen) == 1) && !lucky; 

    return unluckyRoll;
}

// Aktualizuje stan asteroidy 
void Asteroid::update(float deltaTime)
{
    life += deltaTime;
    position += ASTEROID_SPEED * direction * deltaTime;
    angle += ASTEROID_SPEED * deltaTime;

    // Uzyskaj rozmiar ekranu 
    float screenWidth = static_cast<float>(SCREEN_WIDTH);
    float screenHeight = static_cast<float>(SCREEN_HEIGHT);

    float halfWidth = ASTEROID_W / 2.0f;
    float halfHeight = ASTEROID_H / 2.0f;

    // Odbijanie się asteroid
    if (position.x < halfWidth) {
        position.x = halfWidth;
        direction.x = std::abs(direction.x);
    }
    else if (position.x > screenWidth - halfWidth) {
        position.x = screenWidth - halfWidth;
        direction.x = -std::abs(direction.x);
    }

    if (position.y < halfHeight) {
        position.y = halfHeight;
        direction.y = std::abs(direction.y);
    }
    else if (position.y > screenHeight - halfHeight) {
        position.y = screenHeight - halfHeight;
        direction.y = -std::abs(direction.y);
    }
}

// Generuje losowy kierunek ruchu 
sf::Vector2f Asteroid::getRandomDirection()
{
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI); // Pełny zakres kątów

    float angle = dist(gen); 
    return { cos(angle), sin(angle) }; // Konwersja na wektor kierunku
}

// Generuje losową pozycję startową na ekranie
sf::Vector2f Asteroid::getRandomPosition()
{
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());

    // Losowa pozycja X (z uwzględnieniem rozmiaru asteroidy)
    std::uniform_real_distribution<float> xAxis(ASTEROID_W / 2.0f, SCREEN_WIDTH - ASTEROID_W / 2.0f);

    // Losowa pozycja Y (z uwzględnieniem rozmiaru asteroidy)
    std::uniform_real_distribution<float> yAxis(ASTEROID_H / 2.0f, SCREEN_HEIGHT - ASTEROID_H / 2.0f);

    return { xAxis(gen), yAxis(gen) };
}

// Zwraca kształt asteroidy (dla detekcji kolizji)
const sf::VertexArray& Asteroid::getVertexArray() const
{
    return shape;
}

// Renderuje asteroidę na ekranie
void Asteroid::render(sf::RenderWindow& window)
{
    sf::Transform transform;
    transform.translate(position).rotate(angle);

    // Rysuj najpierw sprite, potem shape 
    sf::RenderStates states;
    states.transform = transform;

    window.draw(sprite, states);       
    window.draw(shape, transform);     
}

// Zwraca czas życia asteroidy od ostatniego uderzenia
float Asteroid::getLife() {
    return life;
}

// Aktualizuje stan asteroidy po uderzeniu
bool Asteroid::updateAsteroid(float deltaTime) {
    if (timer <= ASTEROID_DELAY) {
        timer += deltaTime; // Odliczanie czasu
    }
    else {
        timer = 0.0f; 
        can_damage = true; 
    }

    return can_damage;
}
