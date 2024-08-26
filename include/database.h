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
    void addMapping(const std::string& userID, const std::string& videoID);

    // Get the videos watched by a user
    std::vector<std::string> getVideosForUser(const std::string& userID);

    // Expose the user-to-videos map
    const std::map<std::string, std::vector<std::string>>& getUserToVideos() const;

private:
    std::map<std::string, std::vector<std::string>> userToVideos;  // Mapping of userID to list of videoIDs
};

#endif
