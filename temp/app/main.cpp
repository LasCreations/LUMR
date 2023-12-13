#include "server/lib/server.h"

//test from develop branch

int main() {
    Server &serverInstance = Server::getInstance();
    serverInstance.StartHttpServer();

    return EXIT_SUCCESS;
}