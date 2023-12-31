#include "route.h"

struct Route routes[] = {
    {"GET", "/", handleHome},
    {"GET", "/about", handleAbout}
};

void handleRouting(CLIENT *client){
    for (size_t i = 0; i < sizeof(routes) / sizeof(routes[0]); ++i) {
        if (strcmp(client->method, routes[i].method) == 0 || strcmp(client->route, routes[i].path) == 0){
            routes[i].handler(client); // Call the matching route handler
            return;
        }
    }
}

void handleHome(CLIENT *client){
   handlePageRequest(client->route, client->socket);
}

void handleAbout(CLIENT *client){

}

void handleUserProfile(CLIENT *client){

}