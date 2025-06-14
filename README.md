
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
- **Statek - asteroida**: przegrana rozgrywka (algorytm SAT)
- **Pocisk - asteroida**: zniszczenie obu, przyznanie punktów

# Algorytm SAT (Separating Axis Theorem) w fizyce kolizji

## Co to jest SAT?

SAT (Separating Axis Theorem) to twierdzenie geometryczne, które mówi:

> Dwa wypukłe kształty **nie kolidują**, jeśli istnieje oś (linia), na której ich rzuty (projekcje) **nie nakładają się**.

Jeśli takiej osi nie ma, to znaczy, że kształty **kolidują**.

---

## Jak działa SAT w praktyce?

1. **Wypukłe kształty:**  
   SAT działa dla kształtów wypukłych (np. prostokąty, wielokąty wypukłe). Dla każdego kształtu znajdujemy krawędzie i ich normalne (prostopadłe) wektory.

2. **Wybór osi testowych:**  
   - Oś testowa to najczęściej normalna (prostopadła) do każdej krawędzi obu kształtów.  
   - Dla dwóch kształtów testujemy osie normalne do krawędzi pierwszego i drugiego kształtu.

3. **Rzutowanie kształtów na oś:**  
   - Dla każdej osi "rzucamy" (projektujemy) wszystkie wierzchołki kształtu na tę oś.  
   - Otrzymujemy zakres (przedział) wartości na tej osi, który opisuje położenie całego kształtu.

4. **Sprawdzenie nakładania się przedziałów:**  
   - Jeśli przedziały projekcji dwóch kształtów na osi **nie nakładają się**, to znaczy, że na tej osi jest *separująca oś*.  
   - W takim przypadku **nie ma kolizji** i możemy zakończyć testy.

5. **Brak osi separującej:**  
   - Jeśli na żadnej z testowanych osi nie da się znaleźć osi separującej (czyli na wszystkich osiach przedziały się nakładają), to kształty **kolidują**.

---

## Podsumowanie:

| Krok                 | Opis                                                        |
|----------------------|-------------------------------------------------------------|
| 1. Znajdź osie       | Osie normalne do krawędzi obu kształtów                     |
| 2. Rzutuj kształty   | Projekcja wierzchołków obu kształtów na osie                |
| 3. Sprawdź przedziały| Czy przedziały się nakładają?                               |
| 4. Decyzja           | Jeśli brak nakładania na jakiejkolwiek osi → brak kolizji; jeśli nie → kolizja |

---

## Zastosowanie w fizyce kolizji

- SAT jest używany do szybkiego wykrywania kolizji między dwoma obiektami 2D (lub 3D dla rozszerzonych wersji) o wypukłych kształtach.  
- Pozwala określić, czy obiekty się stykają, co jest podstawą do dalszych obliczeń: sił kontaktu, odbić, tarcia itp.  
- Jest bardzo efektywny i często używany w silnikach fizycznych do kolizji wielokątów.

---

## 📝 Commity i Funkcjonalności

Poniżej znajduje się lista commitów zawierające funkcjonalności zawarte w koncepcie:

| Wersje commitów          | Autor                      |  Funkcjonalność                                                                |
|--------------------------|----------------------------|--------------------------------------------------------------------------------|
| v0.2.1                   | Bartosz Pyszka             | Sterowanie statkiem (prędkość i kierunek)                                      |
| v0.5; v0.5.1             | Bartosz Pyszka             | Losowe generowanie asteroid i ich ruch                                         |
| v0.4                     | Bartosz Pyszka             | Strzelanie pociskami                                                           |
| v0.7                     | B. Pyszka & M. Podhajny    | Kolizje pocisków z asteroidami                                                 |
| v0.7                     | B. Pyszka & M. Podhajny    | Kolizje statku z asteroidami`*`                                                  |
| v0.7                     | B. Pyszka & M. Podhajny    | System punktacji                                                               |
| v0.8                     | B. Pyszka & M. Podhajny    | Obsługa końca gry i restart                                                    |
| v0.2.1;  v0.5                | Bartosz Pyszka             | Płynne poruszanie się obiektów                                                 |
| v0.11                    | B. Pyszka & M. Podhajny`**`  | Zapis danych gracza (imię, czas, punkty) przy rozpoczęciu sesji`**`              |
| v0.9                     | B. Pyszka & M. Podhajny`***` | Zapis danych najlepszego gracza (imię, punkty) przy zakończeniu sesji          |
| v0.11.1; v0.12; v0.12.1.b; v0.13; v0.13a; v0.15                      | Maciej Podhajny            | Animacje wybuchów, tekstury obiektów   |
| v0.12.1                     | Maciej Podhajny            | Efekty dźwiękowe (strzały, wybuchy)                                            |
| XXX                      | Maciej Podhajny            | Zapisanie i wczytanie pozycji wszystkich obiektów`****`                          |
| v0.14                      | Maciej Podhajny            | Losowe pojawianie się bonusów                                                  |

## 📌 Uwagi 
> `*` Zmiana do konceptu - gracz ma jedno życie, nie wiele punktów zdrowia

> `**` Zmiana do konceptu - zmiana przypisania osoby (wspólnie zamiast samodzielnie Maciej Podhajny); zapis następuje po śmierci gracza

> `***` Zmiana do konceptu - zmiana przypisania osoby (wspólnie zamiast samodzielnie Bartosz Pyszka)

> `****` Tego nie udało się wykonać, zadanie nas przerosło

> Commity stworzone od 12-06 do 14-06 są drobnymi zmianami kosmetycznymi, kodu i pliku README

## 🗿 Kamienie milowe 🗿
| Wersja  commita   | Opis                                                                 |
|------------|----------------------------------------------------------------------|
| v0.1       | Utworzono główne okno aplikacji, obsługę zdarzeń użytkownika, mechanizm odmierzania czasu (deltaTime) oraz podstawowy system renderowania obiektów na ekranie. |
| v0.2.2     | Dodano klasę Player: gracz może się obracać, poruszać do przodu i do tyłu. Zmiany w main(): uproszczono pętlę gry i dodano komentarze dla lepszej czytelności. Rysowanie gracza: Player jest teraz wyświetlany na ekranie. |
| v0.4       | Dodano funkcję strzelania                             |
| v0.5.1     | Dodano klasę Asteroid z generacją losowego rucheu, obrotu i pozycji.                    |
| v0.7.1     | Dodano system kolizji pocisk-asteroida, gracz-asteroida oraz systemu punktacji         |
| v0.8       | Dodano elementy UI: ekranu głównego, ekranu po przegranej. Dodano system ponownej gry                           |
| v0.9       | Dodano zapis rekordu do pliku i wyświetlanie go w grze                                      |
| v0.11      | Dodano możliwość wprowadzenia nazwy gracza oraz zapis danych z konkretnej sesji, zastosowano unique_ptr, dodano obszerne komentarze                 |
| v0.12.1b   | Dodano elementy UI: audio, animacji gracza, efektów dźwiękowych i tła. Zmiany w Player                |
| v0.13a     | Dodano tekstury asteroid. Dopracowano strzelanie. Zmiana modelu gracza                |
| v0.14.1    | Dodano system bonusów                 |
| v0.15      | Dodano animację wybuchu asteroid                 |
| v1.0.19    | Finalna wersja gry                 |

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
