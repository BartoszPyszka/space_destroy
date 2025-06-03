#include "Bullet.h"
#include "Asteroid.h"

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

    for (size_t i = 0; i < GameLogic::objects.size(); i++) {

        if (typeid(*GameLogic::objects[i]) == typeid(Asteroid)) {
            Asteroid* asteroid = dynamic_cast<Asteroid*>(GameLogic::objects[i]);

            sf::Transform transform = sf::Transform()
                .translate(asteroid->position)
                .rotate(asteroid->angle);

            if (physics::intersects(position,
                physics::getTransformed(asteroid->getVertexArray(), transform))) {

                lifetime = 0.0f;
                GameLogic::toRemoveList.push_back(std::find(GameLogic::objects.begin(),
                    GameLogic::objects.end(), asteroid));
                GameLogic::score += 5;
            }
        }
        }
    }



void Bullet::render(sf::RenderWindow& window)
{
    shape.setPosition(position);
    window.draw(shape);
}
