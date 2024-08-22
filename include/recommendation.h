#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include <vector>
#include <map>
#include <string>

class Recommendation {
public:
    // Recommend videos based on collaborative filtering
    static std::vector<std::string> recommendVideos(const std::string& userID, const std::map<std::string, std::vector<std::string>>& userToVideos);
};

#endif
