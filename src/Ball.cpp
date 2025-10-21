#include "Ball.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Constructor
Ball::Ball(float startX, float startY, float rad, float speed, float winWidth, float winHeight)
    : radius(rad), baseSpeed(speed), currentSpeed(speed), windowWidth(winWidth), windowHeight(winHeight) {
    
    // Initialize random seed
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    
    // Create ball shape
    shape.setRadius(radius);
    shape.setPosition(startX - radius, startY - radius);
    shape.setFillColor(sf::Color::White);
    
    // Set initial velocity (random direction)
    reset();
}

// Update ball position
void Ball::update(float deltaTime) {
    shape.move(velocity * deltaTime);
    
    // Check wall collisions (top and bottom)
    if (checkWallCollision()) {
        velocity.y = -velocity.y;
        if (hitSound.getStatus() != sf::Sound::Playing) {
            hitSound.play();
        }
    }
}

// Check collision with paddle
bool Ball::checkPaddleCollision(const Paddle& paddle) {
    sf::FloatRect ballBounds = shape.getGlobalBounds();
    sf::FloatRect paddleBounds = paddle.getBounds();
    
    if (ballBounds.intersects(paddleBounds)) {
        // Calculate relative position where ball hit the paddle
        float paddleCenter = paddleBounds.top + paddleBounds.height / 2.0f;
        float ballCenter = ballBounds.top + ballBounds.height / 2.0f;
        float relativeIntersection = (ballCenter - paddleCenter) / (paddleBounds.height / 2.0f);
        
        // Reverse horizontal direction
        velocity.x = -velocity.x;
        
        // Adjust vertical velocity based on where it hit the paddle
        velocity.y = relativeIntersection * currentSpeed * 0.75f;
        
        // Increase speed slightly with each hit (max 1.5x base speed)
        currentSpeed = std::min(currentSpeed * 1.05f, baseSpeed * 1.5f);
        
        // Update velocity magnitude
        float magnitude = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        velocity.x = (velocity.x / magnitude) * currentSpeed;
        velocity.y = (velocity.y / magnitude) * currentSpeed;
        
        // Move ball slightly away from paddle to prevent multiple collisions
        if (velocity.x > 0) {
            shape.setPosition(paddleBounds.left + paddleBounds.width + 1, shape.getPosition().y);
        } else {
            shape.setPosition(paddleBounds.left - ballBounds.width - 1, shape.getPosition().y);
        }
        
        // Play hit sound
        if (hitSound.getStatus() != sf::Sound::Playing) {
            hitSound.play();
        }
        
        return true;
    }
    
    return false;
}

// Check collision with top/bottom walls
bool Ball::checkWallCollision() {
    sf::FloatRect bounds = shape.getGlobalBounds();
    
    if (bounds.top <= 0) {
        shape.setPosition(shape.getPosition().x, 0);
        return true;
    }
    
    if (bounds.top + bounds.height >= windowHeight) {
        shape.setPosition(shape.getPosition().x, windowHeight - bounds.height);
        return true;
    }
    
    return false;
}

// Check if ball went out of bounds (scoring)
int Ball::checkScore() {
    sf::Vector2f pos = shape.getPosition();
    
    // Player 1 scores (ball went past right edge)
    if (pos.x > windowWidth) {
        return 1;
    }
    
    // Player 2 scores (ball went past left edge)
    if (pos.x + radius * 2 < 0) {
        return 2;
    }
    
    return 0;
}

// Reset ball to center with random direction
void Ball::reset() {
    // Reset position to center
    shape.setPosition(windowWidth / 2.0f - radius, windowHeight / 2.0f - radius);
    
    // Reset speed
    currentSpeed = baseSpeed;
    
    // Random direction (left or right)
    float directionX = (std::rand() % 2 == 0) ? 1.0f : -1.0f;
    
    // Random angle between -45 and 45 degrees
    float angle = ((std::rand() % 90) - 45) * 3.14159f / 180.0f;
    
    velocity.x = directionX * currentSpeed * std::cos(angle);
    velocity.y = currentSpeed * std::sin(angle);
}

// Render ball
void Ball::render(sf::RenderWindow& window) {
    window.draw(shape);
}

// Load sound effects
bool Ball::loadSounds(const std::string& hitSoundPath) {
    if (!hitBuffer.loadFromFile(hitSoundPath)) {
        return false;
    }
    hitSound.setBuffer(hitBuffer);
    hitSound.setVolume(50.0f);
    return true;
}

// Get position
sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

// Get radius
float Ball::getRadius() const {
    return radius;
}
