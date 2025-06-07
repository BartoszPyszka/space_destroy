#include "Player.h"
#include <cmath>        // std::sin, std::cos, M_PI
#include <algorithm>    // std::min, std::max
#include <memory>       // std::make_unique
// Konstruktor gracza - inicjalizuje podstawowe w³aœciwoœci
Player::Player(sf::Texture& texture)
    : GameObject({ 500, 500 }, 0.0f),
    Playersprite(texture),
    PlayercurrentFrame(1),
    PlayertotalFrames(5),                // 7 klatek w spritesheet
    PlayerframeTime(0.2f),
    PlayerframeTimer(0.0f),
    PlayerframeSize(192, 164)
{
    originalTexture = &texture;  // zapamiêtaj oryginaln¹ teksturê

    if (!boostTexture.loadFromFile("Assets//graphics//boost.png")) {
        printf("Error loading boost texture\n");
    }
    if (!bonusBuffer.loadFromFile("Assets/audio/bonus.mp3")) {
        printf("Error loading bonus sound\n");
    }
    else {
        bonusSound.setBuffer(bonusBuffer);
    }

    Playersprite.setPosition(position);
    Playersprite.setOrigin(PlayerframeSize.x / 2.0f, PlayerframeSize.y / 2.0f);
    Playersprite.setTextureRect(sf::IntRect(0, 0, PlayerframeSize.x, PlayerframeSize.y));
}

void Player::update(float deltaTime)
{
    // Obs³uga bonusów
    if (currentBonus != BonusType::None) {
        bonusTimer -= deltaTime;
        if (bonusTimer <= 0.0f) {
            currentBonus = BonusType::None;
            shootDelayBase = SHOOT_DELAY;
            playerSpeedBase = PLAYER_SPEED;
            invincible = false;
        }
    }
    else {
        // Losowe przyznanie bonusu co jakiœ czas
        static float bonusSpawnTimer = 0.0f;
        bonusSpawnTimer += deltaTime;
        if (bonusSpawnTimer >= 15.f) {
            bonusSpawnTimer = 0.0f;

            int r = rand() % 3;
            bonusTimer = 5.0f;  // Czas trwania bonusu

            switch (r) {
            case 0:
                currentBonus = BonusType::FastShoot;
                shootDelayBase = SHOOT_DELAY / 10.0f;
                break;
            case 1:
                currentBonus = BonusType::FastMove;
                playerSpeedBase = PLAYER_SPEED * 3.f;
                break;
            case 2:
                currentBonus = BonusType::Invincible;
                invincible = true;
                break;
            }
            bonusSound.play();

        }
    }
    // Zmiana wygladu na nieœmiertelnoœæ
    if (invincible) {
        // Miganie co 0.2 sekundy
        static float blinkTimer = 0.0f;
        blinkTimer += deltaTime;
        if (blinkTimer >= 0.2f) blinkTimer = 0.0f;

        if (blinkTimer < 0.1f)
            Playersprite.setColor(sf::Color(100, 200, 255, 180)); // widoczny
        else
            Playersprite.setColor(sf::Color(100, 200, 255, 80)); // pó³przezroczysty
    }
    else {
        Playersprite.setColor(sf::Color::White);
    }
    // Zmiana animacji na bonusie predkosci
    if (currentBonus == BonusType::FastMove) {
        Playersprite.setTexture(boostTexture);
    }
    else {
        Playersprite.setTexture(*originalTexture);
    }



        // Animacja
    PlayerframeTimer += deltaTime;
        if (PlayerframeTimer >= PlayerframeTime) {
            PlayerframeTimer = 0.0f;
            PlayercurrentFrame = (PlayercurrentFrame + 1) % PlayertotalFrames;

            Playersprite.setTextureRect(sf::IntRect(PlayercurrentFrame * PlayerframeSize.x, 0, PlayerframeSize.x, PlayerframeSize.y));
        }

        Playersprite.setPosition(position);
        Playersprite.setRotation(angle);  // zak³adamy, ¿e rotation masz z GameObject
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
        position.x += std::cos(radians) * playerSpeedBase * deltaTime;
        position.y += std::sin(radians) * playerSpeedBase * deltaTime;

        // Sprawdzenie granic ekranu (z marginesem 10 pikseli od krawêdzi)
        position.x = std::min(std::max(position.x, PLAYER_W / 2.0f + 10.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
        position.y = std::min(std::max(position.y, PLAYER_H / 2.0f + 10.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
    }

    // Poruszanie siê do ty³u (klawisz S) - 3x wolniej ni¿ do przodu
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        position.x -= std::cos(radians) * playerSpeedBase * deltaTime / 2;
        position.y -= std::sin(radians) * playerSpeedBase * deltaTime / 2;

        // Analogiczne sprawdzenie granic ekranu
        position.x = std::min(std::max(position.x, PLAYER_W / 2.0f + 10.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
        position.y = std::min(std::max(position.y, PLAYER_H / 2.0f + 10.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
    }
    sf::Vector2f forward = { std::cos(radians), std::sin(radians) };
    sf::Vector2f perpendicular = { -forward.y, forward.x };

    sf::Vector2f cannonBase = position + forward * 54.f; // 64 - 10
    sf::Vector2f topCannon = cannonBase - perpendicular * 0.1f;
    sf::Vector2f bottomCannon = cannonBase + perpendicular * 20.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer <= 0.0f) {
        shootTimer = shootDelayBase;
        sf::Vector2f direction = forward;

        GameLogic::toAddList.push_back(std::make_unique<Bullet>(topCannon, direction));
        GameLogic::toAddList.push_back(std::make_unique<Bullet>(bottomCannon, direction));
    }



    // Tworzymy prostok¹tny polygon (sf::VertexArray) na podstawie sprite'a gracza

    sf::FloatRect localBounds = Playersprite.getLocalBounds();  // prostok¹t w lokalnych wspó³rzêdnych sprite'a

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
        playerPolygon[0].position = { 56.f - offsetX, 66.f - offsetY };
        playerPolygon[1].position = { 154.f - offsetX, 66.f - offsetY };
        playerPolygon[2].position = { 154.f - offsetX, 128.f - offsetY };
        playerPolygon[3].position = { 56.f - offsetX, 128.f - offsetY };
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
            if (!invincible) {
                GameLogic::gameOver();
            }
        }
    }
}

void Player::render(sf::RenderWindow& window)
{
    Playersprite.setPosition(position);
    Playersprite.setRotation(angle); // U¿yj angle, jeœli rotation = angle w Twoim GameObject
    window.draw(Playersprite);
}