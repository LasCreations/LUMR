
#include "server.h"
#include "cache.h"
#include "database.h"

int main(){

    //Initialize singletons
    DATABASEMANAGER& dbMan = DATABASEMANAGER::getInstance();
    CACHE& cache = CACHE::getInstance();

    confiureServer();
    return EXIT_SUCCESS;  
}