# C++ Server

## Run the Server

1. Clone the repository to your local machine.
2. Open a terminal in the cloned folder.
3. In `src/main.cpp`, change the server port number if needed.
4. Execute the following command to start the server:
   ```bash
   ./server
   
## Recommendation Algorithm

The recommendation algorithm implemented in this project is designed to suggest videos to users based on their viewing history. The algorithm primarily operates in the following steps:

### 1. Handling Client Requests

The server handles incoming client requests through the `ClientHandler` class, specifically in the `handle_client` method. The server can process two types of requests:
- **Recommendations Request**: The client sends a request in the format `recommend:<userID>`. This triggers the server to generate video recommendations for the specified user.
- **Watch History Update**: The client sends a request in the format `<userID>:<videoID>`, indicating that the user has watched a specific video. The server updates the user's watch history accordingly.

### 2. Generating Recommendations

The core of the recommendation algorithm is implemented in the `Recommendation::recommendVideos` method. Here's how it works:

#### Step 1: Find Similar Users
- The algorithm begins by identifying other users who have watched similar videos to the requesting user. This is done by iterating over all users in the database and checking if they have watched any videos in common with the requesting user.

#### Step 2: Count Video Frequencies
- For each similar user, the algorithm counts the number of times they have watched other videos that the requesting user has not yet seen. This frequency count is stored in a map (`videoFrequency`), where the key is the video ID and the value is the frequency.

#### Step 3: Sort Videos by Popularity
- The videos are then sorted by frequency in descending order. This means that videos watched by the most similar users are considered the most relevant recommendations.

#### Step 4: Filter Watched Videos
- Finally, the algorithm filters out any videos that the requesting user has already watched to ensure that only new content is recommended.

### 3. Database Management

The algorithm relies on a `Database` class that stores the following mappings:
- **User to Videos**: A map that tracks which videos each user has watched.
- **Video to Users**: A map that tracks which users have watched each video.
- **Video Frequency List**: A map that counts how many 'similar users' have watched each video.

#### Data Persistence
- The `Database` class is capable of loading from and saving to a file (`storage.txt`). This ensures that the user's watch history and video frequencies are preserved across server restarts.

#### Updating the Database
- When a user watches a new video, the server updates the database using the `Database::addMapping` method, which modifies the in-memory structures and immediately saves the changes to the file.

### 4. Example Scenario

Suppose User A has watched Videos 1, 2, and 3, while User B has watched Videos 2, 3, and 4. If User A requests recommendations, the algorithm will notice the common videos (2 and 3) between User A and User B, and then recommend Video 4 to User A because User B has watched it but User A has not.

### 5. Server Operation

The server listens on a specified port for incoming connections. For each client connection, it spawns a new thread to handle the client's requests independently. This design ensures that multiple clients can be served concurrently without blocking the main server thread.

### Conclusion

This recommendation system is a basic collaborative filtering algorithm that leverages user similarity to suggest content. While simple, it provides a solid foundation that can be extended with more sophisticated techniques, such as content-based filtering or matrix factorization.

## Work Distribution

We approached this project collaboratively, working together on each part of the development process:

- **Recommendation Algorithm**: We began by understanding how the recommendation algorithm works. This was crucial for the server's functionality, ensuring it can provide accurate video recommendations.
- **Server Creation**: After understanding the algorithm, we designed and developed the C++ server. We applied knowledge from the lectures to decide on the structure and how to implement the necessary code.
- **API Integration**: Once the server was up and running, we integrated its functionality with the React frontend and the Android application. This included creating the necessary API requests to fetch recommended videos and ensuring smooth communication between the server and the clients.
- **Testing and Validation**: Finally, we thoroughly tested the server by running it in both the React frontend and the Android application. We verified that the server returns the correct recommended videos, ensuring everything works as expected.

## Repository Links

You can find the related repositories here:

- [Android Application Repository (Part 3)](https://github.com/amitkarol/AndroidYTPart3.git)
- [Web Application Repository (Part 2)](https://github.com/maayanzahavi/WebPart2.git)
- **Note**: The relevant branches for the server integration and functionality are under **mainPart4**.
