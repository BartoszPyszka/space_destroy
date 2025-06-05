#include "Bullet.h"

// Konstruktor pocisku - inicjalizuje w�a�ciwo�ci i wygl�d
Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f dir)
    : shape(3.0f),            // Okr�g o promieniu 3 pikseli
    direction(dir),         // Kierunek ruchu (znormalizowany wektor)
    lifetime(BULLET_LIFE),  // Czas �ycia ustawiony na maksymaln� warto��
    GameObject(startPos, 0.0f)  // Inicjalizacja pozycji i k�ta obrotu
{
    shape.setFillColor(sf::Color::Green);  // Czerwony kolor pocisku
}

void Bullet::update(float deltaTime)
{
    // Aktualizacja pozycji pocisku
    // Porusza si� w ustalonym kierunku ze sta�� pr�dko�ci�
    position += direction * BULLET_SPEED * deltaTime;

    // Odliczanie czasu �ycia pocisku
    lifetime -= deltaTime;

    // Mechanika znikania pocisku po up�ywie czasu �ycia
    if (lifetime <= 0.0f) {
        // Znajd� i oznacz ten pocisk do usuni�cia
        for (size_t i = 0; i < GameLogic::objects.size(); ++i) {
            if (GameLogic::objects[i].get() == this) {
                GameLogic::toRemoveIndices.push_back(i);
                break;
            }
        }
        return;
    }

    // Sprawdzanie kolizji z asteroidami
    for (size_t i = 0; i < GameLogic::objects.size(); i++) {
        // Sprawd� czy obiekt jest asteroid�
        if (typeid(*GameLogic::objects[i]) == typeid(Asteroid)) {
            Asteroid* asteroid = dynamic_cast<Asteroid*>(GameLogic::objects[i].get());

            // Przygotuj transformacj� asteroidy (pozycja + rotacja)
            sf::Transform transform = sf::Transform()
                .translate(asteroid->position)
                .rotate(asteroid->angle);

            // Sprawd� kolizj� pocisku z asteroid�
            if (physics::intersects(position,
                physics::getTransformed(asteroid->getVertexArray(), transform))) {

                lifetime = 0.0f;  // Oznacz pocisk do usuni�cia

                // Znajd� i oznacz asteroid� do usuni�cia
                for (size_t j = 0; j < GameLogic::objects.size(); ++j) {
                    if (GameLogic::objects[j].get() == asteroid) {
                        GameLogic::toRemoveIndices.push_back(j);
                        break;
                    }
                }

                // Aktualizacja punktacji w zale�no�ci od typu asteroidy
                if (asteroid->lucky) {
                    GameLogic::score += 15;  // Bonus za szcz�liw� asteroid�
                }
                else if (asteroid->unlucky) {
                    GameLogic::score += -10; // Kara za pechow� asteroid�
                }
                else {
                    GameLogic::score += 5;  // Standardowa punktacja
                }
            }
        }
    }
}

void Bullet::render(sf::RenderWindow& window)
{
    // Narysuj pocisk w aktualnej pozycji
    window.draw(shape, sf::Transform().translate(position));
}