#include "Bullet.h"

// Konstruktor pocisku - inicjalizuje w³aœciwoœci i wygl¹d
Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f dir)
    : shape(3.0f),            // Okr¹g o promieniu 3 pikseli
    direction(dir),         // Kierunek ruchu (znormalizowany wektor)
    lifetime(BULLET_LIFE),  // Czas ¿ycia ustawiony na maksymaln¹ wartoœæ
    GameObject(startPos, 0.0f)  // Inicjalizacja pozycji i k¹ta obrotu
{   
    shape.setFillColor(sf::Color::Green);  // Czerwony kolor pocisku
    // Za³aduj dŸwiêk (sprawdŸ czy siê wczyta³)
    if (!soundBuffer.loadFromFile("Assets\\audio\\laserShoot.wav")) {
        // Obs³u¿ b³¹d wczytania pliku (np. wypisz komunikat)
        printf("Error loading shoot\n");
    }
    else {
        sound.setBuffer(soundBuffer);
        sound.play();  // Odtwórz dŸwiêk raz na start pocisku
    }
}

void Bullet::update(float deltaTime)
{
    // Jeœli pocisk jest w stanie wybuchu, czekaj a¿ dŸwiêk siê skoñczy
    if (exploding) {
        if (sound.getStatus() == sf::Sound::Stopped) {
            // DŸwiêk zakoñczony, oznacz do usuniêcia
            for (size_t i = 0; i < GameLogic::objects.size(); ++i) {
                if (GameLogic::objects[i].get() == this) {
                    GameLogic::toRemoveIndices.push_back(i);
                    break;
                }
            }
        }
        return;  // nie ruszamy siê podczas wybuchu
    }

    // Normalna aktualizacja pozycji i ¿ycia pocisku
    position += direction * BULLET_SPEED * deltaTime;
    lifetime -= deltaTime;

    if (lifetime <= 0.0f) {
        // Jeœli pocisk po prostu "umiera" (bez wybuchu), od razu usuwamy
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
        if (typeid(*GameLogic::objects[i]) == typeid(Asteroid)) {
            Asteroid* asteroid = dynamic_cast<Asteroid*>(GameLogic::objects[i].get());
            sf::Transform transform = sf::Transform()
                .translate(asteroid->position)
                .rotate(asteroid->angle);

            if (physics::intersects(position,
                physics::getTransformed(asteroid->getVertexArray(), transform))) {

                // Za³aduj i odtwórz dŸwiêk wybuchu
                if (!soundBuffer.loadFromFile("Assets\\audio\\explosion.wav")) {
                    printf("Error loading explosion sound\n");
                }
                else {
                    sound.setBuffer(soundBuffer);
                    sound.play();

                    // Ustaw flagê wybuchu - pocisk siê nie usuwa od razu
                    exploding = true;
                    shape.setFillColor(sf::Color::Transparent);
                }

                // Oznacz asteroidê do usuniêcia
                for (size_t j = 0; j < GameLogic::objects.size(); ++j) {
                    if (GameLogic::objects[j].get() == asteroid) {
                        GameLogic::toRemoveIndices.push_back(j);
                        break;
                    }
                }


                // Aktualizacja punktacji i postawienie odpowiedniej animacji
                if (asteroid->lucky) {
                    GameLogic::score += 15;
                    GameLogic::toAddList.push_back(std::make_unique<Explosion>(asteroid->position, Explosion::ExplosionColorType::Lucky));
                }
                else if (asteroid->unlucky) {
                    GameLogic::score += -10;
                    GameLogic::toAddList.push_back(std::make_unique<Explosion>(asteroid->position, Explosion::ExplosionColorType::Unlucky));
                }
                else {
                    GameLogic::score += 5;
                    GameLogic::toAddList.push_back(std::make_unique<Explosion>(asteroid->position, Explosion::ExplosionColorType::Normal));
                }

                // Nie ruszamy wiêcej po kolizji
                break;
            }
        }
    }
}

void Bullet::render(sf::RenderWindow& window)
{
    // Narysuj pocisk w aktualnej pozycji
    window.draw(shape, sf::Transform().translate(position));
}