#include "lib/server.h"


int main() {
    Server &serverInstance = Server::getInstance();
    serverInstance.StartHttpServer();

    return EXIT_SUCCESS;
}