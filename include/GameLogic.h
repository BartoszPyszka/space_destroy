#pragma once

// Standardowe biblioteki C++ 
#include <vector>      
#include <list>      
#include <algorithm>   
#include <fstream> 

// Własne nagłówki
#include "GameObject.h" 
#include "Asteroid.h"   
#include "Player.h"     
#include "ScoreSave.h"  

// Główna klasa zarządzająca logiką gry
class GameLogic
{
public:
    // Metody zarządzające stanem gry
    static void init();    // Inicjalizacja zasobów gry
    static void begin();   // Rozpoczęcie nowej gry
    static void update(sf::RenderWindow& window, float deltaTime); // Aktualizacja stanu gry

    static void gameOver(); 

    // Kontenery obiektów gry 
    static std::vector<std::unique_ptr<GameObject>> objects;   // Aktywne obiekty gry
    static std::list<size_t> toRemoveIndices;                  // Indeksy obiektów do usunięcia
    static std::list<std::unique_ptr<GameObject>> toAddList;   // Obiekty do dodania

    static sf::Texture playerTexture;

    static size_t score;     

private:
    // Zmienne kontrolujące rozgrywkę 
    static float asteroidSpawnTime; 
    static size_t highScore;        
    static std::string playerName;  

    // Elementy interfejsu użytkownika
    static sf::Text highScoreText; 
    static sf::Font font;   
    static sf::Text gameOverText;    
    static sf::Text continueText;     
    static sf::Text scoreText;        
    static sf::Text menuText;         
    static sf::Text titleText;        
    static sf::Text playText;         
    static sf::Text exitText;         
    static sf::Text playerNameText;   
    static sf::Texture backgroundTexture;
    static sf::Sprite backgroundSprite;

    // Stany gry 
    enum State {
        MENU,          
        PLAYING,       
        GAME_OVER,     
        ENTERING_NAME  
    };

    static State state; 
};
