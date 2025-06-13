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

// Własne nagłówki
#include "ScoreSave.h"

std::string ScoreSaver::GetCurrentDateTime() {
    std::time_t now = std::time(nullptr); // Pobierz aktualny czas
    std::tm localTime; // Struktura przechowująca czas lokalny

    // Konwertuj do czasu lokalnego (wersja bezpieczna)
    localtime_s(&localTime, &now);

    // Sformatuj czas do czytelnego stringa
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

/**
 * Zapisuje wynik do pliku w formacie:
 * Player: [name]
 * Score: [score]
 * Date: [timestamp]
 * ----------------
 */
void ScoreSaver::SaveToFile(const std::string& filename,
    const std::string& playerName,
    int score) {
    // Otwórz plik w trybie dopisywania
    std::ofstream file(filename, std::ios::app);

    if (file.is_open()) {
        // Zapisz dane w czytelnym formacie
        file << "Player: " << playerName << "\n";
        file << "Score: " << score << "\n";
        file << "Date: " << GetCurrentDateTime() << "\n";
        file << "----------------\n"; // Separator między wpisami
        file.close();
    }
    else {
        // Rzuć wyjątek jeżli plik nie mógł zostać otwarty
        throw std::runtime_error("Cannot open scores file: " + filename);
    }
}
