#include "GameObject.h"

// Inicjalizuje konstruktor klasy GameObject, zawieraj�cy
// pozycj� i k�t obiektu na warto�ci przekazane jako argumenty 
GameObject::GameObject(sf::Vector2f pos, float ang)
	: position(pos), angle(ang) {
}
