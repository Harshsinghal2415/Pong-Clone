# Pong Clone Makefile
# C++17 with SFML 2.6+

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = .

# Target executable
TARGET = $(BIN_DIR)/pong

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete!"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean build files
clean:
	@echo "Cleaning build files..."
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Clean complete!"

# Run the game
run: $(TARGET)
	./$(TARGET)

# Rebuild
rebuild: clean all

# Install dependencies (Linux)
install-deps-linux:
	@echo "Installing SFML dependencies on Linux..."
	sudo apt-get update
	sudo apt-get install -y libsfml-dev

# Display help
help:
	@echo "Pong Clone - Makefile Commands"
	@echo "=============================="
	@echo "make              - Build the project"
	@echo "make run          - Build and run the game"
	@echo "make clean        - Remove build files"
	@echo "make rebuild      - Clean and rebuild"
	@echo "make install-deps-linux - Install SFML on Linux"
	@echo "make help         - Display this help message"

.PHONY: all clean run rebuild install-deps-linux help
