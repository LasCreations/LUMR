
#include "server.h"
#include "cache.h"
#include "database.h"


int main()
{

    // Initialize singletons
    DATABASEMANAGER::getInstance();
    CACHE::getInstance();
    


    // for(const auto &itInst : CACHE::getInstance().getInstitutionMap()){
    //     for(const auto &itDeg : itInst.second.getInstitutionDegrees()){
    //        for(const auto &itCour : itDeg.second.getCourses()) {
    //             std::cout << itCour.second.getCourseName() << std::endl;
    //             std::cout << itCour.second.getCourseCode() << std::endl;
    //        }
    //     }
    // }
    //run the server 
    confiureServer();
    return EXIT_SUCCESS;
}