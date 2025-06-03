#pragma once

// Nag³ówki niezbêdne do dzia³ania zapisu
#include <string>   //Obs³uga ci¹gów znaków
#include <ctime>    // Do obs³ugi czasu systemowego
#include <iomanip>  // Do formatowania wyjœcia
#include <sstream>  // Do konwersji stringów
#include <fstream>  // Do operacji na plikach

/**
 * Klasa odpowiedzialna za zapisywanie i przechowywanie wyników gry.
 * Implementuje funkcjonalnoœæ zapisu do pliku z timestampem.
 */
class ScoreSaver {
public:
    /**
     * Zapisuje wynik gracza do pliku tekstowego.
     * @param filename Œcie¿ka do pliku z wynikami
     * @param playerName Nazwa gracza do zapisania
     * @param score Wynik do zapisania
     * @throws std::runtime_error Jeœli nie uda siê otworzyæ pliku
     */
    static void SaveToFile(const std::string& filename,
        const std::string& playerName,
        int score);

    /**
     * Generuje aktualn¹ datê i czas w formacie YYYY-MM-DD HH:MM:SS.
     * @return Sformatowany string z dat¹ i czasem
     */
    static std::string GetCurrentDateTime();
};