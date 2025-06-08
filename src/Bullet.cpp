#include "Bullet.h"

// Konstruktor pocisku - inicjalizuje w�a�ciwo�ci i wygl�d
Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f dir)
    : shape(3.0f),            // Okr�g o promieniu 3 pikseli
    direction(dir),         // Kierunek ruchu (znormalizowany wektor)
    lifetime(BULLET_LIFE),  // Czas �ycia ustawiony na maksymaln� warto��
    GameObject(startPos, 0.0f)  // Inicjalizacja pozycji i k�ta obrotu
{   
    shape.setFillColor(sf::Color::Green);  // Czerwony kolor pocisku
    // Za�aduj d�wi�k (sprawd� czy si� wczyta�)
    if (!soundBuffer.loadFromFile("Assets\\audio\\laserShoot.wav")) {
        // Obs�u� b��d wczytania pliku (np. wypisz komunikat)
        printf("Error loading shoot\n");
    }
    else {
        sound.setBuffer(soundBuffer);
        sound.play();  // Odtw�rz d�wi�k raz na start pocisku
    }
}

void Bullet::update(float deltaTime)
{
    // Je�li pocisk jest w stanie wybuchu, czekaj a� d�wi�k si� sko�czy
    if (exploding) {
        if (sound.getStatus() == sf::Sound::Stopped) {
            // D�wi�k zako�czony, oznacz do usuni�cia
            for (size_t i = 0; i < GameLogic::objects.size(); ++i) {
                if (GameLogic::objects[i].get() == this) {
                    GameLogic::toRemoveIndices.push_back(i);
                    break;
                }
            }
        }
        return;  // nie ruszamy si� podczas wybuchu
    }

    // Normalna aktualizacja pozycji i �ycia pocisku
    position += direction * BULLET_SPEED * deltaTime;
    lifetime -= deltaTime;

    if (lifetime <= 0.0f) {
        // Je�li pocisk po prostu "umiera" (bez wybuchu), od razu usuwamy
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

                // Za�aduj i odtw�rz d�wi�k wybuchu
                if (!soundBuffer.loadFromFile("Assets\\audio\\explosion.wav")) {
                    printf("Error loading explosion sound\n");
                }
                else {
                    sound.setBuffer(soundBuffer);
                    sound.play();

                    // Ustaw flag� wybuchu - pocisk si� nie usuwa od razu
                    exploding = true;
                    shape.setFillColor(sf::Color::Transparent);
                }

                // Oznacz asteroid� do usuni�cia
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

                // Nie ruszamy wi�cej po kolizji
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