// Standardowe biblioteki C++ 
#include <vector>                
#include <list>                  
#include <memory>                
#include <fstream>               
#include <string>                
#include <cstdio>               
#include <functional>            
#include <algorithm>  
#include <cmath>

// Własne nagłówki
#include "Bullet.h"

// Konstruktor pocisku 
Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f dir)
    : shape(3.0f),            
    direction(dir),        
    lifetime(BULLET_LIFE),  
    GameObject(startPos, 0.0f)  
{   
    shape.setFillColor(sf::Color::Green);  // Kolor pocisku - zielony
    
    // Załaduj dźwięk 
    if (!soundBuffer.loadFromFile("Assets\\audio\\laserShoot.wav")) {
        printf("Error loading shoot\n");
    }
    else {
        sound.setBuffer(soundBuffer);
        sound.play();  
    }
}
// Aktualizuje stan pocisku 
void Bullet::update(float deltaTime)
{
    if (exploding) {
        if (sound.getStatus() == sf::Sound::Stopped) {
            for (size_t i = 0; i < GameLogic::objects.size(); ++i) {
                if (GameLogic::objects[i].get() == this) {
                    GameLogic::toRemoveIndices.push_back(i);
                    break;
                }
            }
        }
        return;  
    }

    position += direction * BULLET_SPEED * deltaTime;
    lifetime -= deltaTime;

    if (lifetime <= 0.0f) {
        // Jeżli pocisk po prostu "umiera" (bez wybuchu), od razu usuwamy
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

                // Załaduj i odtwórz dźwięk wybuchu
                if (!soundBuffer.loadFromFile("Assets\\audio\\explosion.wav")) {
                    printf("Error loading explosion sound\n");
                }
                else {
                    sound.setBuffer(soundBuffer);
                    sound.play();

                    // Ustaw flagę wybuchu - pocisk nie usuwa się od razu 
                    exploding = true;

                    // Wypełnienie kolorem przezroczystym
                    shape.setFillColor(sf::Color::Transparent);
                }

                // Oznacz asteroidę do usunięcia
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
