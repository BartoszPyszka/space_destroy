#include <SFML/Graphics.hpp>
#include "GameLogic.h"

int main()
{
    // Zmienne potrzebne do stworzenia okna
    constexpr unsigned int windowWidth = 1200;
    constexpr unsigned int windowHeight = 900;
    const std::string windowTitle = "Space Destroy";

    // Tworzy g��wne okno aplikacji 
    sf::RenderWindow window(sf::VideoMode(windowWidth, 
        windowHeight), windowTitle, sf::Style::Titlebar | 
        sf::Style::Close);

    // Zmienna mierz�ca czas pomi�dzy klatkami, potrzebna
    // do obliczania deltaTime
    sf::Clock clock;

    // Inicjalizacja gry
    GameLogic::init();

    // G��wna p�tla gry. Dzia�a, dop�ki 
    // okno jest otwarte 
    while (window.isOpen()) {

        // Oblicza czas, jaki up�yn�� od 
        // ostatniego od�wie�enia gry, w sekundach.
        // Metoda `clock.restart()` resetuje 
        // zegar i zwraca czas, kt�ry up�yn�� 
        // od ostatniego restartu
        float deltaTime = clock.restart().asSeconds();

        // GameLogic::update aktualizuje logik� 
        // gry (np. poruszanie obiekt�w, obs�ug� 
        // kolizji, renderowanie).
        GameLogic::update(window, deltaTime);

        // Wy�wietla wszystkie elementy w oknie
        window.display();
    }

    return 0;
}
