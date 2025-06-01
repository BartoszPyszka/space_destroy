#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <random>

// =================== Stałe ===================
constexpr float TURN_SPEED = 200.0f;         // Prędkość obrotu gracza (stopnie/sek)
constexpr float PLAYER_SPEED = 1000.0f;      // Prędkość gracza (piksele/sek)
constexpr float BULLET_SPEED = 400.0f;       // Prędkość pocisku
constexpr float SHOOT_DELAY = 0.2f;          // Odstęp między strzałami
constexpr float BULLET_LIFE = 3.0f;          // Czas życia pocisku
constexpr float M_PI = 3.14159265f;          // Pi (do obliczeń trygonometrycznych)

constexpr float ASTEROID_SPIN = 40.0f;       // Prędkość obrotu asteroidy
constexpr float ASTEROID_SPEED = 200.0f;     // Prędkość ruchu asteroidy
constexpr float ASTEROID_W = 20.0f;          // Szerokość asteroidy
constexpr float ASTEROID_H = 20.0f;          // Wysokość asteroidy

constexpr float SCREEN_WIDTH = 1190.0f;      // Szerokość ekranu
constexpr float SCREEN_HEIGHT = 890.0f;      // Wysokość ekranu

constexpr float PLAYER_W = 4.0f;             // Szerokość gracza
constexpr float PLAYER_H = 4.0f;             // Wysokość gracza

constexpr float ASTEROID_SPAWN_TIME = 2.0f;  // Interwał generowania asteroid

// =================== Klasa bazowa GameObject ===================
class GameObject {
public:
    GameObject(sf::Vector2f pos = { 0, 0 }, float ang = 0.0f)
        : position(pos), angle(ang) {
    }

    virtual ~GameObject() {}

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    sf::Vector2f position;   // Pozycja obiektu
    float angle;             // Kąt obrotu obiektu
};

// =================== Zarządzanie obiektami gry ===================
std::vector<GameObject*> objects{};  // Główna lista obiektów
std::list<std::vector<GameObject*>::const_iterator> toRemoveList{}; // Obiekty do usunięcia
std::list<GameObject*> toAddList{}; // Obiekty do dodania

// =================== Klasa Bullet (pocisk) ===================
class Bullet : public GameObject {
public:
    Bullet(sf::Vector2f startPos, sf::Vector2f dir)
        : GameObject(startPos), shape(3.0f), direction(dir), lifetime(BULLET_LIFE)
    {
        shape.setFillColor(sf::Color::Red);
    }

    void update(float deltaTime) override {
        // Ruch pocisku
        position += direction * BULLET_SPEED * deltaTime;
        lifetime -= deltaTime;

        // Usunięcie po upływie czasu życia
        if (lifetime <= 0.0f) {
            toRemoveList.push_back(std::find(objects.begin(), objects.end(), this));
        }
    }

    void render(sf::RenderWindow& window) override {
        shape.setPosition(position);
        window.draw(shape);
    }

private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    float lifetime;
};

// =================== Klasa Player ===================
class Player : public GameObject {
public:
    Player()
        : GameObject({ 500, 500 }, 0.0f), shape(sf::LineStrip, 5), shootTimer()
    {
        // Kształt statku gracza (trójkąt + zamknięcie)
        shape[0].position = { 10.f, 0.f };
        shape[1].position = { -10.f, -20.f };
        shape[2].position = { 0.f, 0.f };
        shape[3].position = { -10.f, 20.f };
        shape[4].position = shape[0].position;

        for (size_t i = 0; i < shape.getVertexCount(); ++i)
            shape[i].color = sf::Color::White;
    }

