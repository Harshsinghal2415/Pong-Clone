#include "Paddle.h"

// Constructor
Paddle::Paddle(float startX, float startY, sf::Keyboard::Key up, sf::Keyboard::Key down, float winHeight)
    : speed(400.0f), upKey(up), downKey(down), windowHeight(winHeight) {
    
    // Create paddle shape (width: 15, height: 80)
    shape.setSize(sf::Vector2f(15.0f, 80.0f));
    shape.setPosition(startX, startY);
    shape.setFillColor(sf::Color::White);
}

// Move paddle up
void Paddle::moveUp(float deltaTime) {
    float newY = shape.getPosition().y - speed * deltaTime;
    if (newY >= 0) {
        shape.setPosition(shape.getPosition().x, newY);
    } else {
        shape.setPosition(shape.getPosition().x, 0);
    }
}

// Move paddle down
void Paddle::moveDown(float deltaTime) {
    float newY = shape.getPosition().y + speed * deltaTime;
    float maxY = windowHeight - shape.getSize().y;
    if (newY <= maxY) {
        shape.setPosition(shape.getPosition().x, newY);
    } else {
        shape.setPosition(shape.getPosition().x, maxY);
    }
}

// Update paddle based on input
void Paddle::update(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(upKey)) {
        moveUp(deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(downKey)) {
        moveDown(deltaTime);
    }
}

// Render paddle
void Paddle::render(sf::RenderWindow& window) {
    window.draw(shape);
}

// Get bounding box for collision detection
sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

// Get position
sf::Vector2f Paddle::getPosition() const {
    return shape.getPosition();
}

// Get size
sf::Vector2f Paddle::getSize() const {
    return shape.getSize();
}

// Reset paddle position
void Paddle::reset(float x, float y) {
    shape.setPosition(x, y);
}
