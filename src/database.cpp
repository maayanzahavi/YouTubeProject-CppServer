#include "database.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Load data from file
bool Database::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        int userID;
        char colon;
        ss >> userID >> colon;

        std::vector<int> videos;
        int videoID;
        while (ss >> videoID) {
            videos.push_back(videoID);
            if (ss.peek() == ',') ss.ignore();  // Ignore commas between video IDs
        }

        userToVideos[userID] = videos;
    }

    file.close();
    return true;
}

// Save data to file
bool Database::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return false;
    }

    for (const auto& pair : userToVideos) {
        file << pair.first << ":";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            file << pair.second[i];
            if (i < pair.second.size() - 1) file << ",";  // Comma-separate video IDs
        }
        file << "\n";
    }

    file.close();
    return true;
}

// Add a user-to-video mapping
void Database::addMapping(int userID, int videoID) {
    userToVideos[userID].push_back(videoID);
}

// Get videos watched by a user
std::vector<int> Database::getVideosForUser(int userID) {
    if (userToVideos.find(userID) != userToVideos.end()) {
        return userToVideos[userID];
    } else {
        return std::vector<int>();  // Return empty vector if userID not found
    }
}

// Expose the user-to-videos map
const std::map<int, std::vector<int>>& Database::getUserToVideos() const {
    return userToVideos;
}
