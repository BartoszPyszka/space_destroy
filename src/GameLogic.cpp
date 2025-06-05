#include "GameLogic.h"

// Inicjalizacja statycznych pól klasy GameLogic
std::vector<std::unique_ptr<GameObject>> GameLogic::objects{};      // Kontener aktywnych obiektów gry
std::list<size_t> GameLogic::toRemoveIndices{};                     // Lista indeksów obiektów do usuniêcia
std::list<std::unique_ptr<GameObject>> GameLogic::toAddList{};      // Lista nowych obiektów do dodania
float GameLogic::asteroidSpawnTime{};                               // Czas do pojawienia siê kolejnej asteroidy
sf::Texture GameLogic::playerTexture;                               // tekstura

sf::Font GameLogic::font{};                                         // Czcionka u¿ywana w interfejsie

size_t GameLogic::score{};                                          // Aktualny wynik gracza
size_t GameLogic::highScore{};                                      // Najlepszy osi¹gniêty wynik

GameLogic::State GameLogic::state{};                                // Aktualny stan gry

std::string GameLogic::playerName{};                                // Nazwa gracza

// Elementy interfejsu u¿ytkownika
sf::Text GameLogic::playerNameText{};
sf::Text GameLogic::exitText{};
sf::Text GameLogic::highScoreText{};
sf::Text GameLogic::gameOverText{};
sf::Text GameLogic::continueText{};
sf::Text GameLogic::scoreText{};
sf::Text GameLogic::titleText{};
sf::Text GameLogic::menuText{};
sf::Text GameLogic::playText{};

void GameLogic::init()
{
    // Wczytanie najlepszego wyniku z pliku (jeœli istnieje)
    std::ifstream file("score.dat", std::ios::binary | std::ios::in);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
        file.close();
    }

    // £adowanie czcionki
    if (!font.loadFromFile("font.ttf")) {
        printf("Error loading font\n");
    }

    // Konfiguracja tekstu wprowadzania nazwy gracza
    playerNameText.setFont(font);
    playerNameText.setPosition(sf::Vector2f(300, 400));
    playerNameText.setCharacterSize(40);
    playerNameText.setFillColor(sf::Color::Blue);
    playerNameText.setString("Enter your name: ");

    // Konfiguracja wyœwietlacza wyniku
    scoreText.setFont(font);
    scoreText.setPosition(sf::Vector2f(10, 10));
    scoreText.setCharacterSize(40);

    // Konfiguracja napisu "Game Over"
    gameOverText.setFont(font);
    gameOverText.setPosition(sf::Vector2f(250, 200));
    gameOverText.setCharacterSize(80);
    gameOverText.setString("Game Over!");

    // Konfiguracja instrukcji kontynuacji
    continueText.setFont(font);
    continueText.setPosition(sf::Vector2f(180, 500));
    continueText.setCharacterSize(30);
    continueText.setString("Press B to continue...");

    // Konfiguracja tytu³u gry
    titleText.setFont(font);
    titleText.setPosition(sf::Vector2f(250, 200));
    titleText.setCharacterSize(80);
    titleText.setString("Space Destroy!!!");

    // Konfiguracja przycisku rozpoczêcia gry
    playText.setFont(font);
    playText.setPosition(sf::Vector2f(400, 500));
    playText.setCharacterSize(20);
    playText.setString("Press P to play");

    // Konfiguracja przycisku wyjœcia
    exitText.setFont(font);
    exitText.setPosition(sf::Vector2f(10, 10));
    exitText.setCharacterSize(30);
    exitText.setString("Press Esc to exit");

    // Konfiguracja przycisku powrotu do menu
    menuText.setFont(font);
    menuText.setPosition(sf::Vector2f(140, 540));
    menuText.setCharacterSize(30);
    menuText.setString("Press E to return to menu");

    // Konfiguracja wyœwietlacza najlepszego wyniku
    highScoreText.setFont(font);
    highScoreText.setPosition(sf::Vector2f(10, 850));
    highScoreText.setCharacterSize(30);
    highScoreText.setString("High Score: " + std::to_string(highScore));

    // Ustawienie pocz¹tkowego stanu gry
    state = ENTERING_NAME;
    if (!playerTexture.loadFromFile("D:\\Projekt\\SFML\\SFML\\Move.png")) {
        printf("Error loading player texture\n");
    }
}

