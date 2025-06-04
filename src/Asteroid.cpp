#include "Asteroid.h"

// Konstruktor asteroidy - inicjalizuje w�a�ciwo�ci i wygl�d
Asteroid::Asteroid(sf::Vector2f direction, sf::Vector2f position)
    : GameObject(position, 0.0f),  // Inicjalizacja pozycji i k�ta obrotu
    direction(direction),        // Ustawienie kierunku ruchu
    shape(sf::TrianglesFan, 6),  // Przygotowanie kszta�tu z 6 wierzcho�k�w
    life(0.0f)                  // Inicjalizacja czasu �ycia
{
    // Domy�lne ustawienia stanu asteroidy
    can_damage = false;  // Pocz�tkowo nie mo�e zadawa� obra�e�
    alive = true;        // Asteroida zaczyna jako aktywna
    timer = 0.0f;       // Reset licznika czasu

    // Definicja kszta�tu asteroidy 
    shape[0].position = { 0, 30 };    
    shape[1].position = { 30, 15 };   
    shape[2].position = { 30, -15 };  
    shape[3].position = { 0, -30 };   
    shape[4].position = { -30, -15 }; 
    shape[5].position = { -30, 15 };  

    // Ustawienie koloru br�zowego dla wszystkich wierzcho�k�w
    for (size_t i = 0; i < shape.getVertexCount(); i++) {
        shape[i].color = sf::Color(112, 42, 42);
    }

    // Sprawdzenie czy asteroida jest "szcz�liwa" (10% szans)
    lucky = isLucky();

    // Je�li nie jest szcz�liwa, sprawd� czy jest "pechowa" (1% szans)
    if (!lucky) {
        unlucky = isUnlucky();
    }
    else {
        unlucky = false; // Nie mo�e by� jednocze�nie szcz�liwa i pechowa
    }
}

// Sprawdza czy asteroida jest "szcz�liwa" (dodatkowe punkty)
bool Asteroid::isLucky() {
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10); // 1 na 10 szans

    bool luckyRoll = (dist(gen) == 1); // 10% prawdopodobie�stwo

    if (luckyRoll) {
        // Zmiana koloru na ��ty dla szcz�liwej asteroidy
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

    bool unluckyRoll = (dist(gen) == 1) && !lucky; // 1% i nie mo�e by� szcz�liwa

    if (unluckyRoll) {
        // Zmiana koloru na niebieski dla pechowej asteroidy
        for (size_t i = 0; i < shape.getVertexCount(); i++) {
            shape[i].color = sf::Color::Blue;
        }
    }

    return unluckyRoll;
}

// Aktualizuje stan asteroidy co klatk�
void Asteroid::update(float deltaTime)
{
    life += deltaTime; // Aktualizacja czasu �ycia

    // Aktualizacja pozycji zgodnie z kierunkiem i pr�dko�ci�
    position += ASTEROID_SPEED * direction * deltaTime;

    // Obracanie asteroidy
    angle += ASTEROID_SPEED * deltaTime;

    // Obs�uga odbi� od kraw�dzi ekranu
    // Lewa kraw�d�
    if (position.x < ASTEROID_W / 2.0f + 17.0f) {
        direction.x = abs(direction.x); // Odbicie w prawo
    }
    // Prawa kraw�d�
    else if (position.x > SCREEN_WIDTH - ASTEROID_W / 2.0f - 10.0f) {
        direction.x = -abs(direction.x); // Odbicie w lewo
    }

    // G�rna kraw�d�
    if (position.y < ASTEROID_H / 2.0f + 17.0f) {
        direction.y = abs(direction.y); // Odbicie w d�
    }
    // Dolna kraw�d�
    else if (position.y > SCREEN_HEIGHT - ASTEROID_H / 2.0f - 10.0f) {
        direction.y = -abs(direction.y); // Odbicie w g�r�
    }
}

// Generuje losowy kierunek ruchu (znormalizowany wektor)
sf::Vector2f Asteroid::getRandomDirection()
{
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI); // Pe�ny zakres k�t�w

    float angle = dist(gen); // Losowy k�t
    return { cos(angle), sin(angle) }; // Konwersja na wektor kierunku
}

// Generuje losow� pozycj� startow� na ekranie
sf::Vector2f Asteroid::getRandomPosition()
{
    std::random_device rd;  // Inicjalizacja generatora liczb losowych
    std::mt19937 gen(rd());

    // Losowa pozycja X (z uwzgl�dnieniem rozmiaru asteroidy)
    std::uniform_real_distribution<float> xAxis(ASTEROID_W / 2.0f, SCREEN_WIDTH - ASTEROID_W / 2.0f);

    // Losowa pozycja Y (z uwzgl�dnieniem rozmiaru asteroidy)
    std::uniform_real_distribution<float> yAxis(ASTEROID_H / 2.0f, SCREEN_HEIGHT - ASTEROID_H / 2.0f);

    return { xAxis(gen), yAxis(gen) };
}

// Zwraca kszta�t asteroidy (dla detekcji kolizji)
const sf::VertexArray& Asteroid::getVertexArray() const
{
    return shape;
}

// Renderuje asteroid� na ekranie
void Asteroid::render(sf::RenderWindow& window)
{
    sf::Transform transform;
    transform.translate(position).rotate(angle); // Pozycja + rotacja
    window.draw(shape, transform); // Rysowanie kszta�tu
}

// Zwraca czas �ycia asteroidy od ostatniego uderzenia
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
        can_damage = true; // Mo�e ponownie zadawa� obra�enia
    }

    return can_damage;
}