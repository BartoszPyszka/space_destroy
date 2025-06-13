
# 🚀 Space Destroy

## 👨‍🚀 Autorzy
Projekt zespołowy wykonany przez:

- **Bartosz Pyszka**
- **Maciej Podhajny**

## 🎮 Opis gry
**Space Destroy** to dynamiczna gra zręcznościowa 2D typu top-down. Gracz wciela się w pilota statku kosmicznego przemierzającego niebezpieczną strefę asteroid po zniszczeniu stacji kosmicznej. Celem jest przetrwanie jak najdłużej, niszczenie asteroid oraz zdobywanie punktów.

### 🪐 Elementy gry:
- **Gracz**: Steruje statkiem kosmicznym
- **Przeciwnicy**: Asteroidy (różne rozmiary, różna wartość punktowa)
- **Bonusy**: Pojawiają się losowo po zniszczeniu asteroid, zapewniając dodatkowe punkty lub efekty
- **Sceneria**: Kosmos w widoku z góry

### 🎮 Sterowanie:
- **Ruch:**
  - `W`: napęd rakietowy (do przodu)
  - `S`: silniki manewrowe przednie (do tyłu, wolniej)
  - `A`/`D`: obrót statku w lewo/prawo
- **Strzał:**
  - `Spacja`: wystrzał pocisku z dzioba statku

### 💥 Kolizje:
- **Statek - asteroida**: przegrana rozgrywka
- **Pocisk - asteroida**: zniszczenie obu, przyznanie punktów

## ⚙️ Funkcjonalności

| Funkcjonalność | Odpowiedzialny |
|----------------|----------------|
| Sterowanie statkiem (prędkość i kierunek) | Bartosz Pyszka |
| Losowe generowanie asteroid i ich ruch | Bartosz Pyszka |
| Strzelanie pociskami | Bartosz Pyszka |
| Płynne poruszanie się obiektów | Bartosz Pyszka |
| Kolizje pocisków z asteroidami | B. Pyszka & M. Podhajny |
| Kolizje statku z asteroidami | B. Pyszka & M. Podhajny |
| Licznik punktów i wyświetlanie wyniku | B. Pyszka & M. Podhajny |
| Obsługa końca gry i restart | B. Pyszka & M. Podhajny |
| Zapis danych gracza (imię, czas, punkty) przy zakończeniu sesji | B. Pyszka & M. Podhajny |
| Zapis wyniku końcowego (jeśli lepszy niż poprzedni) | B. Pyszka & M. Podhajny |
| Animacje wybuchów, tekstury obiektów | Maciej Podhajny |
| Efekty dźwiękowe (strzały, wybuchy) | Maciej Podhajny |
| Zapisywanie/wczytywanie stanu gry | Maciej Podhajny |
| Losowe pojawianie się bonusów | Maciej Podhajny |

## 📝 Commity

Poniżej znajduje się lista istotnych commitów dokumentujących rozwój gry:

| Data       | Autor              | Opis commita                                                                 |
|------------|-------------------|------------------------------------------------------------------------------|
| XXX | Bartosz Pyszka     | XXX                 |
| XXX | Bartosz Pyszka     | XXX                                      |
| XXX | Bartosz Pyszka     | XXX                               |
| XXX | Bartosz Pyszka     | XXX                                              |
| XXX | B. Pyszka & M. Podhajny | XXX               |
| XXX | Maciej Podhajny    | XXX                             |
| XXX | Maciej Podhajny    | XXX                   |
| XXX | B. Pyszka & M. Podhajny | XXX                        |
| XXX | Maciej Podhajny    | XXX                        |
| XXX | Bartosz Pyszka     | XXX                      |
| XXX | Maciej Podhajny    | XXX                 |

## 📍 Kamienie milowe 🗿

| Wersja    | Data       | Opis                                                                 |
|-----------|------------|----------------------------------------------------------------------|
| v0.1      | 2025-05-31 | utworzono główne okno aplikacji, obsługę zdarzeń użytkownika, mechanizm odmierzania czasu (deltaTime) oraz podstawowy system renderowania obiektów na ekranie.         |
| v0.2.2    | 2025-05-31 | Ruch statku i obracanie                                              |
| v0.4      | 2025-06-01 | Dodanie strzelania i podstawowej walki                              |
| v0.5.1    | 2025-06-01 | Obsługa kolizji, podstawowa interakcja obiektów                     |
| v0.7.1    | 2025-06-03  | W pełni działająca rozgrywka z punktacją i zakończeniem gry         |
| v0.8      | 2025-06-03 | UI startowe, zapis/wczytywanie stanu gry                            |
| v0.10.3   | 2025-06-03  | Restart gry i obsługa rekordów                                      |
| v0.11     | 2025-06-04 | Stabilizacja wersji do prezentacji/testów końcowych                 |
| v0.14.1     | 2025-06-08 | Stabilizacja wersji do prezentacji/testów końcowych                 |
| v0.15     | 2025-06-08 | Stabilizacja wersji do prezentacji/testów końcowych                 |
| v1.0.1     | 2025-06-12 | Stabilizacja wersji do prezentacji/testów końcowych                 |

> Kamienie milowe oznaczają stabilne, grywalne etapy rozwoju — wersje, które można testować i oceniać.

## 🖥️ Makiety UI

1. **Ekran startowy** – ekran powitalny z opcją wpisania imienia i rozpoczęcia gry.
2. **Ekran główny** – prezentuje wynik, liczbę żyć oraz przyciski restartu/wyjścia.
3. **Ekran gry** – widok gry z aktywnym statkiem, asteroidami, punktami i interakcją.

## 🛠️ Technologie
- C++
- Biblioteka do grafiki (SFML)
- Pliki tekstowe do zapisu wyników i stanów

## 💾 Instalacja i uruchomienie
1. Sklonuj repozytorium:
```bash
git clone https://github.com/BartoszPyszka/space-destroy.git
cd space-destroy
```
2. Uruchom grę:
przeciagnij cmakelista.txt do qt i skompiluj 

## 📁 Struktura katalogów
```
space-destroy/
│
├── assets/            # Tekstury, dźwięki
├── saves/             # Zapisy gier i wyników
├── include/             # Pliki nagłówkowe
├── src/             # Kody i deklaracje obiektów
├── main.cpp            # Główny plik gry
└── README.md          # Dokumentacja projektu
```

## 📌 Uwagi końcowe
Projekt jest rozwijany zespołowo — przypisane funkcje mogą ulec zmianie w toku pracy. Cały zespół współpracuje przy testach i optymalizacji gry. 
