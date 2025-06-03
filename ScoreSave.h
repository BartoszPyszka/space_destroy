#pragma once

// Nag��wki niezb�dne do dzia�ania zapisu
#include <string>   //Obs�uga ci�g�w znak�w
#include <ctime>    // Do obs�ugi czasu systemowego
#include <iomanip>  // Do formatowania wyj�cia
#include <sstream>  // Do konwersji string�w
#include <fstream>  // Do operacji na plikach

/**
 * Klasa odpowiedzialna za zapisywanie i przechowywanie wynik�w gry.
 * Implementuje funkcjonalno�� zapisu do pliku z timestampem.
 */
class ScoreSaver {
public:
    /**
     * Zapisuje wynik gracza do pliku tekstowego.
     * @param filename �cie�ka do pliku z wynikami
     * @param playerName Nazwa gracza do zapisania
     * @param score Wynik do zapisania
     * @throws std::runtime_error Je�li nie uda si� otworzy� pliku
     */
    static void SaveToFile(const std::string& filename,
        const std::string& playerName,
        int score);

    /**
     * Generuje aktualn� dat� i czas w formacie YYYY-MM-DD HH:MM:SS.
     * @return Sformatowany string z dat� i czasem
     */
    static std::string GetCurrentDateTime();
};