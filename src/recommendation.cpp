#include "recommendation.h"
#include <unordered_map>
#include <set>
#include <algorithm>

std::vector<int> Recommendation::recommendVideos(int userID, const std::map<int, std::vector<int>>& userToVideos) {
    std::unordered_map<int, int> videoFrequency;  // To count how many similar users watched each video
    std::set<int> userWatchedVideos(userToVideos.at(userID).begin(), userToVideos.at(userID).end());  // Convert user-watched videos to a set for quick lookup

    // Find similar users by iterating over videos watched by the user
    for (int videoID : userToVideos.at(userID)) {
        for (const auto& [otherUserID, videos] : userToVideos) {
            if (otherUserID != userID && std::find(videos.begin(), videos.end(), videoID) != videos.end()) {
                // Increment frequency of videos watched by similar users
                for (int similarUserVideo : videos) {
                    if (userWatchedVideos.find(similarUserVideo) == userWatchedVideos.end()) {
                        videoFrequency[similarUserVideo]++;
                    }
                }
            }
        }
    }

    // Convert the frequency map to a sorted vector
    std::vector<std::pair<int, int>> sortedVideos(videoFrequency.begin(), videoFrequency.end());
    std::sort(sortedVideos.begin(), sortedVideos.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return b.second > a.second;  // Sort by frequency in descending order
    });

    // Extract the video IDs from the sorted pairs
    std::vector<int> recommendations;
    for (const auto& pair : sortedVideos) {
        recommendations.push_back(pair.first);
    }

    return recommendations;
}
