#include <SFML/Graphics.hpp>
#include "GameLogic.h"

int main()
{
    // Zmienne potrzebne do stworzenia okna
    constexpr unsigned int windowWidth = 1200;
    constexpr unsigned int windowHeight = 900;
    const std::string windowTitle = "Space Destroy";

    // Tworzy g³ówne okno aplikacji 
    sf::RenderWindow window(sf::VideoMode(windowWidth, 
        windowHeight), windowTitle, sf::Style::Titlebar | 
        sf::Style::Close);

    // Zmienna mierz¹ca czas pomiêdzy klatkami, potrzebna
    // do obliczania deltaTime
    sf::Clock clock;

    // Inicjalizacja gry
    GameLogic::init();

    // G³ówna pêtla gry. Dzia³a, dopóki 
    // okno jest otwarte 
    while (window.isOpen()) {

        // Oblicza czas, jaki up³yn¹³ od 
        // ostatniego odœwie¿enia gry, w sekundach.
        // Metoda `clock.restart()` resetuje 
        // zegar i zwraca czas, który up³yn¹³ 
        // od ostatniego restartu
        float deltaTime = clock.restart().asSeconds();

        // GameLogic::update aktualizuje logikê 
        // gry (np. poruszanie obiektów, obs³ugê 
        // kolizji, renderowanie).
        GameLogic::update(window, deltaTime);

        // Wyœwietla wszystkie elementy w oknie
        window.display();
    }

    return 0;
}
