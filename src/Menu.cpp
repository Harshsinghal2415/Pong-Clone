#include "Menu.h"
#include <iostream>

// Constructor
Menu::Menu(ProfileManager& profManager, const std::string& fontPath)
    : profileManager(profManager), currentState(MenuState::MAIN_MENU), 
      selectedIndex(0), inputActive(false) {
    
    loadFont(fontPath);
    updateMenuItems();
}

// Load font
bool Menu::loadFont(const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font: " << fontPath << std::endl;
        return false;
    }
    return true;
}

// Update menu items based on current state
void Menu::updateMenuItems() {
    menuItems.clear();
    
    switch (currentState) {
        case MenuState::MAIN_MENU:
            menuItems.push_back("Start Game");
            menuItems.push_back("Exit");
            break;
            
        case MenuState::SELECT_PLAYER1:
        case MenuState::SELECT_PLAYER2:
            menuItems = profileManager.getProfileNames();
            menuItems.push_back("Create New Profile");
            break;
            
        case MenuState::CREATE_PROFILE:
            // No menu items for text input
            break;
            
        case MenuState::READY_TO_PLAY:
            menuItems.push_back("Press SPACE to Start");
            menuItems.push_back("Back to Menu");
            break;
    }
    
    // Reset selection if out of bounds
    if (selectedIndex >= static_cast<int>(menuItems.size())) {
        selectedIndex = 0;
    }
}

// Handle input
void Menu::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        
        // Text input mode for creating profile
        if (currentState == MenuState::CREATE_PROFILE) {
            if (event.key.code == sf::Keyboard::Enter && !textInput.empty()) {
                // Create profile
                if (profileManager.createProfile(textInput)) {
                    textInput.clear();
                    // Return to appropriate player selection
                    if (player1Name.empty()) {
                        currentState = MenuState::SELECT_PLAYER1;
                    } else {
                        currentState = MenuState::SELECT_PLAYER2;
                    }
                    updateMenuItems();
                }
            } else if (event.key.code == sf::Keyboard::Escape) {
                // Cancel profile creation
                textInput.clear();
                if (player1Name.empty()) {
                    currentState = MenuState::SELECT_PLAYER1;
                } else {
                    currentState = MenuState::SELECT_PLAYER2;
                }
                updateMenuItems();
            }
        }
        // Normal menu navigation
        else {
            if (event.key.code == sf::Keyboard::Up) {
                selectedIndex--;
                if (selectedIndex < 0) {
                    selectedIndex = menuItems.size() - 1;
                }
            } else if (event.key.code == sf::Keyboard::Down) {
                selectedIndex++;
                if (selectedIndex >= static_cast<int>(menuItems.size())) {
                    selectedIndex = 0;
                }
            } else if (event.key.code == sf::Keyboard::Enter) {
                // Handle selection
                switch (currentState) {
                    case MenuState::MAIN_MENU:
                        if (selectedIndex == 0) {
                            currentState = MenuState::SELECT_PLAYER1;
                            selectedIndex = 0;
                            updateMenuItems();
                        }
                        break;
                        
                    case MenuState::SELECT_PLAYER1:
                    case MenuState::SELECT_PLAYER2:
                        if (selectedIndex == static_cast<int>(menuItems.size()) - 1) {
                            // Create new profile
                            currentState = MenuState::CREATE_PROFILE;
                            textInput.clear();
                        } else if (selectedIndex < static_cast<int>(menuItems.size())) {
                            // Select existing profile
                            std::string selectedName = menuItems[selectedIndex];
                            
                            if (currentState == MenuState::SELECT_PLAYER1) {
                                player1Name = selectedName;
                                currentState = MenuState::SELECT_PLAYER2;
                                selectedIndex = 0;
                                updateMenuItems();
                            } else {
                                // Prevent selecting same player
                                if (selectedName != player1Name) {
                                    player2Name = selectedName;
                                    currentState = MenuState::READY_TO_PLAY;
                                    selectedIndex = 0;
                                    updateMenuItems();
                                }
                            }
                        }
                        break;
                        
                    case MenuState::READY_TO_PLAY:
                        if (selectedIndex == 1) {
                            reset();
                        }
                        break;
                        
                    default:
                        break;
                }
            } else if (event.key.code == sf::Keyboard::Escape) {
                // Go back
                if (currentState == MenuState::SELECT_PLAYER1) {
                    currentState = MenuState::MAIN_MENU;
                    updateMenuItems();
                } else if (currentState == MenuState::SELECT_PLAYER2) {
                    player1Name.clear();
                    currentState = MenuState::SELECT_PLAYER1;
                    updateMenuItems();
                } else if (currentState == MenuState::READY_TO_PLAY) {
                    reset();
                }
            }
        }
    }
    
    // Handle text input for profile creation
    if (currentState == MenuState::CREATE_PROFILE && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && !textInput.empty()) { // Backspace
            textInput.pop_back();
        } else if (event.text.unicode >= 32 && event.text.unicode < 128) {
            if (textInput.length() < 20) { // Limit username length
                textInput += static_cast<char>(event.text.unicode);
            }
        }
    }
}

// Update
void Menu::update() {
    // Menu is event-driven, no continuous updates needed
}

