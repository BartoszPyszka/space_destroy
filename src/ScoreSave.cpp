#include "ScoreSave.h"

/**
 * Generuje string z aktualn� dat� i czasem.
 * Format: RRRR-MM-DD GG:MM:SS
 */
std::string ScoreSaver::GetCurrentDateTime() {
    std::time_t now = std::time(nullptr); // Pobierz aktualny czas
    std::tm localTime; // Struktura przechowuj�ca czas lokalny

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
    // Otw�rz plik w trybie dopisywania
    std::ofstream file(filename, std::ios::app);

    if (file.is_open()) {
        // Zapisz dane w czytelnym formacie
        file << "Player: " << playerName << "\n";
        file << "Score: " << score << "\n";
        file << "Date: " << GetCurrentDateTime() << "\n";
        file << "----------------\n"; // Separator mi�dzy wpisami
        file.close();
    }
    else {
        // Rzu� wyj�tek je�li plik nie m�g� zosta� otwarty
        throw std::runtime_error("Cannot open scores file: " + filename);
    }
}