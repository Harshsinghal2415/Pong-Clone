#include "Game.h"
#include <iostream>

int main() {
    std::cout << "==================================" << std::endl;
    std::cout << "    PONG CLONE - SFML C++17      " << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "\nStarting game...\n" << std::endl;
    
    try {
        // Create and run the game
        Game game;
        game.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\nThanks for playing!" << std::endl;
    return 0;
}
