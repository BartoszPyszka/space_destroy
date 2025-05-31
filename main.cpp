#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Ustawienia pocz¹tkowe okna gry
    constexpr unsigned int windowWidth = 1200;
    constexpr unsigned int windowHeight = 900;
    const std::string windowTitle = "Space Destroy";

    // Tworzymy okno renderuj¹ce z okreœlonymi wymiarami i tytu³em
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Titlebar | sf::Style::Close);

    // Zegar do mierzenia czasu miêdzy klatkami (delta time)
    sf::Clock deltaClock;

    // Flaga okreœlaj¹ca, czy gra nadal dzia³a
    bool isRunning = true;

    // G³ówna pêtla gry
    while (isRunning)
    {
        // Oblicz czas, który up³yn¹³ od ostatniej klatki
        float deltaTime = deltaClock.restart().asSeconds();

        // Obs³uga zdarzeñ (np. zamkniêcie okna)
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // U¿ytkownik klikn¹³ zamkniêcie — koñczymy pêtlê i zamykamy okno
                isRunning = false;
                window.close();
            }
        }

        // Czyszczenie ekranu — wype³niamy go kolorem czarnym
        window.clear(sf::Color::Black);

        // Tutaj w przysz³oœci bêdzie rysowanie obiektów gry (gracz, wrogowie, pociski itd.)

        // Wyœwietlenie zawartoœci bufora na ekranie
        window.display();
    }

    // Zakoñczenie programu
    return 0;
}
