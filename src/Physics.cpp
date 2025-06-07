#include "Physics.h"
#include <SFML/Graphics.hpp>     // Dla sf::Vector2f, sf::VertexArray, sf::Transform
#include <limits>                // Dla std::numeric_limits
#include <cmath>                 // Dla sqrt()
#include <algorithm>            // Dla std::min, std::max
// Kolizja pocisk - asteroida
bool physics::intersects(const sf::Vector2f& point, const sf::VertexArray& polygon)
{
    // Zmienna przechowuj¹ca liczbê punktów przeciêcia promienia z bokami wielok¹ta.
    size_t n = polygon.getVertexCount() - 1;
    size_t intersectionCount = 0;

    // Okreœla punkt koñca promienia, który biegnie w prawo od punktu.
    sf::Vector2f rayEnd = sf::Vector2f(std::numeric_limits<float>::max(), point.y);

    // Iteruje przez wszystkie boki wielok¹ta.
    for (size_t i = 0; i < n; i++) {
        // Pobiera dwie s¹siednie pozycje wierzcho³ków.
        sf::Vector2f p1 = (polygon[i].position);
        sf::Vector2f p2 = (polygon[(i + 1) % n].position);

        // Sprawdza, czy bok przecina promieñ przechodz¹cy przez punkt.
        if ((p1.y < point.y && p2.y >= point.y) ||
            (p2.y < point.y && p1.y >= point.y)) {
            // Oblicza wspó³rzêdn¹ X przeciêcia.
            float t = (point.y - p1.y) / (p2.y - p1.y);
            float intersectX = p1.x + t * (p2.x - p1.x);

            // Jeœli punkt przeciêcia znajduje siê na lewo od punktu, zwiêksza licznik.
            if (intersectX <= point.x && intersectX <= rayEnd.x) {
                intersectionCount++;
            }
        }
    }

    // Jeœli liczba przeciêæ jest nieparzysta, punkt jest wewn¹trz wielok¹ta.
    return intersectionCount % 2 == 1;
}
// Kolizja gracz - asteroida, przy u¿yciu algorytmu SAT 
bool physics::intersects(const sf::VertexArray& poly1, const sf::VertexArray& poly2) {
    // Lambda do sprawdzania osi separacji
    auto checkSeparatingAxis = [](const sf::VertexArray& polyA, const sf::VertexArray& polyB) -> bool {
        size_t countA = polyA.getVertexCount();
        size_t countB = polyB.getVertexCount();
        const float epsilon = 0.01f; // Tolerancja dla separacji

        for (size_t i = 0; i < countA; i++) {
            // Obliczanie krawêdzi i normali
            sf::Vector2f edge = polyA[(i + 1) % countA].position - polyA[i].position;
            sf::Vector2f normal(-edge.y, edge.x);

            // Normalizacja wektor normalny
            float length = sqrt(normal.x * normal.x + normal.y * normal.y);
            if (length != 0) {
                normal /= length;
            }

            // Znajdywanie projekcji wielok¹tów na normalê
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

            // Sprawdzanie separacji z tolerancj¹
            if (maxA < minB - epsilon || maxB < minA - epsilon) {
                return false;  // Separacja - brak kolizji
            }
        }

        return true;  // Brak osi separacji
        };

    // SprawdŸ osie separacji obu wielok¹tów
    return checkSeparatingAxis(poly1, poly2) && checkSeparatingAxis(poly2, poly1);
}

sf::VertexArray physics::getTransformed(const sf::VertexArray& polygon,
    const sf::Transform& transform) {

    // Tworzenie kopii tablicy wierzcho³ków (polygon).
    sf::VertexArray transformed = polygon;

    // Przemieszczanie ka¿dego wierzcho³ka zgodnie z transformacj¹.
    for (size_t i = 0; i < transformed.getVertexCount(); i++) {
        transformed[i].position = transform.transformPoint(transformed[i].position);
    }

    // Zwrot przekszta³conej tablicy wierzcho³ków.
    return transformed;
}
