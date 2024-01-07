#include "route.h"

struct Route routes[] = {
    {"GET", "/", handlePageRequest},
    {"GET", "/institutions", handleInstitutions},
    {"POST", "/degree", handleDegrees},
    {"POST", "/courses", handleCourses},
    {"GET", "/user/authenticate", handleUserAuthentication},
    {"POST", "/user/authenticate/login", handleUserLoginAuthentication},
    {"POST", "/register/user", handleUserRegistration}
};


void handleRouting(CLIENT *client)
{
    if (strcmp(client->method, "GET") == 0 || strcmp(client->method, "POST") == 0)
    {
        for (size_t i = 0; i < sizeof(routes) / sizeof(routes[0]); ++i)
        {
            if (strcmp(client->route, routes[i].path) == 0)
            {
                routes[i].handler(client); // specific path was requested
                return; // Exit the function immediately after handling the request
            }
        }
        routes[0].handler(client); // page resources are being requested
    }else{
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(client->socket, response, sizeof(response) - 1, 0);
    }
}