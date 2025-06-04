#include "Player.h"

// Konstruktor gracza - inicjalizuje podstawowe w³aœciwoœci
Player::Player()
    : GameObject({ 500, 500 }, 0.0f),  // Start na œrodku ekranu, skierowany w prawo
    shape(sf::LineStrip, 5),         // Przygotowanie kszta³tu z 5 wierzcho³ków
    shootTimer(0.0f)                 // Mo¿na strzelaæ od razu
{
    // Definicja kszta³tu statku 
    shape[0].position = { 10.f, 0.f };   
    shape[1].position = { -10.f, -20.f };
    shape[2].position = { 0.f, 0.f };    
    shape[3].position = { -10.f, 20.f }; 
    shape[4].position = shape[0].position;

    // Ustawienie bia³ego koloru gracza
    for (size_t i = 0; i < shape.getVertexCount(); ++i)
        shape[i].color = sf::Color::White;
}

void Player::update(float deltaTime)
{
    // Aktualizacja timera strza³u (odliczanie do nastêpnego mo¿liwego strza³u)
    shootTimer -= deltaTime;

    // Sterowanie obrotem:
    // A - obrót w lewo, D - obrót w prawo
    // Prêdkoœæ obrotu zale¿na od sta³ej TURN_SPEED i czasu klatki
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) angle -= TURN_SPEED * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) angle += TURN_SPEED * deltaTime;

    // Konwersja k¹ta na radiany dla funkcji trygonometrycznych
    float radians = angle * (M_PI / 180.f);

    // Poruszanie siê do przodu (klawisz W)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        // Obliczenie nowej pozycji na podstawie kierunku
        position.x += std::cos(radians) * PLAYER_SPEED * deltaTime;
        position.y += std::sin(radians) * PLAYER_SPEED * deltaTime;

        // Sprawdzenie granic ekranu (z marginesem 10 pikseli od krawêdzi)
        position.x = std::min(std::max(position.x, PLAYER_W / 2.0f + 10.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
        position.y = std::min(std::max(position.y, PLAYER_H / 2.0f + 10.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
    }

    // Poruszanie siê do ty³u (klawisz S) - 3x wolniej ni¿ do przodu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        position.x -= std::cos(radians) * PLAYER_SPEED * deltaTime / 3;
        position.y -= std::sin(radians) * PLAYER_SPEED * deltaTime / 3;

        // Analogiczne sprawdzenie granic ekranu
        position.x = std::min(std::max(position.x, PLAYER_W / 2.0f + 10.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
        position.y = std::min(std::max(position.y, PLAYER_H / 2.0f + 10.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
    }

    // Mechanika strzelania (spacja)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer <= 0.0f) {
        shootTimer = SHOOT_DELAY;  // Reset timera strza³u
        sf::Vector2f direction = { std::cos(radians), std::sin(radians) };
        // Utworzenie nowego pocisku i dodanie do listy obiektów do dodania
        GameLogic::toAddList.push_back(std::make_unique<Bullet>(position, direction));
    }

    // Przygotowanie transformacji gracza (pozycja + rotacja)
    sf::Transform playerTransform = sf::Transform().translate(position).rotate(angle);

    // Sprawdzenie kolizji z asteroidami
    for (const auto& obj : GameLogic::objects)
    {
        Asteroid* asteroid = dynamic_cast<Asteroid*>(obj.get());
        if (!asteroid) continue;  // Pomijanie obiektów nie bêd¹cych asteroidami

        // Tymczasowa nieœmiertelnoœæ po uderzeniu (eyeframes)
        if (asteroid->getLife() < ASTEROID_HIT_TIME) continue;

        // Pomijanie nieaktywnych asteroid
        if (!asteroid->alive) continue;

        // Przygotowanie transformacji asteroidy
        sf::Transform asteroidTransform = sf::Transform().translate(asteroid->position).rotate(asteroid->angle);

        // Sprawdzenie kolizji miêdzy graczem a asteroid¹
        if (physics::intersects(
            physics::getTransformed(shape, playerTransform),
            physics::getTransformed(asteroid->getVertexArray(), asteroidTransform))) {
            GameLogic::gameOver();  // Kolizja = koniec gry
        }
    }
}

void Player::render(sf::RenderWindow& window)
{
    // Przygotowanie transformacji (pozycja + rotacja)
    sf::Transform transform;
    transform.translate(position).rotate(angle);

    // Narysowanie kszta³tu statku z uwzglêdnieniem transformacji
    window.draw(shape, transform);
}