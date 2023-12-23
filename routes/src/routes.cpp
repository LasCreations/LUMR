#include "../lib/routes.h"


char method[10] = "";
char route[100] = "";


void apiRoute(char* request, int clientSocket, USERCACHE *userCacheData){
        // parse HTTP request
        sscanf(request, "%s %s", method, route);
        printf("%s %s\n", method, route);

        // only support GET method
        if (strcmp(method, "GET") == 0)
        {
            // addUser();
            handlePageRequest(route, clientSocket);
            
        }
        else if (strcmp(method, "POST") == 0)
        {
            if (strcmp(route, "/user/register") == 0){
                if(!userExistsInCache(request,clientSocket,userCacheData)){
                    addUser(request, clientSocket, userCacheData);
                }
            }
               

            // if (strcmp(route, "/api/users/me") == 0)
            //     findUser(request, clientSocket, user_data_cache);

            // if (strcmp(route, "/api/search/user") == 0)
            //     searchUser(request, clientSocket);

            // if (strcmp(route, "/api/follow/user") == 0)
            //     followUser(request, clientSocket);

            // if (strcmp(route, "/api/auth/login") == 0)
            //     loginUser(request, clientSocket, user_data_cache);
        }
        else
        {
            const char response[] = "HTTP/1.1 400 Bad Request\r\n\n";
            send(clientSocket, response, sizeof(response), 0);
        }
}

        