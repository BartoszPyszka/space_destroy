#include "Asteroid.h"
sf::Texture Asteroid::textures[3];
// Konstruktor asteroidy - inicjalizuje w³aœciwoœci i wygl¹d
Asteroid::Asteroid(sf::Vector2f direction, sf::Vector2f position)
    : GameObject(position, 0.0f),  // Inicjalizacja pozycji i k¹ta obrotu
    direction(direction),        // Ustawienie kierunku ruchu
    shape(sf::TrianglesFan, 6),  // Przygotowanie kszta³tu z 6 wierzcho³ków
    life(0.0f)                  // Inicjalizacja czasu ¿ycia
{
    // Domyœlne ustawienia stanu asteroidy
    can_damage = false;
    alive = true;
    timer = 0.0f;

    // Definicja kszta³tu asteroidy
    shape[0].position = { 0, 30 };
    shape[1].position = { 30, 15 };
    shape[2].position = { 30, -15 };
    shape[3].position = { 0, -30 };
    shape[4].position = { -30, -15 };
    shape[5].position = { -30, 15 };

    for (size_t i = 0; i < shape.getVertexCount(); i++) {
        shape[i].color = sf::Color::Transparent;
    }

    // Sprawdzenie czy asteroida jest "szczêœliwa" lub "pechowa"
    lucky = isLucky();
    if (!lucky) {
        unlucky = isUnlucky();
    }
    else {
        unlucky = false;
    }

    // ===== NAK£ADANIE SPRITE'A GRAFICZNEGO =====
    int textureIndex = 0; // 0 - zwyk³a
    if (lucky) textureIndex = 1;       // 1 - szczêœliwa
    else if (unlucky) textureIndex = 2; // 2 - pechowa

    sprite.setTexture(textures[textureIndex]);

    // Skalowanie do ok. 60x60 (bo grafika ma 512x512)
    float targetSize = 60.0f;
    float scale = targetSize / 512.0f;
    sprite.setScale(scale, scale);

    // Ustaw œrodek na œrodek tekstury
    sprite.setOrigin(256.0f, 256.0f);
}

bool Asteroid::loadTextures()
{
    return textures[0].loadFromFile("Assets\\graphics\\asteroid1.png") &&
        textures[1].loadFromFile("Assets\\graphics\\asteroid2.png") &&
        textures[2].loadFromFile("Assets\\graphics\\asteroid3.png");
}

// Sprawdza czy asteroida jest "szczêœliwa" (dodatkowe punkty)
bool Asteroid::isLucky() {
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10); // 1 na 10 szans

    bool luckyRoll = (dist(gen) == 1); // 10% prawdopodobieñstwo

    return luckyRoll;
}

// Sprawdza czy asteroida jest "pechowa" (karna)
bool Asteroid::isUnlucky() {
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100); // 1 na 100 szans

    bool unluckyRoll = (dist(gen) == 1) && !lucky; // 1% i nie mo¿e byæ szczêœliwa

    return unluckyRoll;
}

// Aktualizuje stan asteroidy co klatkê
void Asteroid::update(float deltaTime)
{
    life += deltaTime;
    position += ASTEROID_SPEED * direction * deltaTime;
    angle += ASTEROID_SPEED * deltaTime;

    // Uzyskaj rozmiar ekranu z globalnego Ÿród³a (przyk³ad)
    float screenWidth = static_cast<float>(SCREEN_WIDTH);
    float screenHeight = static_cast<float>(SCREEN_HEIGHT);

    float halfWidth = ASTEROID_W / 2.0f;
    float halfHeight = ASTEROID_H / 2.0f;

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

// Generuje losowy kierunek ruchu (znormalizowany wektor)
sf::Vector2f Asteroid::getRandomDirection()
{
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI); // Pe³ny zakres k¹tów

    float angle = dist(gen); // Losowy k¹t
    return { cos(angle), sin(angle) }; // Konwersja na wektor kierunku
}

// Generuje losow¹ pozycjê startow¹ na ekranie
sf::Vector2f Asteroid::getRandomPosition()
{
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());

    // Losowa pozycja X (z uwzglêdnieniem rozmiaru asteroidy)
    std::uniform_real_distribution<float> xAxis(ASTEROID_W / 2.0f, SCREEN_WIDTH - ASTEROID_W / 2.0f);

    // Losowa pozycja Y (z uwzglêdnieniem rozmiaru asteroidy)
    std::uniform_real_distribution<float> yAxis(ASTEROID_H / 2.0f, SCREEN_HEIGHT - ASTEROID_H / 2.0f);

    return { xAxis(gen), yAxis(gen) };
}

// Zwraca kszta³t asteroidy (dla detekcji kolizji)
const sf::VertexArray& Asteroid::getVertexArray() const
{
    return shape;
}

// Renderuje asteroidê na ekranie
void Asteroid::render(sf::RenderWindow& window)
{
    sf::Transform transform;
    transform.translate(position).rotate(angle);

    // Rysuj najpierw sprite, potem shape (np. jako kolizjê)
    sf::RenderStates states;
    states.transform = transform;

    window.draw(sprite, states);       // Tekstura
    window.draw(shape, transform);     // Kszta³t (kolizja lub efekt)
}

// Zwraca czas ¿ycia asteroidy od ostatniego uderzenia
float Asteroid::getLife() {
    return life;
}

// Aktualizuje stan asteroidy po uderzeniu
bool Asteroid::updateAsteroid(float deltaTime) {
    if (timer <= ASTEROID_DELAY) {
        timer += deltaTime; // Odliczanie czasu
    }
    else {
        timer = 0.0f; // Reset timera
        can_damage = true; // Mo¿e ponownie zadawaæ obra¿enia
    }

    return can_damage;
}