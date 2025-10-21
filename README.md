# 🏓 Pong Clone

A classic 2D Pong game built with C++17 and SFML, featuring two-player local multiplayer, user profiles with persistent statistics, countdown timer, and smooth physics.

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![SFML](https://img.shields.io/badge/SFML-2.6-green.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)

## ✨ Features

- 🎮 **Two-Player Local Multiplayer** - Classic Pong gameplay
- 👥 **User Profile System** - Create and manage player profiles
- 📊 **Persistent Statistics** - Track wins, losses, and total games
- ⏱️ **Countdown Timer** - 3-2-1 countdown after each score
- 🎨 **Clean Menu System** - Intuitive navigation and profile selection
- 🎵 **Sound Effects** - Paddle hits and scoring sounds (optional)
- ⚡ **Smooth Physics** - Ball speed increases with each hit
- 💾 **JSON Storage** - Profiles saved automatically
- 📦 **Portable** - All dependencies included (Windows)

## 📸 Screenshots

> **Main Menu** → **Profile Selection** → **Gameplay** → **Countdown**

## 🚀 Quick Start

### 🎮 Windows - Ready to Play (No Installation!)

**Just download and play:**

1. Clone or download this repository
2. Double-click `pong.exe` or `PLAY.bat`
3. That's it! The game runs immediately! 🎉

> ℹ️ All required DLLs and assets are included. No installation needed!

### 🛠️ Building from Source (Linux/macOS/Windows)

If you want to build from source or you're on Linux/macOS:

#### Prerequisites

1. **C++17 Compiler** (g++, clang++, or MSVC)
2. **SFML 2.6+** - Graphics library
3. **nlohmann/json** - JSON parser (already included)

### Build Instructions

#### Linux (Ubuntu/Debian)

```bash
# Install dependencies
sudo apt-get update
sudo apt-get install build-essential libsfml-dev

# Clone repository
git clone https://github.com/yourusername/pong-clone.git
cd pong-clone

# Build and run
make run
```

#### macOS

```bash
# Install dependencies
brew install sfml

# Clone repository
git clone https://github.com/yourusername/pong-clone.git
cd pong-clone

# Build and run
make run
```

#### Windows (Building from Source)

```powershell
# 1. Install MinGW-w64 (for g++)
# Download from: https://www.mingw-w64.org/

# 2. Download SFML 2.6.1
# Download from: https://www.sfml-dev.org/download/sfml/2.6.1/
# Get: GCC MinGW (SEH) - 64-bit
# Extract to C:\SFML

# 3. Clone repository
git clone https://github.com/yourusername/pong-clone.git
cd pong-clone

# 4. Build with PowerShell script
.\build.ps1 -SFMLPath "C:\SFML" -Run
```

> **Note:** The Windows portable version (pong.exe) already includes all DLLs and fonts, so you can just run it directly without building!

## 🎮 How to Play

### First Time Setup

1. Run the game
2. Create a profile for Player 1
3. Create a profile for Player 2
4. Press **SPACE** to start playing

### Controls

**Menu Navigation:**
- **Arrow Keys** - Navigate options
- **Enter** - Select
- **ESC** - Exit game (in main menu) / Go back

**Player 1 (Left Paddle):**
- **W** - Move up
- **S** - Move down

**Player 2 (Right Paddle):**
- **↑ Arrow** - Move up
- **↓ Arrow** - Move down

**During Game:**
- **ESC** - Return to menu

### Game Rules

- First player to reach **5 points** wins
- Ball speed increases with each paddle hit
- After each score, a **3-2-1 countdown** appears
- Your win/loss record is automatically saved

## 📁 Project Structure

```
pong-clone/
├── src/
│   ├── main.cpp              # Entry point
│   ├── Game.cpp              # Game loop and state management
│   ├── Paddle.cpp            # Paddle physics and controls
│   ├── Ball.cpp              # Ball physics and collision
│   ├── ProfileManager.cpp    # User profile management (JSON)
│   └── Menu.cpp              # Menu system and UI
├── include/
│   ├── Game.h                # Game class interface
│   ├── Paddle.h              # Paddle class interface
│   ├── Ball.h                # Ball class interface
│   ├── ProfileManager.h      # ProfileManager interface
│   ├── Menu.h                # Menu class interface
│   └── nlohmann/
│       └── json.hpp          # JSON library (header-only)
├── assets/
│   ├── font.ttf              # Font file (included)
│   ├── hit.wav               # Hit sound (included)
│   ├── score.wav             # Score sound (included)
│   └── profiles.json         # User profiles (auto-generated)
├── pong.exe                  # Game executable (Windows)
├── *.dll                     # SFML & OpenAL runtime libraries
├── build.ps1                 # Windows build script
├── PLAY.bat                  # Windows quick launch
├── Makefile                  # Linux/macOS build configuration
├── LICENSE                   # MIT License
├── .gitignore                # Git ignore rules
└── README.md                 # This file
```

## 🛠️ Build System

### Makefile (Linux/macOS)

```bash
make              # Build the project
make run          # Build and run
make clean        # Remove build files
make rebuild      # Clean and rebuild
```

### PowerShell Script (Windows)

```powershell
.\build.ps1                                    # Build with default settings
.\build.ps1 -Run                              # Build and run
.\build.ps1 -SFMLPath "C:\Your\Path"         # Specify SFML location
.\build.ps1 -SFMLPath "C:\SFML" -Run         # Build, run with custom path
```

### Quick Launch (Windows)

After first build, just double-click `PLAY.bat` to run the game.

## 📦 Required Assets

### Font File (REQUIRED)

The game needs a TrueType font file at `assets/font.ttf`. You can:

**Option 1: Download from Google Fonts**
- Visit [Google Fonts](https://fonts.google.com/)
- Download any font (Roboto, Open Sans, etc.)
- Rename the `.ttf` file to `font.ttf`
- Place in `assets/` folder

**Option 2: Use System Font**
```bash
# Linux
cp /usr/share/fonts/truetype/dejavu/DejaVuSans.ttf assets/font.ttf

# macOS
cp /System/Library/Fonts/Helvetica.ttc assets/font.ttf

# Windows
Copy-Item "C:\Windows\Fonts\arial.ttf" -Destination "assets\font.ttf"
```

### Sound Files (Optional)

The game works without sound, but you can add:
- `assets/hit.wav` - Paddle hit sound
- `assets/score.wav` - Scoring sound

Download free sounds from [freesound.org](https://freesound.org/) or [zapsplat.com](https://www.zapsplat.com/).

## � User Profiles

Profiles are stored in `assets/profiles.json`:

```json
[
    {
        "username": "Player1",
        "wins": 5,
        "losses": 2,
        "totalGames": 7
    },
    {
        "username": "Player2",
        "wins": 2,
        "losses": 5,
        "totalGames": 7
    }
]
```

The file is created automatically on first run.

## 🏗️ Architecture

The game uses object-oriented design with clear separation of concerns:

- **Game**: Main controller, manages game loop and states
- **Paddle**: Player-controlled paddles with physics
- **Ball**: Ball physics, collision detection, and velocity
- **ProfileManager**: JSON-based profile persistence
- **Menu**: User interface and navigation system

### Technologies

- **C++17**: Modern C++ features, smart pointers, RAII
- **SFML 2.6+**: Graphics, window management, audio, input
- **nlohmann/json**: JSON parsing and serialization

## � Troubleshooting

### "Failed to load font"
**Problem:** Missing `assets/font.ttf`  
**Solution:** Download and place a `.ttf` font file in `assets/` folder

### "Undefined reference to sf::..."
**Problem:** SFML not linked properly  
**Solution:** 
- Ensure SFML is installed
- Check linker flags include all SFML libraries
- On Windows, copy SFML DLLs to game directory

### "nlohmann/json.hpp not found"
**Problem:** Missing JSON header  
**Solution:**
- Download `json.hpp` from [GitHub](https://github.com/nlohmann/json/releases)
- Create `include/nlohmann/` folder
- Place `json.hpp` inside

### Missing DLLs (Windows)
**Problem:** SFML DLL errors when running  
**Solution:** Copy all DLLs from `C:\SFML\bin\` to game directory:
```powershell
Copy-Item "C:\SFML\bin\*.dll" -Destination "."
```

### No Sound
**Problem:** Sound files not playing  
**Solution:** Sound is optional. Add `.wav` files to `assets/` or ignore warnings.

## 🤝 Contributing

Contributions are welcome! Here's how:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 🚀 Future Enhancements

Ideas for future development:

- 🤖 AI opponent for single-player mode
- 🎵 Background music
- ⚡ Power-ups (speed boost, paddle size change)
- 🏆 High score leaderboard
- 🌐 Network multiplayer
- ⚙️ Settings menu (difficulty, volume)
- 🎨 Themes and skins

## � License

This project is open source and available under the MIT License.

## � Acknowledgments

- **SFML** - Simple and Fast Multimedia Library
- **nlohmann/json** - JSON for Modern C++
- Classic Pong game by Atari (1972)

## 📧 Contact

For questions or suggestions, please open an issue on GitHub.

---

**Made with ❤️ using C++ and SFML**

⭐ Star this repository if you found it helpful!
