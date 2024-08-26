#include "../include/database.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm> // for std::find

// Load data from file
bool Database::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;

    // Load userToVideos
    while (getline(file, line) && !line.empty()) {
        std::stringstream ss(line);
        std::string userID;
        char colon;
        ss >> userID >> colon;

        std::vector<std::string> videos;
        std::string videoID;
        while (getline(ss, videoID, ',')) {  // Read video IDs separated by commas
            videos.push_back(videoID);
        }

        // Ensure userID is parsed correctly
        if (!userID.empty()) {
            userToVideos[userID] = videos;
            std::cout << "Loaded user: " << userID << " with videos: ";
            for (const auto& vid : videos) {
                std::cout << vid << " ";
            }
            std::cout << std::endl;
        }
    }

    // Load videoToUsers
    while (getline(file, line) && !line.empty()) {
        std::stringstream ss(line);
        std::string videoID;
        char colon;
        ss >> videoID >> colon;

        std::vector<std::string> users;
        std::string userID;
        while (getline(ss, userID, ',')) {  // Read user IDs separated by commas
            users.push_back(userID);
        }

        // Ensure videoID is parsed correctly
        if (!videoID.empty()) {
            videoToUsers[videoID] = users;
            std::cout << "Loaded video: " << videoID << " with users: ";
            for (const auto& user : users) {
                std::cout << user << " ";
            }
            std::cout << std::endl;
        }
    }

    // Load frequencyList
    while (getline(file, line) && !line.empty()) {
        std::stringstream ss(line);
        std::string videoID;
        int frequency;
        ss >> videoID >> frequency;

        // Ensure videoID and frequency are parsed correctly
        if (!videoID.empty()) {
            frequencyList[videoID] = frequency;
            std::cout << "Loaded video: " << videoID << " with frequency: " << frequency << std::endl;
        }
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

    // Save userToVideos
    for (const auto& pair : userToVideos) {
        file << pair.first << ":";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            file << pair.second[i];
            if (i < pair.second.size() - 1) file << ",";  // Comma-separate video IDs
        }
        file << "\n";
    }

    // Separate sections
    file << "\n";

    // Save videoToUsers
    for (const auto& pair : videoToUsers) {
        file << pair.first << ":";
        for (size_t i = 0; i < pair.second.size(); ++i) {
            file << pair.second[i];
            if (i < pair.second.size() - 1) file << ",";  // Comma-separate user IDs
        }
        file << "\n";
    }

    // Separate sections
    file << "\n";

    // Save frequencyList
    for (const auto& pair : frequencyList) {
        file << pair.first << " " << pair.second << "\n";
    }

    file.close();
    return true;
}

// Add a user-to-video mapping and update related data structures
void Database::addMapping(const std::string& userID, const std::string& videoID) {
    // Update userToVideos only if the video is not already in the user's list
    if (std::find(userToVideos[userID].begin(), userToVideos[userID].end(), videoID) == userToVideos[userID].end()) {
        userToVideos[userID].push_back(videoID);
    }

    // Update videoToUsers only if the user is not already in the video's list
    if (std::find(videoToUsers[videoID].begin(), videoToUsers[videoID].end(), userID) == videoToUsers[videoID].end()) {
        videoToUsers[videoID].push_back(userID);
    }

    // Update frequencyList
    frequencyList[videoID]++;

    // Save the updated database to the file after every update
    if (!saveToFile("data/storage.txt")) {
        std::cerr << "Error saving data to file after update." << std::endl;
    }
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

// Expose the video-to-users map
const std::map<std::string, std::vector<std::string>>& Database::getVideoToUsers() const {
    return videoToUsers;
}

// Expose the frequency list
const std::map<std::string, int>& Database::getFrequencyList() const {
    return frequencyList;
}
