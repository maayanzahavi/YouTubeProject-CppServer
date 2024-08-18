#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <thread>

using namespace std;

// Function to handle communication with a single client
void handle_client(int client_sock) {
    char buffer[4096];
    int expected_data_len = sizeof(buffer);

    while (true) {
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            // Connection is closed by the client
            cout << "Client disconnected." << endl;
            break;
        } else if (read_bytes < 0) {
            perror("Error receiving data");
            break;
        } else {
            // Successfully received data, print it
            cout << "Received from client: " << buffer << endl;

            // Echo the data back to the client
            int sent_bytes = send(client_sock, buffer, read_bytes, 0);
            if (sent_bytes < 0) {
                perror("Error sending to client");
                break;
            }
        }
    }

    // Close the client socket
    close(client_sock);
}

int main() {
    const int server_port = 5555;

    // Create a TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        return 1;
    }

    // Define server address structure
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;            // IPv4
    sin.sin_addr.s_addr = INADDR_ANY;    // Bind to any available interface
    sin.sin_port = htons(server_port);   // Port number in network byte order

    // Bind the socket to the specified port
    if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("Error binding socket");
        close(sock);
        return 1;
    }

    // Start listening for incoming connections
    if (listen(sock, 5) < 0) {
        perror("Error listening on socket");
        close(sock);
        return 1;
    }

    cout << "Server is listening on port " << server_port << "..." << endl;

    while (true) {
        // Accept an incoming connection
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr*)&client_sin, &addr_len);
        if (client_sock < 0) {
            perror("Error accepting client");
            continue;
        }

        cout << "Client connected. Handling in a separate thread." << endl;

        // Create a new thread to handle the client
        thread client_thread(handle_client, client_sock);

        // Detach the thread so that it runs independently
        client_thread.detach();
    }

    // Close the server socket (this will never be reached in the current loop)
    close(sock);

    return 0;
}
