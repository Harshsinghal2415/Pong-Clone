#include "ProfileManager.h"
#include <fstream>
#include <iostream>

// Constructor
ProfileManager::ProfileManager(const std::string& profilePath)
    : filepath(profilePath) {
    loadProfiles();
}

// Load profiles from JSON file
bool ProfileManager::loadProfiles() {
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        std::cout << "No existing profiles found. Creating new profile database." << std::endl;
        return false;
    }
    
    try {
        json j;
        file >> j;
        file.close();
        
        // Parse JSON array of profiles
        if (j.is_array()) {
            for (const auto& item : j) {
                UserProfile profile;
                profile.username = item["username"].get<std::string>();
                profile.wins = item["wins"].get<int>();
                profile.losses = item["losses"].get<int>();
                profile.totalGames = item["totalGames"].get<int>();
                
                profiles[profile.username] = profile;
            }
        }
        
        std::cout << "Loaded " << profiles.size() << " profiles." << std::endl;
        return true;
        
    } catch (const json::exception& e) {
        std::cerr << "Error parsing profiles.json: " << e.what() << std::endl;
        return false;
    }
}

// Save profiles to JSON file
bool ProfileManager::saveProfiles() {
    try {
        json j = json::array();
        
        // Convert profiles map to JSON array
        for (const auto& pair : profiles) {
            json profileJson;
            profileJson["username"] = pair.second.username;
            profileJson["wins"] = pair.second.wins;
            profileJson["losses"] = pair.second.losses;
            profileJson["totalGames"] = pair.second.totalGames;
            
            j.push_back(profileJson);
        }
        
        // Write to file with pretty formatting
        std::ofstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing: " << filepath << std::endl;
            return false;
        }
        
        file << j.dump(4); // 4-space indentation
        file.close();
        
        std::cout << "Saved " << profiles.size() << " profiles." << std::endl;
        return true;
        
    } catch (const json::exception& e) {
        std::cerr << "Error saving profiles: " << e.what() << std::endl;
        return false;
    }
}

// Get a profile by username
UserProfile* ProfileManager::getProfile(const std::string& username) {
    auto it = profiles.find(username);
    if (it != profiles.end()) {
        return &(it->second);
    }
    return nullptr;
}

// Create a new profile
bool ProfileManager::createProfile(const std::string& username) {
    if (username.empty()) {
        std::cerr << "Username cannot be empty." << std::endl;
        return false;
    }
    
    if (profileExists(username)) {
        std::cerr << "Profile already exists: " << username << std::endl;
        return false;
    }
    
    UserProfile newProfile(username);
    profiles[username] = newProfile;
    
    std::cout << "Created profile: " << username << std::endl;
    return saveProfiles();
}

// Update stats for a profile
void ProfileManager::updateStats(const std::string& username, bool won) {
    UserProfile* profile = getProfile(username);
    if (profile) {
        profile->totalGames++;
        if (won) {
            profile->wins++;
        } else {
            profile->losses++;
        }
        saveProfiles();
    }
}

// Get all profile names
std::vector<std::string> ProfileManager::getProfileNames() const {
    std::vector<std::string> names;
    for (const auto& pair : profiles) {
        names.push_back(pair.first);
    }
    return names;
}

// Check if profile exists
bool ProfileManager::profileExists(const std::string& username) const {
    return profiles.find(username) != profiles.end();
}
