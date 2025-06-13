#pragma once

// Biblioteki zewnętrzne 
#include <SFML/Graphics.hpp>

// Przestrzeń nazw dla funkcji fizyki kolizji 
namespace physics {
    // Sprawdza kolizję pocisk - asteroida
    bool intersects(const sf::Vector2f& point, const sf::VertexArray& polygon);

    // Sprawdza kolizję gracz - asteroida metodą SAT
    bool intersects(const sf::VertexArray& poly1, const sf::VertexArray& poly2);

    // Zwraca przekształconą tablicę wierzchołków 
    sf::VertexArray getTransformed(const sf::VertexArray& polygon, const sf::Transform& transform);
}
