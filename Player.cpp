#include "Player.h"

Player::Player()
    : GameObject({ 500, 500 }, 0.0f), shape(sf::LineStrip, 5), shootTimer()
{
    // Kszta³t statku gracza (trójk¹t + zamkniêcie)
    shape[0].position = { 10.f, 0.f };
    shape[1].position = { -10.f, -20.f };
    shape[2].position = { 0.f, 0.f };
    shape[3].position = { -10.f, 20.f };
    shape[4].position = shape[0].position;

    for (size_t i = 0; i < shape.getVertexCount(); ++i)
        shape[i].color = sf::Color::White;
}

void Player::update(float deltaTime)
{
    shootTimer -= deltaTime;

    // Obrót
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) angle -= TURN_SPEED * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) angle += TURN_SPEED * deltaTime;

    float radians = angle * (M_PI / 180.f);

    // Ruch w przód
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        position.x += std::cos(radians) * PLAYER_SPEED * deltaTime;
        position.y += std::sin(radians) * PLAYER_SPEED * deltaTime;

        // Granice ekranu (z góry i z lewej te¿)
        position.x = std::min(std::max(position.x, PLAYER_W / 2.0f + 10.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
        position.y = std::min(std::max(position.y, PLAYER_H / 2.0f + 10.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
    }

    // Ruch w ty³ (wolniejszy)
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
        GameLogic::toAddList.push_back(new Bullet(position, direction));
    }
}

void Player::render(sf::RenderWindow& window)
{
    sf::Transform transform;
    transform.translate(position).rotate(angle);
    window.draw(shape, transform);
}
