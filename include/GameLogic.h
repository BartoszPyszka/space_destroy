#pragma once

// Nag��wki niezb�dne do dzia�ania klasy GameLogic
#include <vector>      // Kontener dla obiekt�w gry
#include <list>        // Listy do zarz�dzania obiektami
#include "GameObject.h" // Bazowa klasa obiekt�w
#include "Asteroid.h"   // Obiekty asteroid
#include "Player.h"     // Klasa gracza
#include <algorithm>    // Algorytmy do przetwarzania kontener�w
#include <fstream>      // Operacje na plikach (zapisywanie wynik�w)
#include "ScoreSave.h"  // Plik s�u��cy do zapisu sesji rozgrywki

// G��wna klasa zarz�dzaj�ca logik� gry
class GameLogic
{
public:
    // ----- Metody zarz�dzaj�ce stanem gry -----
    static void init();    // Inicjalizacja zasob�w gry
    static void begin();   // Rozpocz�cie nowej gry
    static void update(sf::RenderWindow& window, float deltaTime); // Aktualizacja stanu gry

    static void gameOver(); // Zako�czenie gry

    // ----- Kontenery obiekt�w gry -----
    static std::vector<std::unique_ptr<GameObject>> objects;   // Aktywne obiekty gry
    static std::list<size_t> toRemoveIndices;                  // Indeksy obiekt�w do usuni�cia
    static std::list<std::unique_ptr<GameObject>> toAddList;   // Obiekty do dodania

    // ----- Stan gry -----
    static size_t score;     // Aktualny wynik gracza

private:
    // ----- Zmienne kontroluj�ce rozgrywk� -----
    static float asteroidSpawnTime; // Czas do pojawienia si� kolejnej asteroidy
    static size_t highScore;        // Najlepszy wynik
    static std::string playerName;  // Nazwa gracza (dla tabeli wynik�w)

    // ----- Zasoby graficzne -----
    static sf::Font font; // Czcionka u�ywana w grze

    // ----- Elementy interfejsu u�ytkownika -----
    static sf::Text highScoreText;    // Tekst z najlepszym wynikiem
    static sf::Text gameOverText;     // Tekst ko�ca gry
    static sf::Text continueText;     // Instrukcja kontynuacji
    static sf::Text scoreText;        // Wy�wietlacz aktualnego wyniku
    static sf::Text menuText;         // Tekst menu
    static sf::Text titleText;        // Tytu� gry
    static sf::Text playText;         // Przycisk rozpocz�cia gry
    static sf::Text exitText;         // Przycisk wyj�cia
    static sf::Text playerNameText;   // Pole na nazw� gracza

    // ----- Stany gry -----
    enum State {
        MENU,          // Ekran g��wny
        PLAYING,       // Rozgrywka
        GAME_OVER,     // Koniec gry
        ENTERING_NAME  // Wprowadzanie nazwy gracza
    };

    static State state; // Aktualny stan gry
};