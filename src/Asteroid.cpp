#include "Asteroid.h"

// Konstruktor asteroidy - inicjalizuje w³aœciwoœci i wygl¹d
Asteroid::Asteroid(sf::Vector2f direction, sf::Vector2f position)
    : GameObject(position, 0.0f),  // Inicjalizacja pozycji i k¹ta obrotu
    direction(direction),        // Ustawienie kierunku ruchu
    shape(sf::TrianglesFan, 6),  // Przygotowanie kszta³tu z 6 wierzcho³ków
    life(0.0f)                  // Inicjalizacja czasu ¿ycia
{
    // Domyœlne ustawienia stanu asteroidy
    can_damage = false;  // Pocz¹tkowo nie mo¿e zadawaæ obra¿eñ
    alive = true;        // Asteroida zaczyna jako aktywna
    timer = 0.0f;       // Reset licznika czasu

    // Definicja kszta³tu asteroidy 
    shape[0].position = { 0, 30 };    
    shape[1].position = { 30, 15 };   
    shape[2].position = { 30, -15 };  
    shape[3].position = { 0, -30 };   
    shape[4].position = { -30, -15 }; 
    shape[5].position = { -30, 15 };  

    // Ustawienie koloru br¹zowego dla wszystkich wierzcho³ków
    for (size_t i = 0; i < shape.getVertexCount(); i++) {
        shape[i].color = sf::Color(112, 42, 42);
    }

    // Sprawdzenie czy asteroida jest "szczêœliwa" (10% szans)
    lucky = isLucky();

    // Jeœli nie jest szczêœliwa, sprawdŸ czy jest "pechowa" (1% szans)
    if (!lucky) {
        unlucky = isUnlucky();
    }
    else {
        unlucky = false; // Nie mo¿e byæ jednoczeœnie szczêœliwa i pechowa
    }
}

// Sprawdza czy asteroida jest "szczêœliwa" (dodatkowe punkty)
bool Asteroid::isLucky() {
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10); // 1 na 10 szans

    bool luckyRoll = (dist(gen) == 1); // 10% prawdopodobieñstwo

    if (luckyRoll) {
        // Zmiana koloru na ¿ó³ty dla szczêœliwej asteroidy
        for (size_t i = 0; i < shape.getVertexCount(); i++) {
            shape[i].color = sf::Color::Yellow;
        }
    }

    return luckyRoll;
}

// Sprawdza czy asteroida jest "pechowa" (karna)
bool Asteroid::isUnlucky() {
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100); // 1 na 100 szans

    bool unluckyRoll = (dist(gen) == 1) && !lucky; // 1% i nie mo¿e byæ szczêœliwa

    if (unluckyRoll) {
        // Zmiana koloru na niebieski dla pechowej asteroidy
        for (size_t i = 0; i < shape.getVertexCount(); i++) {
            shape[i].color = sf::Color::Blue;
        }
    }

    return unluckyRoll;
}

// Aktualizuje stan asteroidy co klatkê
void Asteroid::update(float deltaTime)
{
    life += deltaTime; // Aktualizacja czasu ¿ycia

    // Aktualizacja pozycji zgodnie z kierunkiem i prêdkoœci¹
    position += ASTEROID_SPEED * direction * deltaTime;

    // Obracanie asteroidy
    angle += ASTEROID_SPEED * deltaTime;

    // Obs³uga odbiæ od krawêdzi ekranu
    // Lewa krawêdŸ
    if (position.x < ASTEROID_W / 2.0f + 17.0f) {
        direction.x = abs(direction.x); // Odbicie w prawo
    }
    // Prawa krawêdŸ
    else if (position.x > SCREEN_WIDTH - ASTEROID_W / 2.0f - 10.0f) {
        direction.x = -abs(direction.x); // Odbicie w lewo
    }

    // Górna krawêdŸ
    if (position.y < ASTEROID_H / 2.0f + 17.0f) {
        direction.y = abs(direction.y); // Odbicie w dó³
    }
    // Dolna krawêdŸ
    else if (position.y > SCREEN_HEIGHT - ASTEROID_H / 2.0f - 10.0f) {
        direction.y = -abs(direction.y); // Odbicie w górê
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
    transform.translate(position).rotate(angle); // Pozycja + rotacja
    window.draw(shape, transform); // Rysowanie kszta³tu
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