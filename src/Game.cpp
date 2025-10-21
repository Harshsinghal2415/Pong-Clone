#include "Game.h"
#include <iostream>

// Constructor
Game::Game() 
    : score1(0), score2(0), maxScore(5), currentState(GameState::MENU),
      isCountingDown(false), countdownTimer(0.0f), countdownNumber(3) {
    
    initWindow();
    initGame();
    initUI();
    loadResources();
}

// Destructor
Game::~Game() {
    // Smart pointers automatically clean up
}

// Initialize window
void Game::initWindow() {
    videoMode.width = 800;
    videoMode.height = 600;
    window.create(videoMode, "Pong Clone - SFML", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
}

// Initialize game objects
void Game::initGame() {
    // Create paddles
    paddle1 = std::make_unique<Paddle>(30.0f, 250.0f, sf::Keyboard::W, sf::Keyboard::S, 600.0f);
    paddle2 = std::make_unique<Paddle>(755.0f, 250.0f, sf::Keyboard::Up, sf::Keyboard::Down, 600.0f);
    
    // Create ball
    ball = std::make_unique<Ball>(400.0f, 300.0f, 8.0f, 300.0f, 800.0f, 600.0f);
    
    // Create menu
    menu = std::make_unique<Menu>(profileManager, "assets/font.ttf");
}

// Initialize UI
void Game::initUI() {
    if (!font.loadFromFile("assets/font.ttf")) {
        std::cerr << "Failed to load font for UI" << std::endl;
    }
    
    // Score text for player 1
    scoreText1.setFont(font);
    scoreText1.setCharacterSize(40);
    scoreText1.setFillColor(sf::Color::White);
    scoreText1.setPosition(300, 20);
    
    // Score text for player 2
    scoreText2.setFont(font);
    scoreText2.setCharacterSize(40);
    scoreText2.setFillColor(sf::Color::White);
    scoreText2.setPosition(460, 20);
    
    // Game over text
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Yellow);
    
    // Countdown text
    countdownText.setFont(font);
    countdownText.setCharacterSize(120);
    countdownText.setFillColor(sf::Color::Yellow);
    
    // Instruction text
    instructionText.setFont(font);
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setString("Press ESC to return to menu");
    instructionText.setPosition(240, 550);
}

// Load resources (sounds, etc.)
bool Game::loadResources() {
    // Load ball hit sound
    if (!ball->loadSounds("assets/hit.wav")) {
        std::cerr << "Warning: Failed to load hit.wav" << std::endl;
    }
    
    // Load score sound
    if (!scoreBuffer.loadFromFile("assets/score.wav")) {
        std::cerr << "Warning: Failed to load score.wav" << std::endl;
    } else {
        scoreSound.setBuffer(scoreBuffer);
        scoreSound.setVolume(70.0f);
    }
    
    return true;
}

// Main game loop
void Game::run() {
    while (window.isOpen()) {
        pollEvents();
        update();
        render();
    }
}

// Poll events
void Game::pollEvents() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        // Handle escape key
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (currentState == GameState::PLAYING || currentState == GameState::GAME_OVER) {
                setState(GameState::MENU);
                menu->reset();
                score1 = 0;
                score2 = 0;
            } else if (currentState == GameState::MENU) {
                window.close();
            }
        }
        
        // Menu input
        if (currentState == GameState::MENU) {
            menu->handleInput(event);
            
            // Check if ready to start playing
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (menu->isReadyToPlay()) {
                    player1Name = menu->getPlayer1Name();
                    player2Name = menu->getPlayer2Name();
                    score1 = 0;
                    score2 = 0;
                    resetRound();
                    setState(GameState::PLAYING);
                }
            }
        }
        
        // Game over input
        if (currentState == GameState::GAME_OVER) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    setState(GameState::MENU);
                    menu->reset();
                    score1 = 0;
                    score2 = 0;
                }
            }
        }
    }
}

// Update game state
void Game::update() {
    float deltaTime = deltaClock.restart().asSeconds();
    
    if (currentState == GameState::PLAYING) {
        // Handle countdown
        if (isCountingDown) {
            countdownTimer -= deltaTime;
            
            if (countdownTimer <= 0.0f) {
                countdownNumber--;
                if (countdownNumber > 0) {
                    countdownTimer = 1.0f;
                } else {
                    isCountingDown = false;
                }
            }
            
            // Update paddles even during countdown
            paddle1->update(deltaTime);
            paddle2->update(deltaTime);
            
            return; // Don't update ball during countdown
        }
        
        // Update paddles
        paddle1->update(deltaTime);
        paddle2->update(deltaTime);
        
        // Update ball
        ball->update(deltaTime);
        
        // Check paddle collisions
        ball->checkPaddleCollision(*paddle1);
        ball->checkPaddleCollision(*paddle2);
        
        // Check scoring
        int scoreResult = ball->checkScore();
        if (scoreResult != 0) {
            if (scoreResult == 1) {
                score1++;
                std::cout << player1Name << " scores! " << score1 << " - " << score2 << std::endl;
            } else if (scoreResult == 2) {
                score2++;
                std::cout << player2Name << " scores! " << score1 << " - " << score2 << std::endl;
            }
            
            // Play score sound
            if (scoreSound.getStatus() != sf::Sound::Playing) {
                scoreSound.play();
            }
            
            // Check for game over
            checkGameOver();
            
            if (currentState == GameState::PLAYING) {
                resetRound();
            }
        }
        
        // Update score display
        scoreText1.setString(std::to_string(score1));
        scoreText2.setString(std::to_string(score2));
    }
    
    if (currentState == GameState::MENU) {
        menu->update();
    }
}

