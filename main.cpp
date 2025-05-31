#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Ustawienia pocz�tkowe okna gry
    constexpr unsigned int windowWidth = 1200;
    constexpr unsigned int windowHeight = 900;
    const std::string windowTitle = "Space Destroy";

    // Tworzymy okno renderuj�ce z okre�lonymi wymiarami i tytu�em
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Titlebar | sf::Style::Close);

    // Zegar do mierzenia czasu mi�dzy klatkami (delta time)
    sf::Clock deltaClock;

    // Flaga okre�laj�ca, czy gra nadal dzia�a
    bool isRunning = true;

    // G��wna p�tla gry
    while (isRunning)
    {
        // Oblicz czas, kt�ry up�yn�� od ostatniej klatki
        float deltaTime = deltaClock.restart().asSeconds();

        // Obs�uga zdarze� (np. zamkni�cie okna)
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // U�ytkownik klikn�� zamkni�cie � ko�czymy p�tl� i zamykamy okno
                isRunning = false;
                window.close();
            }
        }

        // Czyszczenie ekranu � wype�niamy go kolorem czarnym
        window.clear(sf::Color::Black);

        // Tutaj w przysz�o�ci b�dzie rysowanie obiekt�w gry (gracz, wrogowie, pociski itd.)

        // Wy�wietlenie zawarto�ci bufora na ekranie
        window.display();
    }

    // Zako�czenie programu
    return 0;
}
