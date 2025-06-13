
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
| Wersja    | Opis                                                                 |
|-----------|----------------------------------------------------------------------|
| v0.1      | Utworzono główne okno aplikacji, obsługę zdarzeń użytkownika, mechanizm odmierzania czasu (deltaTime) oraz podstawowy system renderowania obiektów na ekranie. |
| v0.2.2    | Dodano klasę Player: gracz może się obracać, poruszać do przodu i do tyłu. Zmiany w main(): uproszczono pętlę gry i dodano komentarze dla lepszej czytelności. Rysowanie gracza: Player jest teraz wyświetlany na ekranie. |
| v0.4      | Dodano funkcję strzelania                             |
| v0.5.1    | Dodano klasę Asteroid z ruchem, obrotem i losową generacją.                    |
| v0.7.1    | Dodano system kolizji pocisk-asteroida, gracz-asteroida oraz systemu punktacji         |
| v0.8      | Dodano elementu UI: ekranu głównego, ekranu po przegranej. Dodano system ponownej gry                           |
| v0.9      | Dodano zapis rekordu do pliku i wyświetlanie go w grze                                      |
| v0.11     | Dodano możliwość wprowadzenia nazwy gracza oraz zapis danych z konkretnej sesji, zastosowano unique_ptr, dodano obszerne komentarze                 |
| v0.12.1b  | Dodano elementu UI: audio, animacji gracza, efektów dźwiękowych i tła. Zmiany w Player                |
| v0.13a    | Dodano tekstury asteroid. Dopracowano strzelanie. Zmiana modelu gracza                |
| v0.14.1   | Dodano system bonusów                 |
| v0.15     | Dodano animację wybuchu asteroid                 |
| v1.0.1    | Finalna wersja gry                 |

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
