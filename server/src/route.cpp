#include "route.h"

struct Route routes[] = {
    {"GET", "/", pageRequest},
    {"GET", "/about", handleAbout}
};

void handleRouting(CLIENT *client)
{

    if (strcmp(client->method, "GET") == 0)
    {
        routes[0].handler(client); //page resources are being requested
    }
    else
    {
        for (size_t i = 0; i < sizeof(routes) / sizeof(routes[0]); ++i)
        {
            if (strcmp(client->route, routes[i].path) == 0)
            {
                routes[i].handler(client);  //specific path was requested
                return;
            }
        }
    }
}

void pageRequest(CLIENT *client)
{
    handlePageRequest(client->route, client->socket);
}

void handleAbout(CLIENT *client)
{
}

void handleUserProfile(CLIENT *client)
{
}