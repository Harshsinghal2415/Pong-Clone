@echo off
REM Pong Game Launcher
REM Double-click this file to run the game!

cd /d "%~dp0"

echo.
echo ========================================
echo   PONG GAME LAUNCHER
echo ========================================
echo.

REM Check if game is built
if exist "pong.exe" (
    echo Starting Pong Game...
    echo.
    pong.exe
) else (
    echo ERROR: pong.exe not found!
    echo.
    echo You need to build the game first.
    echo Run: build.ps1
    echo.
    pause
)
