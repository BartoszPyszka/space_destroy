// Biblioteki zewnętrzne (SFML)
#include <SFML/Graphics.hpp>

// Własne nagłówki
#include "GameLogic.h"

int main()
{
    // Zmienne potrzebne do stworzenia okna
    constexpr unsigned int windowWidth = 1200;
    constexpr unsigned int windowHeight = 900;
    const std::string windowTitle = "Space Destroy";

    // Tworzy główne okno aplikacji 
    sf::RenderWindow window(sf::VideoMode(windowWidth, 
        windowHeight), windowTitle, sf::Style::Titlebar | 
        sf::Style::Close);

    // Zmienna mierząca czas pomiędzy klatkami, potrzebna
    // do obliczania deltaTime
    sf::Clock clock;

    // Inicjalizacja gry
    GameLogic::init();

    // Główna pętla gry. Działa, dopóki 
    // okno jest otwarte 
    while (window.isOpen()) {

        // Oblicza czas, jaki upłynął od 
        // ostatniego odświeżenia gry, w sekundach.
        // Metoda `clock.restart()` resetuje 
        // zegar i zwraca czas, który upłynął 
        // od ostatniego restartu
        float deltaTime = clock.restart().asSeconds();

        // Aktualizuje logikę gry
        GameLogic::update(window, deltaTime);
        
    }

    return 0;
}
