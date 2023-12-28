#include "../lib/connectionController.h"

void addConnection(char* request, int clientSocket, DATABASEMANAGER *dbMan, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData){
    //get the current user
    USER *data = userCacheData->getUserFromCacheByToken(parseTokenFromRequest(parseHttpRequest(request)));
    
    //get the user being searched for
    USER *tempdata = parseTokens(parseHttpRequest(request));
    USER *userSearch = userCacheData->getUserFromCache(tempdata->getUsername());

    CONNECTION *userCon = new CONNECTION(data,userSearch,true,false);
    
    if(addConnectionToDatabase(dbMan, userCon)){
        cacheConnectionData->preloadConnectionData(dbMan, userCacheData);
        const char response[] = "HTTP/1.1 200 OK\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }else{
        const char response[] = "HTTP/1.1 500 SERVER ERROR\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}