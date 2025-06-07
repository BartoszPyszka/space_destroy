#include "Player.h"
#include <cmath>        // std::sin, std::cos, M_PI
#include <algorithm>    // std::min, std::max
#include <memory>       // std::make_unique
// Konstruktor gracza - inicjalizuje podstawowe w�a�ciwo�ci
Player::Player(sf::Texture& texture)
    : GameObject({ 500, 500 }, 0.0f),
    Playersprite(texture),
    PlayercurrentFrame(1),
    PlayertotalFrames(6),                // 7 klatek w spritesheet
    PlayerframeTime(0.2f),
    PlayerframeTimer(0.0f),
    PlayerframeSize(192, 164)
{
    Playersprite.setPosition(position);
    Playersprite.setOrigin(PlayerframeSize.x / 2.0f, PlayerframeSize.y / 2.0f);
    Playersprite.setTextureRect(sf::IntRect(0, 0, PlayerframeSize.x, PlayerframeSize.y));
}

void Player::update(float deltaTime)
{
        // Obs�uga ruchu, kolizji itd...

        // Animacja
    PlayerframeTimer += deltaTime;
        if (PlayerframeTimer >= PlayerframeTime) {
            PlayerframeTimer = 0.0f;
            PlayercurrentFrame = (PlayercurrentFrame + 1) % PlayertotalFrames;

            Playersprite.setTextureRect(sf::IntRect(PlayercurrentFrame * PlayerframeSize.x, 0, PlayerframeSize.x, PlayerframeSize.y));
        }

        Playersprite.setPosition(position);
        Playersprite.setRotation(angle);  // zak�adamy, �e rotation masz z GameObject
    // Aktualizacja timera strza�u (odliczanie do nast�pnego mo�liwego strza�u)
    shootTimer -= deltaTime;

    // Sterowanie obrotem:
    // A - obr�t w lewo, D - obr�t w prawo
    // Pr�dko�� obrotu zale�na od sta�ej TURN_SPEED i czasu klatki
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) angle -= TURN_SPEED * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) angle += TURN_SPEED * deltaTime;

    // Konwersja k�ta na radiany dla funkcji trygonometrycznych
    float radians = angle * (M_PI / 180.f);

    // Poruszanie si� do przodu (klawisz W)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        // Obliczenie nowej pozycji na podstawie kierunku
        position.x += std::cos(radians) * PLAYER_SPEED * deltaTime;
        position.y += std::sin(radians) * PLAYER_SPEED * deltaTime;

        // Sprawdzenie granic ekranu (z marginesem 10 pikseli od kraw�dzi)
        position.x = std::min(std::max(position.x, PLAYER_W / 2.0f + 10.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
        position.y = std::min(std::max(position.y, PLAYER_H / 2.0f + 10.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
    }

    // Poruszanie si� do ty�u (klawisz S) - 3x wolniej ni� do przodu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        position.x -= std::cos(radians) * PLAYER_SPEED * deltaTime / 3;
        position.y -= std::sin(radians) * PLAYER_SPEED * deltaTime / 3;

        // Analogiczne sprawdzenie granic ekranu
        position.x = std::min(std::max(position.x, PLAYER_W / 2.0f + 10.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
        position.y = std::min(std::max(position.y, PLAYER_H / 2.0f + 10.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
    }
    sf::Vector2f shootPos = position + sf::Vector2f(std::cos(radians), std::sin(radians)) * 92.f;
    // Mechanika strzelania (spacja)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer <= 0.0f) {
        shootTimer = SHOOT_DELAY;  // Reset timera strza�u
        sf::Vector2f direction = { std::cos(radians), std::sin(radians) };
        // Utworzenie nowego pocisku i dodanie do listy obiekt�w do dodania
        GameLogic::toAddList.push_back(std::make_unique<Bullet>(shootPos, direction));
    }

    // Tworzymy prostok�tny polygon (sf::VertexArray) na podstawie sprite'a gracza

    sf::FloatRect localBounds = Playersprite.getLocalBounds();  // prostok�t w lokalnych wsp�rz�dnych sprite'a

    for (const auto& obj : GameLogic::objects)
    {
        Asteroid* asteroid = dynamic_cast<Asteroid*>(obj.get());
        if (!asteroid) continue;
        if (asteroid->getLife() < ASTEROID_HIT_TIME) continue;
        if (!asteroid->alive) continue;

        // Tworzymy hitboxy gracza na podstawie sprite 
        sf::FloatRect localBounds = Playersprite.getLocalBounds();
        sf::VertexArray playerPolygon(sf::LineStrip, 5);

        //offset pod srodek klatki by hitbox byl w dobym miejscu
        float offsetX = 96.f;
        float offsetY = 82.f;

        //kwadraty hitboxu
        playerPolygon[0].position = { 4.f - offsetX, 50.f - offsetY };
        playerPolygon[1].position = { 188.f - offsetX, 50.f - offsetY };
        playerPolygon[2].position = { 188.f - offsetX, 142.f - offsetY };
        playerPolygon[3].position = { 4.f - offsetX, 142.f - offsetY };
        playerPolygon[4].position = playerPolygon[0].position;

        sf::Transform playerTransform;
        playerTransform.translate(position);
        playerTransform.rotate(angle);
        sf::VertexArray transformedPlayer = physics::getTransformed(playerPolygon, playerTransform);
        // Wyciagamy parametry asteroidy
        sf::Transform asteroidTransform;
        asteroidTransform.translate(asteroid->position);
        asteroidTransform.rotate(asteroid->angle);
        sf::VertexArray transformedAsteroid = physics::getTransformed(asteroid->getVertexArray(), asteroidTransform);

        if (physics::intersects(transformedPlayer, transformedAsteroid)) {
            
            GameLogic::gameOver();
        }
    }
}

void Player::render(sf::RenderWindow& window)
{
    Playersprite.setPosition(position);
    Playersprite.setRotation(angle); // U�yj angle, je�li rotation = angle w Twoim GameObject
    window.draw(Playersprite);
}