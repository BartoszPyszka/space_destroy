#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// Stałe określające szybkość obrotu i ruchu gracza
//test
constexpr float TURN_SPEED = 200.0f;           // Prędkość obrotu (stopnie na sekundę)
constexpr float PLAYER_SPEED = 100.0f;         // Prędkość ruchu gracza (piksele na sekundę)
constexpr float M_PI = 3.14159265f;            // Stała Pi do przeliczenia na radiany


// Bazowa klasa dla wszystkich obiektów gry
class GameObject
{
public:
    GameObject();
    ~GameObject();

    // Wirtualne metody do nadpisania przez klasy dziedziczące
    virtual void update(float deltaTime) = 0;       // Aktualizacja stanu obiektu
    virtual void render(sf::RenderWindow& window) = 0;     // Rysowanie obiektu w oknie

private:

};

// Implementacja konstruktora i destruktora klasy bazowej
GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

// Klasa gracza, dziedziczy po GameObject
class Player : public GameObject {
public:
    Player();
    ~Player();

    // Aktualizacja stanu gracza (obrót i ruch)
    void update(float deltaTime) override; //override- nadpisanie klasy wirtualnej

    // Rysowanie gracza w oknie
    void render(sf::RenderWindow& window) override; //override- nadpisanie klasy wirtualnej

private:
    sf::Vector2f position;     // Aktualna pozycja gracza na ekranie
    float angle;               // Kąt obrotu gracza (w stopniach)
    sf::VertexArray shape;     // Graficzna reprezentacja statku jako zbiór wierzchołków
};

// Konstruktor gracza — ustawienie początkowej pozycji, kąta i kształtu
Player::Player()
    : position(500.f, 500.f), angle(45.f), shape(sf::LineStrip, 5)
{
    // Definicja punktów tworzących kształt statku
    shape[0].position = sf::Vector2f(10.f, 0.f);     // Wierzchołek "przodu" statku
    shape[1].position = sf::Vector2f(-10.f, -20.f);  // Lewy "róg" tyłu
    shape[2].position = sf::Vector2f(0.f, 0.f);      // Środkowy punkt tyłu
    shape[3].position = sf::Vector2f(-10.f, 20.f);   // Prawy "róg" tyłu
    shape[4].position = shape[0].position;           // Zamknięcie kształtu (wracamy do przodu)

    // Ustawienie koloru każdego wierzchołka na biały
    for (size_t i = 0; i < shape.getVertexCount(); ++i) {
        shape[i].color = sf::Color::White;
    }
}

Player::~Player() = default;

// Aktualizacja stanu gracza na podstawie wejścia użytkownika
void Player::update(float deltaTime) {
    // Obrót w lewo (A)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        angle -= TURN_SPEED * deltaTime;
    }

    // Obrót w prawo (D)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        angle += TURN_SPEED * deltaTime;
    }

    // Ruch do przodu (W)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        // Konwersja kąta na radiany dla funkcji trygonometrycznych
        float radians = angle * (M_PI / 180.0f);

        // Przesuwanie pozycji gracza w kierunku aktualnego obrotu
        position.x += std::cos(radians) * PLAYER_SPEED * deltaTime;
        position.y += std::sin(radians) * PLAYER_SPEED * deltaTime;
    }

    // Ruch do tyłu (S)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        float radians = angle * (M_PI / 180.0f);

        // Ruch w przeciwnym kierunku, ale wolniejszy (1/3 prędkości)
        position.x -= (std::cos(radians) * PLAYER_SPEED * deltaTime) / 3;
        position.y -= (std::sin(radians) * PLAYER_SPEED * deltaTime) / 3;
    }
}


// Rysowanie gracza z odpowiednią transformacją
void Player::render(sf::RenderWindow& window) {
    sf::Transform transform;
    transform.translate(position).rotate(angle);
    window.draw(shape, transform);
}

// Wektor przechowujący wskaźniki do wszystkich obiektów gry
std::vector<GameObject*> objects{};

int main()
{
    // Parametry okna gry
    constexpr unsigned int windowWidth = 1200;
    constexpr unsigned int windowHeight = 900;
    const std::string windowTitle = "Space Destroy";

    // Tworzenie głównego okna gry
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Titlebar | sf::Style::Close);

    // Zegar do obliczania czasu między klatkami
    sf::Clock clock;

    // Dodanie gracza do listy obiektów gry
    objects.push_back(new Player());

    // Główna pętla gry
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Obsługa zdarzeń (np. zamknięcie okna)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Czyszczenie ekranu (kolor czarny)
        window.clear(sf::Color::Black);

        // Aktualizacja i rysowanie wszystkich obiektów gry
        for (auto& object : objects)
        {
            object->update(deltaTime);
            object->render(window);
        }

        // Wyświetlenie zawartości na ekranie
        window.display();
    }

    return 0;
}