void GameLogic::begin()
{
    // Rozpoczêcie nowej gry
    state = PLAYING;
    // £adowanie txt i animacji 
    objects.push_back(std::make_unique<Player>(playerTexture));

    // Ustawienie czasu do pojawienia siê pierwszej asteroidy
    asteroidSpawnTime = ASTEROID_SPAWN_TIME;

    // Reset wyniku
    score = 0;
}

void GameLogic::update(sf::RenderWindow& window, float deltaTime)
{
    // Obs³uga zdarzeñ systemowych
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Obs³uga wprowadzania nazwy gracza
        if (state == ENTERING_NAME) {
            if (event.type == sf::Event::TextEntered) {
                // Obs³uga backspace
                if (event.text.unicode == '\b' && !playerName.empty()) {
                    playerName.pop_back();
                }
                // Dodawanie tylko drukowalnych znaków ASCII
                else if (event.text.unicode >= 32 && event.text.unicode < 128) {
                    playerName += static_cast<char>(event.text.unicode);
                }
                playerNameText.setString("Enter your name: " + playerName);
            }
            else if (event.type == sf::Event::KeyPressed) {
                // Zakoñczenie wprowadzania nazwy po naciœniêciu Enter
                if (event.key.code == sf::Keyboard::Enter && !playerName.empty()) {
                    state = MENU;
                }
            }
        }
    }

    // Czyszczenie okna
    window.clear();

    // Renderowanie odpowiedniego ekranu w zale¿noœci od stanu gry
    if (state == ENTERING_NAME) {
        // Ekran wprowadzania nazwy
        window.draw(playerNameText);
    }
    else if (state == MENU) {
        // Ekran menu g³ównego
        window.draw(titleText);
        window.draw(playText);
        window.draw(highScoreText);
        window.draw(exitText);

        // Obs³uga przycisków menu
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            begin(); // Rozpocznij grê
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close(); // WyjdŸ z gry
        }
    }
    else if (state == PLAYING) {
        // Stan aktywnej rozgrywki

        // Czyszczenie list obiektów do dodania/usuniêcia
        toAddList.clear();
        toRemoveIndices.clear();

        // Aktualizacja czasu pojawienia siê asteroidy
        asteroidSpawnTime -= deltaTime;

        // Aktualizacja i renderowanie wszystkich obiektów
        for (auto& obj : objects) {
            obj->update(deltaTime);
            obj->render(window);
        }

        // Usuwanie obiektów oznaczonych do usuniêcia
        toRemoveIndices.sort(std::greater<size_t>()); // Sortowanie malej¹ce
        for (size_t index : toRemoveIndices) {
            if (index < objects.size()) {
                objects.erase(objects.begin() + index);
            }
        }

        // Dodawanie nowych obiektów
        for (auto& obj : toAddList) {
            objects.push_back(std::move(obj));
        }

        // Generowanie nowych asteroid
        if (asteroidSpawnTime <= 0.0f) {
            objects.push_back(std::make_unique<Asteroid>());
            asteroidSpawnTime = ASTEROID_SPAWN_TIME;
        }

        // Aktualizacja i wyœwietlanie wyniku
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
    }
    else if (state == GAME_OVER) {
        // Ekran koñca gry

        // Czyszczenie obiektów gry
        objects.clear();

        // Renderowanie elementów interfejsu
        window.draw(gameOverText);
        window.draw(continueText);
        window.draw(menuText);
        window.draw(scoreText);

        // Obs³uga przycisków po zakoñczeniu gry
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            ScoreSaver::SaveToFile("scores.txt", playerName, score); // Zapis sesji rozgrywki do pliku
            begin(); // Rozpocznij now¹ grê
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            ScoreSaver::SaveToFile("scores.txt", playerName, score); // Zapis sesji rozgrywki do pliku
            state = MENU; // Powrót do menu
        }
    }

    // Wyœwietlenie wszystkiego na ekranie
    window.display();
}

void GameLogic::gameOver()
{
    // Sprawdzenie i zapis nowego rekordu
    if (score > highScore) {
        highScore = score;
        std::ofstream file("score.dat", std::ios::binary | std::ios::out);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(&highScore), sizeof(size_t));
            file.close();
        }
        else {
            printf("Error saving high score to file\n");
        }
        highScoreText.setString("High Score: " + std::to_string(highScore));
    }

    // Zmiana stanu gry na GAME_OVER
    state = GAME_OVER;
}