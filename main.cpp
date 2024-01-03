
#include "server.h"
#include "cache.h"
#include "database.h"


int main()
{

    // Initialize singletons
    DATABASEMANAGER::getInstance();
    CACHE::getInstance();
    
    //run the server 
    confiureServer();
    return EXIT_SUCCESS;
}