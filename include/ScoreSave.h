#pragma once

// Standardowe biblioteki C++ 
#include <string>   
#include <ctime>    // Do obsługi czasu systemowego
#include <iomanip>  // Do formatowania wyjścia
#include <sstream>  // Do konwersji stringów
#include <fstream>  

// Klasa odpowiedzialna za zapisywanie i przechowywanie wyników gry.
class ScoreSaver {
public:
    // Zapisuje wynik gracza do pliku tekstowego
    static void SaveToFile(const std::string& filename,
        const std::string& playerName,
        int score);

    // Generuje aktualną datę i czas w formacie YYYY-MM-DD HH:MM:SS.
    static std::string GetCurrentDateTime();
};
