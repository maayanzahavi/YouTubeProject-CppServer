#include "server.h"
#include "client_handler.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <thread>

using namespace std;

void Server::start(int port) {
    // Create a TCP socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        return;
    }

    // Define server address structure
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    // Bind the socket to the specified port
    if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("Error binding socket");
        close(sock);
        return;
    }

    // Start listening for incoming connections
    if (listen(sock, 5) < 0) {
        perror("Error listening on socket");
        close(sock);
        return;
    }

    cout << "Server is listening on port " << port << "..." << endl;

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
        thread client_thread(ClientHandler::handle_client, client_sock);

        // Detach the thread so that it runs independently
        client_thread.detach();
    }

    // Close the server socket (this will never be reached in the current loop)
    close(sock);
}
