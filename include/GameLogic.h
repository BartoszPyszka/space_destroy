#pragma once

// Nag³ówki niezbêdne do dzia³ania klasy GameLogic
#include <vector>      // Kontener dla obiektów gry
#include <list>        // Listy do zarz¹dzania obiektami
#include "GameObject.h" // Bazowa klasa obiektów
#include "Asteroid.h"   // Obiekty asteroid
#include "Player.h"     // Klasa gracza
#include <algorithm>    // Algorytmy do przetwarzania kontenerów
#include <fstream>      // Operacje na plikach (zapisywanie wyników)
#include "ScoreSave.h"  // Plik s³u¿¹cy do zapisu sesji rozgrywki

// G³ówna klasa zarz¹dzaj¹ca logik¹ gry
class GameLogic
{
public:
    // ----- Metody zarz¹dzaj¹ce stanem gry -----
    static void init();    // Inicjalizacja zasobów gry
    static void begin();   // Rozpoczêcie nowej gry
    static void update(sf::RenderWindow& window, float deltaTime); // Aktualizacja stanu gry

    static void gameOver(); // Zakoñczenie gry

    // ----- Kontenery obiektów gry -----
    static std::vector<std::unique_ptr<GameObject>> objects;   // Aktywne obiekty gry
    static std::list<size_t> toRemoveIndices;                  // Indeksy obiektów do usuniêcia
    static std::list<std::unique_ptr<GameObject>> toAddList;   // Obiekty do dodania

    // ----- Stan gry -----
    static size_t score;     // Aktualny wynik gracza

private:
    // ----- Zmienne kontroluj¹ce rozgrywkê -----
    static float asteroidSpawnTime; // Czas do pojawienia siê kolejnej asteroidy
    static size_t highScore;        // Najlepszy wynik
    static std::string playerName;  // Nazwa gracza (dla tabeli wyników)

    // ----- Zasoby graficzne -----
    static sf::Font font; // Czcionka u¿ywana w grze

    // ----- Elementy interfejsu u¿ytkownika -----
    static sf::Text highScoreText;    // Tekst z najlepszym wynikiem
    static sf::Text gameOverText;     // Tekst koñca gry
    static sf::Text continueText;     // Instrukcja kontynuacji
    static sf::Text scoreText;        // Wyœwietlacz aktualnego wyniku
    static sf::Text menuText;         // Tekst menu
    static sf::Text titleText;        // Tytu³ gry
    static sf::Text playText;         // Przycisk rozpoczêcia gry
    static sf::Text exitText;         // Przycisk wyjœcia
    static sf::Text playerNameText;   // Pole na nazwê gracza

    // ----- Stany gry -----
    enum State {
        MENU,          // Ekran g³ówny
        PLAYING,       // Rozgrywka
        GAME_OVER,     // Koniec gry
        ENTERING_NAME  // Wprowadzanie nazwy gracza
    };

    static State state; // Aktualny stan gry
};