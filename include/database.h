#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <vector>
#include <string>

class Database {
private:
    std::map<std::string, std::vector<std::string>> userToVideos;
    std::map<std::string, std::vector<std::string>> videoToUsers;
    std::map<std::string, int> frequencyList;

public:
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename);
    void addMapping(const std::string& userID, const std::string& videoID);

    std::vector<std::string> getVideosForUser(const std::string& userID);
    const std::map<std::string, std::vector<std::string>>& getUserToVideos() const;
    const std::map<std::string, std::vector<std::string>>& getVideoToUsers() const;
    const std::map<std::string, int>& getFrequencyList() const;
};

#endif
