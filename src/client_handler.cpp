#include "client_handler.h"
#include "database.h"
#include "recommendation.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sstream>

extern Database db;  // Global Database object

using namespace std;

void ClientHandler::handle_client(int client_sock) {
    char buffer[4096];
    int expected_data_len = sizeof(buffer);

    while (true) {
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            cout << "Client disconnected." << endl;
            break;
        } else if (read_bytes < 0) {
            perror("Error receiving data");
            break;
        } else {
            // Successfully received data, parse it
            buffer[read_bytes] = '\0';  // Null-terminate the received string
            cout << "Received from client: " << buffer << endl;

            // Parse the message in the format "userID:videoID"
            int userID, videoID;
            stringstream ss(buffer);
            char colon;
            if (ss >> userID >> colon >> videoID && colon == ':') {
                // Update the in-memory database with the userID and videoID
                db.addMapping(userID, videoID);
                cout << "Updated database: User " << userID << " watched video " << videoID << endl;

                // Generate recommendations for the user
                vector<int> recommendations = Recommendation::recommendVideos(userID, db.getUserToVideos());

                // Convert the list of recommended videos to a comma-separated string
                stringstream recommendations_stream;
                for (size_t i = 0; i < recommendations.size(); ++i) {
                    recommendations_stream << recommendations[i];
                    if (i < recommendations.size() - 1) {
                        recommendations_stream << ",";
                    }
                }
                string recommendations_str = recommendations_stream.str();

                // Send the list of recommended videos back to the client
                send(client_sock, recommendations_str.c_str(), recommendations_str.size(), 0);
                cout << "Sent recommendations to client: " << recommendations_str << endl;
            } else {
                // Invalid format, send error message
                string error_message = "Invalid format. Expected format: userID:videoID";
                send(client_sock, error_message.c_str(), error_message.size(), 0);
            }
        }
    }

    close(client_sock);
}
