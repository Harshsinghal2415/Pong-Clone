#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Paddle.h"

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float radius;
    float baseSpeed;
    float currentSpeed;
    float windowWidth;
    float windowHeight;
    
    // Sound effects
    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;

public:
    // Constructor
    Ball(float startX, float startY, float rad, float speed, float winWidth, float winHeight);

    // Update and physics
    void update(float deltaTime);
    bool checkPaddleCollision(const Paddle& paddle);
    bool checkWallCollision();
    
    // Check if ball went out of bounds (scoring)
    int checkScore(); // Returns 1 if player 1 scores, 2 if player 2 scores, 0 otherwise

    // Reset ball to center
    void reset();

    // Rendering
    void render(sf::RenderWindow& window);

    // Load sounds
    bool loadSounds(const std::string& hitSoundPath);

    // Getters
    sf::Vector2f getPosition() const;
    float getRadius() const;
};

#endif // BALL_H
