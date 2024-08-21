#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include <vector>
#include <map>

class Recommendation {
public:
    // Recommend videos based on collaborative filtering
    static std::vector<int> recommendVideos(int userID, const std::map<int, std::vector<int>>& userToVideos);
};

#endif
