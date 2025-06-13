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

// Biblioteki zewnętrzne (SFML)
#include <SFML/Graphics.hpp> 

// Własne nagłówki
#include "GameLogic.h"

// Inicjalizacja statycznych pól klasy GameLogic
std::vector<std::unique_ptr<GameObject>> GameLogic::objects{};      // Kontener aktywnych obiektów gry
std::list<size_t> GameLogic::toRemoveIndices{};                     // Lista indeksów obiektów do usunięcia
std::list<std::unique_ptr<GameObject>> GameLogic::toAddList{};      // Lista nowych obiektów do dodania
float GameLogic::asteroidSpawnTime{};                               
sf::Texture GameLogic::playerTexture;                               

sf::Font GameLogic::font{};                                         

size_t GameLogic::score{};                                          
size_t GameLogic::highScore{};                                      

GameLogic::State GameLogic::state{};                               

std::string GameLogic::playerName{};                                

// Elementy interfejsu użytkownika
sf::Text GameLogic::playerNameText{};
sf::Text GameLogic::exitText{};
sf::Text GameLogic::highScoreText{};
sf::Text GameLogic::gameOverText{};
sf::Text GameLogic::continueText{};
sf::Text GameLogic::scoreText{};
sf::Text GameLogic::titleText{};
sf::Text GameLogic::menuText{};
sf::Text GameLogic::playText{};
sf::Texture GameLogic::backgroundTexture;
sf::Sprite GameLogic::backgroundSprite;

void GameLogic::init()
{
    // Wczytanie najlepszego wyniku z pliku (jeżli istnieje)
    std::ifstream file("score.dat", std::ios::binary | std::ios::in);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&highScore), sizeof(size_t));
        file.close();
    }
    
    // Załadowanie czcionki
    if (!font.loadFromFile("Assets\\font.ttf")) {
        printf("Error loading font\n");
    }

     // Załadowanie tekstur
    if (!backgroundTexture.loadFromFile("Assets\\graphics\\BG.png")) {
        printf("Error loading background texture\n");
    }
    backgroundSprite.setTexture(backgroundTexture);
    if (!Asteroid::loadTextures()) {
        printf("B³¹d ³adowania tekstur asteroid!");
    }

    // Konfiguracje tekstów na ekranie 
    playerNameText.setFont(font);
    playerNameText.setPosition(sf::Vector2f(300, 400));
    playerNameText.setCharacterSize(40);
    playerNameText.setFillColor(sf::Color::Blue);
    playerNameText.setString("Enter your name: ");

    scoreText.setFont(font);
    scoreText.setPosition(sf::Vector2f(10, 10));
    scoreText.setCharacterSize(40);

    gameOverText.setFont(font);
    gameOverText.setPosition(sf::Vector2f(250, 200));
    gameOverText.setCharacterSize(80);
    gameOverText.setString("Game Over!");

    continueText.setFont(font);
    continueText.setPosition(sf::Vector2f(180, 500));
    continueText.setCharacterSize(30);
    continueText.setString("Press B to continue...");

    titleText.setFont(font);
    titleText.setPosition(sf::Vector2f(250, 200));
    titleText.setCharacterSize(80);
    titleText.setString("Space Destroy!!!");

    playText.setFont(font);
    playText.setPosition(sf::Vector2f(400, 500));
    playText.setCharacterSize(20);
    playText.setString("Press P to play");

    exitText.setFont(font);
    exitText.setPosition(sf::Vector2f(10, 10));
    exitText.setCharacterSize(30);
    exitText.setString("Press Esc to exit");

    menuText.setFont(font);
    menuText.setPosition(sf::Vector2f(140, 540));
    menuText.setCharacterSize(30);
    menuText.setString("Press E to return to menu");

    highScoreText.setFont(font);
    highScoreText.setPosition(sf::Vector2f(10, 850));
    highScoreText.setCharacterSize(30);
    highScoreText.setString("High Score: " + std::to_string(highScore));

    // Ustawienie początkowego stanu gry
    state = ENTERING_NAME;

     // Załadowanie tekstury ruchu
    if (!playerTexture.loadFromFile("Assets\\graphics\\Move.png")) {
        printf("Error loading player texture\n");
    }
}

void GameLogic::begin()
{
    state = PLAYING;
    
    // Ładowanie tekstur i animacji gracza
    objects.push_back(std::make_unique<Player>(playerTexture));

    asteroidSpawnTime = ASTEROID_SPAWN_TIME;

    score = 0;
}

// Aktualizacja stanu gry
void GameLogic::update(sf::RenderWindow& window, float deltaTime)
{
    // Obsługa zdarzeń systemowych
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Obsługa wprowadzania nazwy gracza
        if (state == ENTERING_NAME) {
            if (event.type == sf::Event::TextEntered) {
                // Obsługa backspace
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
                // Zakończenie wprowadzania nazwy po naciśnięciu Enter
                if (event.key.code == sf::Keyboard::Enter && !playerName.empty()) {
                    state = MENU;
                }
            }
        }
    }

    // Czyszczenie okna
    window.clear();
    window.draw(backgroundSprite);
    
    // Renderowanie odpowiedniego ekranu w zale¿noœci od stanu gry
    if (state == ENTERING_NAME) {
        window.draw(playerNameText);
    }
    else if (state == MENU) {
        window.draw(titleText);
        window.draw(playText);
        window.draw(highScoreText);
        window.draw(exitText);

        // Obsługa przycisków 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            begin(); // Rozpocznij grę
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close(); // Wyjdź z gry
        }
    }
    else if (state == PLAYING) {
        // Czyszczenie list obiektów do dodania/usunięcia
        toAddList.clear();
        toRemoveIndices.clear();

        // Aktualizacja czasu pojawienia się asteroidy
        asteroidSpawnTime -= deltaTime;

        // Aktualizacja i renderowanie wszystkich obiektów
        for (auto& obj : objects) {
            obj->update(deltaTime);
            obj->render(window);
        }

        // Usuwanie obiektów oznaczonych do usunięcia
        toRemoveIndices.sort(std::greater<size_t>()); // Sortowanie malejące
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

        // Aktualizacja i wyświetlanie wyniku
        scoreText.setString("Score: " + std::to_string((score)));
        window.draw(scoreText);
    }
    else if (state == GAME_OVER) {
        // Czyszczenie obiektów gry
        objects.clear();

        // Renderowanie elementów interfejsu
        window.draw(gameOverText);
        window.draw(continueText);
        window.draw(menuText);
        window.draw(scoreText);

        // Obsługa przycisków po zakończeniu gry
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            ScoreSaver::SaveToFile("scores.txt", playerName, score); // Zapis sesji rozgrywki do pliku
            begin(); // Zagraj ponownie
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            ScoreSaver::SaveToFile("scores.txt", playerName, score); // Zapis sesji rozgrywki do pliku
            state = MENU; // Powrót do menu
        }
    }

    // Wyświetlenie wszystkiego na ekranie
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

    state = GAME_OVER;
}
