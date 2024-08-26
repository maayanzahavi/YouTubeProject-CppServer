#include "../include/recommendation.h"
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iostream>

std::vector<std::string> Recommendation::recommendVideos(const std::string& userID, const std::map<std::string, std::vector<std::string>>& userToVideos) {
    // Check if the userID exists in the map
    auto userIt = userToVideos.find(userID);
    if (userIt == userToVideos.end()) {
        std::cerr << "User ID " << userID << " not found in the database." << std::endl;
        return {};  
    }

    std::unordered_map<std::string, int> videoFrequency;  // To count how many similar users watched each video
    const std::vector<std::string>& userVideos = userIt->second;
    std::set<std::string> userWatchedVideos(userVideos.begin(), userVideos.end());  // Convert user-watched videos to a set for quick lookup

    // Find similar users by iterating over the map of all users
    for (const auto& [otherUserID, videos] : userToVideos) {
        if (otherUserID != userID) {
            // Check for intersection between userVideos and other user's videos
            for (const std::string& videoID : videos) {
                if (userWatchedVideos.find(videoID) != userWatchedVideos.end()) {
                    // Increment frequency of videos watched by similar users
                    for (const std::string& similarUserVideo : videos) {
                        if (userWatchedVideos.find(similarUserVideo) == userWatchedVideos.end()) {
                            videoFrequency[similarUserVideo]++;
                        }
                    }
                    break; // Stop checking this user if a common video is found
                }
            }
        }
    }

    // Convert the frequency map to a sorted vector
    std::vector<std::pair<std::string, int>> sortedVideos(videoFrequency.begin(), videoFrequency.end());
    std::sort(sortedVideos.begin(), sortedVideos.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return b.second > a.second;  // Sort by frequency in descending order
    });

    // Extract the video IDs from the sorted pairs
    std::vector<std::string> recommendations;
    for (const auto& pair : sortedVideos) {
        recommendations.push_back(pair.first);
    }

    return recommendations;
}