    void update(float deltaTime) override {
        shootTimer -= deltaTime;

        // Obrót
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) angle -= TURN_SPEED * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) angle += TURN_SPEED * deltaTime;

        float radians = angle * (M_PI / 180.f);

        // Ruch w przód
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            position.x += std::cos(radians) * PLAYER_SPEED * deltaTime;
            position.y += std::sin(radians) * PLAYER_SPEED * deltaTime;

            // Granice ekranu (z góry i z lewej też)
            position.x = std::min(std::max(position.x, PLAYER_W / 2.0f + 10.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
            position.y = std::min(std::max(position.y, PLAYER_H / 2.0f + 10.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
        }

        // Ruch w tył (wolniejszy)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            position.x -= std::cos(radians) * PLAYER_SPEED * deltaTime / 3;
            position.y -= std::sin(radians) * PLAYER_SPEED * deltaTime / 3;

            // Granice
            position.x = std::min(std::max(position.x, PLAYER_W / 2.0f + 10.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
            position.y = std::min(std::max(position.y, PLAYER_H / 2.0f + 10.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
        }

        // Strzelanie
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer <= 0.0f) {
            shootTimer = SHOOT_DELAY;
            sf::Vector2f direction = { std::cos(radians), std::sin(radians) };
            toAddList.push_back(new Bullet(position, direction));
        }
    }

    void render(sf::RenderWindow& window) override {
        sf::Transform transform;
        transform.translate(position).rotate(angle);
        window.draw(shape, transform);
    }

private:
    sf::VertexArray shape;
    float shootTimer;
};

// =================== Klasa Asteroid ===================
class Asteroid : public GameObject {
public:
    Asteroid(sf::Vector2f direction = getRandomDirection(), sf::Vector2f position = getRandomPosition())
        : GameObject(position, 0.0f), direction(direction), shape(sf::TrianglesFan, 6), life()
    {
        // Kształt asteroidy 
        shape[0].position = { 0, 30 };
        shape[1].position = { 30, 15 };
        shape[2].position = { 30, -15 };
        shape[3].position = { 0, -30 };
        shape[4].position = { -30, -15 };
        shape[5].position = { -30, 15 };

        for (size_t i = 0; i < shape.getVertexCount(); ++i)
            shape[i].color = sf::Color::White;

        // Ładowanie dźwięku odbicia
        if (!bounceBuffer.loadFromFile("assets/bounce.wav"))
            std::cerr << "Nie udalo sie zaladowac dzwieku odbicia!" << std::endl;
        bounceSound.setBuffer(bounceBuffer);
    }

    void update(float deltaTime) override {
        life += deltaTime;
        position += ASTEROID_SPEED * direction * deltaTime;
        angle += ASTEROID_SPIN * deltaTime;

        // Odbicia od ścian (x i y)
        if (position.x < ASTEROID_W / 2.0f + 17.0f) {
            direction.x = abs(direction.x);
            bounceSound.play();
        }
        else if (position.x > SCREEN_WIDTH - ASTEROID_W / 2.0f - 10.0f) {
            direction.x = -abs(direction.x);
            bounceSound.play();
        }

        if (position.y < ASTEROID_H / 2.0f + 17.0f) {
            direction.y = abs(direction.y);
            bounceSound.play();
        }
        else if (position.y > SCREEN_HEIGHT - ASTEROID_H / 2.0f - 10.0f) {
            direction.y = -abs(direction.y);
            bounceSound.play();
        }
    }

    static sf::Vector2f getRandomDirection() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI);
        float angle = dist(gen);
        return { cos(angle), sin(angle) };
    }

    static sf::Vector2f getRandomPosition() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> xAxis(ASTEROID_W / 2.0f, SCREEN_WIDTH - ASTEROID_W / 2.0f);
        std::uniform_real_distribution<float> yAxis(ASTEROID_H / 2.0f, SCREEN_HEIGHT - ASTEROID_H / 2.0f);
        return { xAxis(gen), yAxis(gen) };
    }

    void render(sf::RenderWindow& window) override {
        sf::Transform transform;
        transform.translate(position).rotate(angle);
        window.draw(shape, transform);
    }

private:
    sf::VertexArray shape;
    float life;
    sf::Vector2f direction;
    sf::SoundBuffer bounceBuffer;
    sf::Sound bounceSound;
};

// =================== Funkcja main ===================
int main()
{
    constexpr unsigned int windowWidth = 1200;
    constexpr unsigned int windowHeight = 900;
    const std::string windowTitle = "Space Destroy";

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Titlebar | sf::Style::Close);
    sf::Clock clock;

    // Dodanie gracza
    objects.push_back(new Player());

    float asteroidSprawnTime = ASTEROID_SPAWN_TIME;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Obsługa zdarzeń (zamykanie okna)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        toAddList.clear();
        toRemoveList.clear();

        asteroidSprawnTime -= deltaTime;

        // Aktualizacja i rysowanie obiektów
        for (GameObject* obj : objects) {
            obj->update(deltaTime);
            obj->render(window);
        }

        // Usuwanie
        for (const auto& it : toRemoveList) {
            delete* it;
            objects.erase(it);
        }

        // Dodawanie
        for (GameObject* obj : toAddList) {
            objects.push_back(obj);
        }

        // Dodanie nowej asteroidy co jakiś czas
        if (asteroidSprawnTime <= 0.0f) {
            objects.push_back(new Asteroid());
            asteroidSprawnTime = ASTEROID_SPAWN_TIME;
        }

        window.display();
    }

    return 0;
}
