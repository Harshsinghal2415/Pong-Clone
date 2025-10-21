#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "ProfileManager.h"

enum class MenuState {
    MAIN_MENU,
    SELECT_PLAYER1,
    SELECT_PLAYER2,
    CREATE_PROFILE,
    READY_TO_PLAY
};

class Menu {
private:
    sf::Font font;
    MenuState currentState;
    ProfileManager& profileManager;
    
    // Selected players
    std::string player1Name;
    std::string player2Name;
    
    // Menu navigation
    int selectedIndex;
    std::vector<std::string> menuItems;
    
    // Text input for profile creation
    std::string textInput;
    bool inputActive;
    
    // UI elements
    sf::Text titleText;
    std::vector<sf::Text> menuTexts;
    sf::Text instructionText;
    sf::Text inputText;

    // Helper methods
    void updateMenuItems();
    void renderMainMenu(sf::RenderWindow& window);
    void renderProfileSelection(sf::RenderWindow& window, const std::string& playerLabel);
    void renderCreateProfile(sf::RenderWindow& window);
    void renderReadyScreen(sf::RenderWindow& window);

public:
    // Constructor
    Menu(ProfileManager& profManager, const std::string& fontPath);

    // Load resources
    bool loadFont(const std::string& fontPath);

    // Update and input handling
    void handleInput(sf::Event& event);
    void update();

    // Rendering
    void render(sf::RenderWindow& window);

    // Getters
    bool isReadyToPlay() const;
    std::string getPlayer1Name() const { return player1Name; }
    std::string getPlayer2Name() const { return player2Name; }
    
    // Reset menu
    void reset();
};

#endif // MENU_H
