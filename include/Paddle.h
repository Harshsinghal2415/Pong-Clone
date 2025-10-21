#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape shape;
    float speed;
    sf::Keyboard::Key upKey;
    sf::Keyboard::Key downKey;
    float windowHeight;

public:
    // Constructor
    Paddle(float startX, float startY, sf::Keyboard::Key up, sf::Keyboard::Key down, float winHeight);

    // Movement methods
    void moveUp(float deltaTime);
    void moveDown(float deltaTime);
    void update(float deltaTime);

    // Rendering
    void render(sf::RenderWindow& window);

    // Getters
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

    // Reset position
    void reset(float x, float y);
};

#endif // PADDLE_H
