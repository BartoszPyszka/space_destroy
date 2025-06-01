#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <list>

// Stałe do kontroli ruchu i obrotu
constexpr float TURN_SPEED = 200.0f;     // stopnie/sek
constexpr float PLAYER_SPEED = 1000.0f;     // piksele/sek
constexpr float BULLET_SPEED = 400.0f;     // prędkość pocisku
constexpr float SHOOT_DELAY = 0.2f;       // opóźnienie między strzałami
constexpr float BULLET_LIFE = 3.0f;       // czas życia pocisku w sekundach
constexpr float M_PI = 3.14159265f; // stała Pi
constexpr float ASTEROID_SPIN = 40.0f;
constexpr float ASTEROID_SPEED = 200.0f;
constexpr float ASTEROID_W = 20.0f;
constexpr float ASTEROID_H = 20.0f;
constexpr float SCREEN_WIDTH = 1190.0f;
constexpr float SCREEN_HEIGHT = 890.0;
constexpr float PLAYER_W = 4.0f;
constexpr float PLAYER_H = 4.0f;


// Klasa bazowa dla wszystkich obiektów gry
class GameObject {
public:
    GameObject(sf::Vector2f pos = { 0, 0 }, float ang = 0.0f)
        : position(pos), angle(ang) {
    }

    virtual ~GameObject() {}

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    sf::Vector2f position;
    float angle;
};

// Wektor przechowujący wszystkie obiekty gry (globalnie dostępny)
std::vector<GameObject*> objects{};

// Listy do późniejszego dodawania i usuwania obiektów (aby uniknąć modyfikacji wektora w trakcie iteracji)
std::list<std::vector<GameObject*>::const_iterator> toRemoveList{};
std::list<GameObject*> toAddList{};

// Klasa pocisku (Bullet)
class Bullet : public GameObject {
public:
    Bullet(sf::Vector2f startPos, sf::Vector2f dir)
        : GameObject(startPos), shape(3.0f), direction(dir), lifetime(BULLET_LIFE)
    {
        shape.setFillColor(sf::Color::Red); // Kolor pocisku
    }

    void update(float deltaTime) override {
        // Przesuwanie pocisku w zadanym kierunku
        position += direction * BULLET_SPEED * deltaTime;

        // Zmniejszanie czasu życia
        lifetime -= deltaTime;

        // Usunięcie pocisku po jego "wygaśnięciu"
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

// Klasa gracza
class Player : public GameObject {
public:
    Player()
        : GameObject({ 500, 500 }, 0.0f), shape(sf::LineStrip, 5), shootTimer()
    {
        // Kształt statku 
        shape[0].position = sf::Vector2f(10.f, 0.f);
        shape[1].position = sf::Vector2f(-10.f, -20.f);
        shape[2].position = sf::Vector2f(0.f, 0.f);
        shape[3].position = sf::Vector2f(-10.f, 20.f);
        shape[4].position = shape[0].position;

        for (size_t i = 0; i < shape.getVertexCount(); ++i)
            shape[i].color = sf::Color::White;
    }

    void update(float deltaTime) override {
        shootTimer -= deltaTime; // Odliczanie do następnego możliwego strzału

        // Obrót gracza
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            angle -= TURN_SPEED * deltaTime;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            angle += TURN_SPEED * deltaTime;

        float radians = angle * (M_PI / 180.f);

        // Ruch do przodu
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            position.x += std::cos(radians) * PLAYER_SPEED * deltaTime;
            position.y += std::sin(radians) * PLAYER_SPEED * deltaTime;

            // Ustawienie granicy dla gracza
            position.x = std::min(std::max(position.x, PLAYER_W / 2.0f + 10.0f),
                SCREEN_WIDTH - PLAYER_W / 2.0f);
            position.y = std::min(std::max(position.y, PLAYER_H / 2.0f + 10.0f),
                SCREEN_HEIGHT - PLAYER_H / 2.0f);
        }

        // Ruch do tyłu (wolniejszy)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            position.x -= std::cos(radians) * PLAYER_SPEED * deltaTime / 3;
            position.y -= std::sin(radians) * PLAYER_SPEED * deltaTime / 3;

            // Ustawienie granicy dla gracza
            position.x = std::min(std::max(position.x, PLAYER_W / 2.0f + 10.0f),
                SCREEN_WIDTH - PLAYER_W / 2.0f);
            position.y = std::min(std::max(position.y, PLAYER_H / 2.0f + 10.0f),
                SCREEN_HEIGHT - PLAYER_H / 2.0f);
        }

        // Strzelanie pociskiem (spacja)
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
    float shootTimer; // Timer między strzałami
};

class Asteroid : public GameObject {
public:
    Asteroid(sf::Vector2f direction)
        : GameObject(sf::Vector2f(700, 300), 0.0f), direction(direction), shape(sf::TrianglesFan, 6), life() {


        shape[0].position = sf::Vector2f(0, 30);
        shape[1].position = sf::Vector2f(30, 15);
        shape[2].position = sf::Vector2f(30, -15);
        shape[3].position = sf::Vector2f(0, -30);
        shape[4].position = sf::Vector2f(-30, -15);
        shape[5].position = sf::Vector2f(-30, 15);

        for (size_t i = 0; i < shape.getVertexCount(); ++i)
            shape[i].color = sf::Color::White;

        if (!bounceBuffer.loadFromFile("assets/bounce.wav")) {
            std::cerr << "Nie udalo sie zaladowac dzwieku odbicia!" << std::endl;
        }
        bounceSound.setBuffer(bounceBuffer);

    }

