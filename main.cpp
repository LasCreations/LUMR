
#include "server.h"
#include "cache.h"
#include "database.h"


int main()
{

    // Initialize singletons
    DATABASEMANAGER::getInstance();
    CACHE::getInstance();
    
    for (const auto &user : CACHE::getInstance().getUserMap()){
        std::cout << user.second.getUsername() << std::endl;
    }

    //run the server 
    confiureServer();
    return EXIT_SUCCESS;
}