// Render
void Game::render() {
    window.clear(sf::Color::Black);
    
    if (currentState == GameState::MENU) {
        menu->render(window);
    }
    else if (currentState == GameState::PLAYING) {
        // Draw center line
        for (int i = 0; i < 600; i += 20) {
            sf::RectangleShape line(sf::Vector2f(2, 10));
            line.setPosition(399, i);
            line.setFillColor(sf::Color(100, 100, 100));
            window.draw(line);
        }
        
        // Draw game objects
        paddle1->render(window);
        paddle2->render(window);
        ball->render(window);
        
        // Draw scores
        window.draw(scoreText1);
        window.draw(scoreText2);
        
        // Draw player names
        sf::Text p1NameText, p2NameText;
        p1NameText.setFont(font);
        p1NameText.setString(player1Name);
        p1NameText.setCharacterSize(20);
        p1NameText.setFillColor(sf::Color(150, 150, 150));
        p1NameText.setPosition(50, 30);
        window.draw(p1NameText);
        
        p2NameText.setFont(font);
        p2NameText.setString(player2Name);
        p2NameText.setCharacterSize(20);
        p2NameText.setFillColor(sf::Color(150, 150, 150));
        p2NameText.setPosition(650, 30);
        window.draw(p2NameText);
        
        // Draw countdown if active
        if (isCountingDown && countdownNumber > 0) {
            countdownText.setString(std::to_string(countdownNumber));
            sf::FloatRect textBounds = countdownText.getGlobalBounds();
            countdownText.setPosition((800 - textBounds.width) / 2, 200);
            window.draw(countdownText);
        }
        
        // Draw instruction
        window.draw(instructionText);
    }
    else if (currentState == GameState::GAME_OVER) {
        // Draw final scores and game objects
        for (int i = 0; i < 600; i += 20) {
            sf::RectangleShape line(sf::Vector2f(2, 10));
            line.setPosition(399, i);
            line.setFillColor(sf::Color(100, 100, 100));
            window.draw(line);
        }
        
        paddle1->render(window);
        paddle2->render(window);
        ball->render(window);
        window.draw(scoreText1);
        window.draw(scoreText2);
        
        // Draw game over message
        window.draw(gameOverText);
        
        // Draw restart instruction
        sf::Text restartText;
        restartText.setFont(font);
        restartText.setString("Press SPACE to return to menu or ESC to quit");
        restartText.setCharacterSize(20);
        restartText.setFillColor(sf::Color::White);
        restartText.setPosition(180, 400);
        window.draw(restartText);
    }
    
    window.display();
}

// Reset round (ball position)
void Game::resetRound() {
    ball->reset();
    
    // Start countdown
    isCountingDown = true;
    countdownTimer = 1.0f;
    countdownNumber = 3;
}

// Check for game over
void Game::checkGameOver() {
    if (score1 >= maxScore || score2 >= maxScore) {
        setState(GameState::GAME_OVER);
        handleGameOver();
    }
}

// Handle game over
void Game::handleGameOver() {
    std::string winner;
    
    if (score1 > score2) {
        winner = player1Name;
        gameOverText.setString(player1Name + " Wins!");
        profileManager.updateStats(player1Name, true);
        profileManager.updateStats(player2Name, false);
    } else {
        winner = player2Name;
        gameOverText.setString(player2Name + " Wins!");
        profileManager.updateStats(player2Name, true);
        profileManager.updateStats(player1Name, false);
    }
    
    // Center the game over text
    sf::FloatRect textBounds = gameOverText.getGlobalBounds();
    gameOverText.setPosition((800 - textBounds.width) / 2, 250);
    
    std::cout << "\n===== GAME OVER =====" << std::endl;
    std::cout << "Winner: " << winner << std::endl;
    std::cout << "Final Score: " << score1 << " - " << score2 << std::endl;
    std::cout << "===================\n" << std::endl;
}

// Set game state
void Game::setState(GameState newState) {
    currentState = newState;
}

// Check if game is running
bool Game::isRunning() const {
    return window.isOpen();
}
