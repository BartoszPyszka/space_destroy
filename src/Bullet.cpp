#include "Bullet.h"

// Konstruktor pocisku - inicjalizuje w³aœciwoœci i wygl¹d
Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f dir)
    : shape(3.0f),            // Okr¹g o promieniu 3 pikseli
    direction(dir),         // Kierunek ruchu (znormalizowany wektor)
    lifetime(BULLET_LIFE),  // Czas ¿ycia ustawiony na maksymaln¹ wartoœæ
    GameObject(startPos, 0.0f)  // Inicjalizacja pozycji i k¹ta obrotu
{
    shape.setFillColor(sf::Color::Green);  // Czerwony kolor pocisku
}

void Bullet::update(float deltaTime)
{
    // Aktualizacja pozycji pocisku
    // Porusza siê w ustalonym kierunku ze sta³¹ prêdkoœci¹
    position += direction * BULLET_SPEED * deltaTime;

    // Odliczanie czasu ¿ycia pocisku
    lifetime -= deltaTime;

    // Mechanika znikania pocisku po up³ywie czasu ¿ycia
    if (lifetime <= 0.0f) {
        // ZnajdŸ i oznacz ten pocisk do usuniêcia
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
        // SprawdŸ czy obiekt jest asteroid¹
        if (typeid(*GameLogic::objects[i]) == typeid(Asteroid)) {
            Asteroid* asteroid = dynamic_cast<Asteroid*>(GameLogic::objects[i].get());

            // Przygotuj transformacjê asteroidy (pozycja + rotacja)
            sf::Transform transform = sf::Transform()
                .translate(asteroid->position)
                .rotate(asteroid->angle);

            // SprawdŸ kolizjê pocisku z asteroid¹
            if (physics::intersects(position,
                physics::getTransformed(asteroid->getVertexArray(), transform))) {

                lifetime = 0.0f;  // Oznacz pocisk do usuniêcia

                // ZnajdŸ i oznacz asteroidê do usuniêcia
                for (size_t j = 0; j < GameLogic::objects.size(); ++j) {
                    if (GameLogic::objects[j].get() == asteroid) {
                        GameLogic::toRemoveIndices.push_back(j);
                        break;
                    }
                }

                // Aktualizacja punktacji w zale¿noœci od typu asteroidy
                if (asteroid->lucky) {
                    GameLogic::score += 15;  // Bonus za szczêœliw¹ asteroidê
                }
                else if (asteroid->unlucky) {
                    GameLogic::score += -10; // Kara za pechow¹ asteroidê
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