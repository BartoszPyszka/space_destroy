#include "Bullet.h"

Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f dir)
    : shape(3.0f), direction(dir), lifetime(BULLET_LIFE), GameObject(startPos, 0.0f)
{
    shape.setFillColor(sf::Color::Red);
}

void Bullet::update(float deltaTime)
{
    // Ruch pocisku
    position += direction * BULLET_SPEED * deltaTime;
    lifetime -= deltaTime;

    // Usuniêcie po up³ywie czasu ¿ycia
    if (lifetime <= 0.0f) {
        GameLogic::toRemoveList.push_back(std::find(GameLogic::objects.begin(), 
            GameLogic::objects.end(), this));
    }
}

void Bullet::render(sf::RenderWindow& window)
{
    shape.setPosition(position);
    window.draw(shape);
}