    void update(float deltaTime) override {
        // Zwiększanie czasu życia asteroidy
        life += deltaTime;

        // Przesuwanie asteroidy w aktualnym kierunku z uwzględnieniem prędkości i czasu
        position += ASTEROID_SPEED * direction * deltaTime;

        // Obrót asteroidy
        angle += ASTEROID_SPIN * deltaTime;

        // Odbicie od lewej krawędzi ekranu
        if (position.x < ASTEROID_W / 2.0f + 17.0f) {
            direction.x = abs(direction.x);       // zmień kierunek na dodatni w osi X
            bounceSound.play();                   // odtwórz dźwięk odbicia
        }

        // Odbicie od prawej krawędzi ekranu
        else if (position.x > SCREEN_WIDTH - ASTEROID_W / 2.0f - 10.0f) {
            direction.x = -abs(direction.x);      // zmień kierunek na ujemny w osi X
            bounceSound.play();                   // odtwórz dźwięk odbicia
        }

        // Odbicie od górnej krawędzi ekranu
        if (position.y < ASTEROID_H / 2.0f + 17.0f) {
            direction.y = abs(direction.y);       // zmień kierunek na dodatni w osi Y
            bounceSound.play();                   // odtwórz dźwięk odbicia
        }

        // Odbicie od dolnej krawędzi ekranu
        else if (position.y > SCREEN_HEIGHT - ASTEROID_H / 2.0f - 10.0f) {
            direction.y = -abs(direction.y);      // zmień kierunek na ujemny w osi Y
            bounceSound.play();                   // odtwórz dźwięk odbicia
        }
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

// Funkcja główna programu
int main()
{
    constexpr unsigned int windowWidth = 1200;
    constexpr unsigned int windowHeight = 900;
    const std::string windowTitle = "Space Destroy";

    // Tworzenie okna gry
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Titlebar | sf::Style::Close);
    sf::Clock clock;

    // Dodanie gracza do gry
    objects.push_back(new Player());
    // Dodanie asteroidy do gry
    objects.push_back(new Asteroid(sf::Vector2f(1, 1)));

    // Główna pętla gry
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Obsługa zdarzeń
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Czyszczenie ekranu
        window.clear(sf::Color::Black);
        toAddList.clear();
        toRemoveList.clear();

        // Aktualizacja i rysowanie obiektów
        for (GameObject* obj : objects) {
            obj->update(deltaTime);
            obj->render(window);
        }

        // Usunięcie obiektów oznaczonych do usunięcia
        for (const auto& it : toRemoveList) {
            delete* it;
            objects.erase(it);
        }

        // Dodanie nowych obiektów
        for (GameObject* obj : toAddList) {
            objects.push_back(obj);
        }

        // Wyświetlenie ekranu
        window.display();
    }

    return 0;
}
