#include "../include/database.h"
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
        std::string userID;
        char colon;
        ss >> userID >> colon;

        std::vector<std::string> videos;
        std::string videoID;
        while (getline(ss, videoID, ',')) {  // Read video IDs separated by commas
            videos.push_back(videoID);
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
void Database::addMapping(const std::string& userID, const std::string& videoID) {
    userToVideos[userID].push_back(videoID);
}

// Get videos watched by a user
std::vector<std::string> Database::getVideosForUser(const std::string& userID) {
    if (userToVideos.find(userID) != userToVideos.end()) {
        return userToVideos[userID];
    } else {
        return std::vector<std::string>();  // Return empty vector if userID not found
    }
}

// Expose the user-to-videos map
const std::map<std::string, std::vector<std::string>>& Database::getUserToVideos() const {
    return userToVideos;
}
