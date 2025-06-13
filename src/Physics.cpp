// Standardowe biblioteki C++ 
#include <limits>                
#include <vector>                
#include <list>                  
#include <memory>                
#include <fstream>               
#include <string>                
#include <cstdio>               
#include <functional>            
#include <algorithm>  
#include <cmath>

// Biblioteki zewnętrzne (SFML)
#include <SFML/Graphics.hpp> 

// Własne nagłówki
#include "Physics.h"
    
// Kolizja pocisk - asteroida
bool physics::intersects(const sf::Vector2f& point, const sf::VertexArray& polygon)
{
    // Zmienna przechowująca liczbę punktów przecięcia promienia z bokami wielokąta.
    size_t n = polygon.getVertexCount() - 1;
    size_t intersectionCount = 0;

    // Określa punkt końca promienia, który biegnie w prawo od punktu.
    sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), point.y);

    // Iteruje przez wszystkie boki wielokąta.
    for (size_t i = 0; i < n; i++) {
        // Pobiera dwie sąsiednie pozycje wierzchołków.
        sf::Vector2f p1 = (polygon[i].position);
        sf::Vector2f p2 = (polygon[(i + 1) % n].position);

        // Sprawdza, czy bok przecina promień przechodzący przez punkt.
        if ((p1.y < point.y && p2.y >= point.y) ||
            (p2.y < point.y && p1.y >= point.y)) {
            // Oblicza współrzędną X przecięcia.
            float t = (point.y - p1.y) / (p2.y - p1.y);
            float intersectX = p1.x + t * (p2.x - p1.x);

            // Jeśli punkt przecięcia znajduje się na lewo od punktu, zwiększa licznik.
            if (intersectX <= point.x && intersectX <= rayEnd.x) {
                intersectionCount++;
            }
        }
    }

    // Jeśli liczba przecięć jest nieparzysta, punkt jest wewnątrz wielokąta.
    return intersectionCount % 2 == 1;
}
// Kolizja gracz - asteroida, przy użyciu algorytmu SAT 
bool physics::intersects(const sf::VertexArray& poly1, const sf::VertexArray& poly2) {
    // Lambda do sprawdzania osi separacji
    auto checkSeparatingAxis = [](const sf::VertexArray& polyA, const sf::VertexArray& polyB) -> bool {
        size_t countA = polyA.getVertexCount();
        size_t countB = polyB.getVertexCount();
        const float epsilon = 0.01f; // Tolerancja dla separacji

        for (size_t i = 0; i < countA; i++) {
            // Obliczanie krawędzi i normali
            sf::Vector2f edge = polyA[(i + 1) % countA].position - polyA[i].position;
            sf::Vector2f normal(-edge.y, edge.x);

            // Normalizacja wektor normalny
            float length = sqrt(normal.x * normal.x + normal.y * normal.y);
            if (length != 0) {
                normal /= length;
            }

            // Znajdywanie projekcji wielokątów na normalę
            float minA = std::numeric_limits<float>::max();
            float maxA = std::numeric_limits<float>::min();
            for (size_t j = 0; j < countA; j++) {
                float projection = polyA[j].position.x * normal.x + polyA[j].position.y * normal.y;
                minA = std::min(minA, projection);
                maxA = std::max(maxA, projection);
            }

            float minB = std::numeric_limits<float>::max();
            float maxB = std::numeric_limits<float>::min();
            for (size_t j = 0; j < countB; j++) {
                float projection = polyB[j].position.x * normal.x + polyB[j].position.y * normal.y;
                minB = std::min(minB, projection);
                maxB = std::max(maxB, projection);
            }

            // Sprawdzanie separacji z tolerancją
            if (maxA < minB - epsilon || maxB < minA - epsilon) {
                return false;  // Separacja - brak kolizji
            }
        }

        return true;  // Brak osi separacji
        };

    // Sprawdź osie separacji obu wielokątów
    return checkSeparatingAxis(poly1, poly2) && checkSeparatingAxis(poly2, poly1);
}

sf::VertexArray physics::getTransformed(const sf::VertexArray& polygon,
    const sf::Transform& transform) {

    // Tworzenie kopii tablicy wierzchołków (polygon).
    sf::VertexArray transformed = polygon;

    // Przemieszczanie każdego wierzchołka zgodnie z transformacją.
    for (size_t i = 0; i < transformed.getVertexCount(); i++) {
        transformed[i].position = transform.transformPoint(transformed[i].position);
    }

    // Zwrot przekształconej tablicy wierzchołków.
    return transformed;
}
