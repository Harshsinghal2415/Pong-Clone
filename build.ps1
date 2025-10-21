# Pong Clone - Build Script for Windows (PowerShell)
# Make sure to set the correct SFML path below

param(
    [string]$SFMLPath = "C:\SFML",
    [switch]$Run
)

Write-Host "==================================" -ForegroundColor Cyan
Write-Host "  Pong Clone - Windows Build     " -ForegroundColor Cyan
Write-Host "==================================" -ForegroundColor Cyan
Write-Host ""

# Check if SFML path exists
if (-not (Test-Path $SFMLPath)) {
    Write-Host "ERROR: SFML not found at: $SFMLPath" -ForegroundColor Red
    Write-Host "Please install SFML or specify the path:" -ForegroundColor Yellow
    Write-Host "  .\build.ps1 -SFMLPath 'C:\Path\To\SFML'" -ForegroundColor Yellow
    exit 1
}

Write-Host "SFML Path: $SFMLPath" -ForegroundColor Green

# Check for required files
$requiredFiles = @(
    "assets\font.ttf"
)

$missingFiles = @()
foreach ($file in $requiredFiles) {
    if (-not (Test-Path $file)) {
        $missingFiles += $file
    }
}

if ($missingFiles.Count -gt 0) {
    Write-Host ""
    Write-Host "WARNING: Missing required asset files:" -ForegroundColor Yellow
    foreach ($file in $missingFiles) {
        Write-Host "  - $file" -ForegroundColor Yellow
    }
    Write-Host ""
    Write-Host "Please read assets\README.md for setup instructions." -ForegroundColor Yellow
    Write-Host ""
}

# Build command
Write-Host "Building Pong Clone..." -ForegroundColor Cyan
Write-Host ""

$buildCommand = "g++ src/*.cpp -Iinclude -I`"$SFMLPath/include`" -L`"$SFMLPath/lib`" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -std=c++17 -o pong.exe"

Write-Host "Executing: $buildCommand" -ForegroundColor Gray
Write-Host ""

Invoke-Expression $buildCommand

if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Write-Host "Build successful! ✓" -ForegroundColor Green
    Write-Host ""
    
    # Copy SFML DLLs if they exist
    $dllPath = Join-Path $SFMLPath "bin"
    if (Test-Path $dllPath) {
        Write-Host "Copying SFML DLLs..." -ForegroundColor Cyan
        $dlls = @(
            "sfml-graphics-2.dll",
            "sfml-window-2.dll", 
            "sfml-system-2.dll",
            "sfml-audio-2.dll"
        )
        
        foreach ($dll in $dlls) {
            $dllFile = Join-Path $dllPath $dll
            if (Test-Path $dllFile) {
                Copy-Item $dllFile -Destination "." -Force
                Write-Host "  Copied: $dll" -ForegroundColor Gray
            }
        }
        Write-Host ""
    }
    
    if ($Run) {
        Write-Host "Running game..." -ForegroundColor Cyan
        Write-Host ""
        .\pong.exe
    } else {
        Write-Host "To run the game, execute: .\pong.exe" -ForegroundColor Yellow
        Write-Host "Or build and run with: .\build.ps1 -Run" -ForegroundColor Yellow
    }
} else {
    Write-Host ""
    Write-Host "Build failed! ✗" -ForegroundColor Red
    Write-Host ""
    Write-Host "Common issues:" -ForegroundColor Yellow
    Write-Host "  - Make sure g++ is installed and in PATH" -ForegroundColor Gray
    Write-Host "  - Verify SFML path is correct" -ForegroundColor Gray
    Write-Host "  - Check that nlohmann/json.hpp is in include/nlohmann/" -ForegroundColor Gray
    exit 1
}