// Render main menu
void Menu::renderMainMenu(sf::RenderWindow& window) {
    // Title
    titleText.setFont(font);
    titleText.setString("PONG GAME");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(250, 100);
    window.draw(titleText);
    
    // Menu items
    float yOffset = 300;
    for (size_t i = 0; i < menuItems.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(menuItems[i]);
        text.setCharacterSize(30);
        text.setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(300, yOffset + i * 60);
        window.draw(text);
    }
}

// Render profile selection
void Menu::renderProfileSelection(sf::RenderWindow& window, const std::string& playerLabel) {
    // Title
    titleText.setFont(font);
    titleText.setString("Select " + playerLabel);
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(200, 80);
    window.draw(titleText);
    
    // Instructions
    instructionText.setFont(font);
    instructionText.setString("Use Arrow Keys to Navigate, Enter to Select, ESC to Go Back");
    instructionText.setCharacterSize(18);
    instructionText.setFillColor(sf::Color(150, 150, 150));
    instructionText.setPosition(100, 540);
    window.draw(instructionText);
    
    // Profile list
    float yOffset = 200;
    for (size_t i = 0; i < menuItems.size(); i++) {
        sf::Text text;
        text.setFont(font);
        
        // Show stats for existing profiles
        if (i < menuItems.size() - 1) {
            UserProfile* profile = profileManager.getProfile(menuItems[i]);
            if (profile) {
                std::string statsStr = menuItems[i] + " (W:" + std::to_string(profile->wins) + 
                                      " L:" + std::to_string(profile->losses) + ")";
                text.setString(statsStr);
            } else {
                text.setString(menuItems[i]);
            }
        } else {
            text.setString(menuItems[i]);
        }
        
        text.setCharacterSize(25);
        text.setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(200, yOffset + i * 45);
        
        // Disable if same as player 1 (for player 2 selection)
        if (currentState == MenuState::SELECT_PLAYER2 && menuItems[i] == player1Name) {
            text.setFillColor(sf::Color(100, 100, 100));
            text.setString(text.getString() + " (Already Selected)");
        }
        
        window.draw(text);
    }
}

// Render create profile screen
void Menu::renderCreateProfile(sf::RenderWindow& window) {
    // Title
    titleText.setFont(font);
    titleText.setString("Create New Profile");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(150, 150);
    window.draw(titleText);
    
    // Instructions
    instructionText.setFont(font);
    instructionText.setString("Enter Username (Press Enter to Confirm, ESC to Cancel)");
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color(200, 200, 200));
    instructionText.setPosition(150, 250);
    window.draw(instructionText);
    
    // Input box
    sf::RectangleShape inputBox(sf::Vector2f(400, 50));
    inputBox.setPosition(200, 320);
    inputBox.setFillColor(sf::Color(50, 50, 50));
    inputBox.setOutlineColor(sf::Color::White);
    inputBox.setOutlineThickness(2);
    window.draw(inputBox);
    
    // Input text
    inputText.setFont(font);
    inputText.setString(textInput + "_");
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(210, 330);
    window.draw(inputText);
}

// Render ready screen
void Menu::renderReadyScreen(sf::RenderWindow& window) {
    // Title
    titleText.setFont(font);
    titleText.setString("Ready to Play!");
    titleText.setCharacterSize(50);
    titleText.setFillColor(sf::Color::Green);
    titleText.setPosition(220, 100);
    window.draw(titleText);
    
    // Player info
    sf::Text p1Text, p2Text;
    p1Text.setFont(font);
    p1Text.setString("Player 1 (W/S): " + player1Name);
    p1Text.setCharacterSize(30);
    p1Text.setFillColor(sf::Color::White);
    p1Text.setPosition(200, 250);
    window.draw(p1Text);
    
    p2Text.setFont(font);
    p2Text.setString("Player 2 (Up/Down): " + player2Name);
    p2Text.setCharacterSize(30);
    p2Text.setFillColor(sf::Color::White);
    p2Text.setPosition(200, 320);
    window.draw(p2Text);
    
    // Options
    float yOffset = 420;
    for (size_t i = 0; i < menuItems.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(menuItems[i]);
        text.setCharacterSize(25);
        text.setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(250, yOffset + i * 50);
        window.draw(text);
    }
}

// Render
void Menu::render(sf::RenderWindow& window) {
    switch (currentState) {
        case MenuState::MAIN_MENU:
            renderMainMenu(window);
            break;
            
        case MenuState::SELECT_PLAYER1:
            renderProfileSelection(window, "Player 1");
            break;
            
        case MenuState::SELECT_PLAYER2:
            renderProfileSelection(window, "Player 2");
            break;
            
        case MenuState::CREATE_PROFILE:
            renderCreateProfile(window);
            break;
            
        case MenuState::READY_TO_PLAY:
            renderReadyScreen(window);
            break;
    }
}

// Check if ready to play
bool Menu::isReadyToPlay() const {
    return currentState == MenuState::READY_TO_PLAY && selectedIndex == 0;
}

// Reset menu
void Menu::reset() {
    currentState = MenuState::MAIN_MENU;
    player1Name.clear();
    player2Name.clear();
    selectedIndex = 0;
    textInput.clear();
    updateMenuItems();
}
