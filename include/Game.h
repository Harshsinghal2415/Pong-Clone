#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Paddle.h"
#include "Ball.h"
#include "ProfileManager.h"
#include "Menu.h"

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER,
    EXIT
};

class Game {
private:
    // Window
    sf::RenderWindow window;
    sf::VideoMode videoMode;
    sf::Event event;
    
    // Game state
    GameState currentState;
    
    // Game objects
    std::unique_ptr<Paddle> paddle1;
    std::unique_ptr<Paddle> paddle2;
    std::unique_ptr<Ball> ball;
    
    // Managers
    ProfileManager profileManager;
    std::unique_ptr<Menu> menu;
    
    // Scores
    int score1;
    int score2;
    int maxScore;
    
    // UI elements
    sf::Font font;
    sf::Text scoreText1;
    sf::Text scoreText2;
    sf::Text gameOverText;
    sf::Text instructionText;
    sf::Text countdownText;
    
    // Sound
    sf::SoundBuffer scoreBuffer;
    sf::Sound scoreSound;
    
    // Players
    std::string player1Name;
    std::string player2Name;
    
    // Delta time
    sf::Clock deltaClock;
    
    // Countdown
    bool isCountingDown;
    float countdownTimer;
    int countdownNumber;
    
    // Private methods
    void initWindow();
    void initGame();
    void initUI();
    bool loadResources();
    void resetRound();
    void checkGameOver();
    void handleGameOver();

public:
    // Constructor and destructor
    Game();
    virtual ~Game();

    // Main game loop methods
    void run();
    void pollEvents();
    void update();
    void render();

    // State management
    void setState(GameState newState);
    
    // Check if game is running
    bool isRunning() const;
};

#endif // GAME_H
