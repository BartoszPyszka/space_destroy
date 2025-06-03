#include "Asteroid.h"

Asteroid::Asteroid(sf::Vector2f direction, sf::Vector2f position)
    : GameObject(position, 0.0f), direction(direction), shape(sf::TrianglesFan, 6), life()
{

    can_damage = false;
    alive = true;
    timer = 0;

    // Kszta³t asteroidy 
    shape[0].position = { 0, 30 };
    shape[1].position = { 30, 15 };
    shape[2].position = { 30, -15 };
    shape[3].position = { 0, -30 };
    shape[4].position = { -30, -15 };
    shape[5].position = { -30, 15 };

    for (size_t i = 0; i < shape.getVertexCount(); ++i)
        shape[i].color = sf::Color::White;

    //// £adowanie dŸwiêku odbicia
    //if (!bounceBuffer.loadFromFile("assets/bounce.wav"))
    //    std::cerr << "Nie udalo sie zaladowac dzwieku odbicia!" << std::endl;
    //bounceSound.setBuffer(bounceBuffer);
}

void Asteroid::update(float deltaTime)
{
    life += deltaTime;
    position += ASTEROID_SPEED * direction * deltaTime;
    angle += ASTEROID_SPIN * deltaTime;

    // Odbicia od œcian (x i y)
    if (position.x < ASTEROID_W / 2.0f + 17.0f) {
        direction.x = abs(direction.x);
        bounceSound.play();
    }
    else if (position.x > SCREEN_WIDTH - ASTEROID_W / 2.0f - 10.0f) {
        direction.x = -abs(direction.x);
        bounceSound.play();
    }

    if (position.y < ASTEROID_H / 2.0f + 17.0f) {
        direction.y = abs(direction.y);
        bounceSound.play();
    }
    else if (position.y > SCREEN_HEIGHT - ASTEROID_H / 2.0f - 10.0f) {
        direction.y = -abs(direction.y);
        bounceSound.play();
    }
}

sf::Vector2f Asteroid::getRandomDirection()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 2.0f * M_PI);
    float angle = dist(gen);
    return { cos(angle), sin(angle) };
}

sf::Vector2f Asteroid::getRandomPosition()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xAxis(ASTEROID_W / 2.0f, SCREEN_WIDTH - ASTEROID_W / 2.0f);
    std::uniform_real_distribution<float> yAxis(ASTEROID_H / 2.0f, SCREEN_HEIGHT - ASTEROID_H / 2.0f);
    return { xAxis(gen), yAxis(gen) };
}

const sf::VertexArray& Asteroid::getVertexArray() const
{
    return shape;
}

void Asteroid::render(sf::RenderWindow& window)
{
    sf::Transform transform;
    transform.translate(position).rotate(angle);
    window.draw(shape, transform);
}

float Asteroid::getLife() {
    return life;
}

bool Asteroid::updateAsteroid(float deltaTime) {
    if (timer <= ASTEROID_DELAY) {
        timer += deltaTime;
    }

    else {
        timer = 0;
        can_damage = true;
    }

    return can_damage;
}
