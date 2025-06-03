#include "GameObject.h"

// Inicjalizuje konstruktor klasy GameObject, zawieraj¹cy
// pozycjê i k¹t obiektu na wartoœci przekazane jako argumenty 
GameObject::GameObject(sf::Vector2f pos, float ang)
	: position(pos), angle(ang) {
}
