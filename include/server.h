#ifndef SERVER_H
#define SERVER_H

class Server {
public:
    void start(int port);
private:
    void handle_client(int client_sock);
};

#endif
