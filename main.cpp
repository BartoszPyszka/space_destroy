#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <random>
#include "GameObject.h"
#include "Globals.h"
#include "Player.h"
#include "Asteroid.h"
#include "GameLogic.h"

int main()
{
    constexpr unsigned int windowWidth = 1200;
    constexpr unsigned int windowHeight = 900;
    const std::string windowTitle = "Space Destroy";

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Titlebar | sf::Style::Close);
    sf::Clock clock;

    GameLogic::init();

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Obs³uga zdarzeñ (zamykanie okna)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        GameLogic::update(window, deltaTime);

        window.display();
    }

    return 0;
}
