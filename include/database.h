#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <vector>

class Database {
public:
    // Load user-to-video mappings from file
    bool loadFromFile(const std::string& filename);

    // Save user-to-video mappings to file
    bool saveToFile(const std::string& filename);

    // Add a mapping from a user to a video
    void addMapping(int userID, int videoID);

    // Get the videos watched by a user
    std::vector<int> getVideosForUser(int userID);

    // Expose the user-to-videos map
    const std::map<int, std::vector<int>>& getUserToVideos() const;

private:
    std::map<int, std::vector<int>> userToVideos;  // Mapping of userID to list of videoIDs
};

#endif
