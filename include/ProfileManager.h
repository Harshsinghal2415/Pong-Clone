#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include <string>
#include <map>
#include <vector>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct UserProfile {
    std::string username;
    int wins;
    int losses;
    int totalGames;

    UserProfile() : username(""), wins(0), losses(0), totalGames(0) {}
    UserProfile(const std::string& name) : username(name), wins(0), losses(0), totalGames(0) {}
};

class ProfileManager {
private:
    std::map<std::string, UserProfile> profiles;
    std::string filepath;

public:
    // Constructor
    ProfileManager(const std::string& profilePath = "assets/profiles.json");

    // Load and save profiles
    bool loadProfiles();
    bool saveProfiles();

    // Profile management
    UserProfile* getProfile(const std::string& username);
    bool createProfile(const std::string& username);
    void updateStats(const std::string& username, bool won);
    
    // Get all profile names
    std::vector<std::string> getProfileNames() const;

    // Check if profile exists
    bool profileExists(const std::string& username) const;
};

#endif // PROFILEMANAGER_H
