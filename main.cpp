
#include "server.h"
#include "cache.h"
#include "database.h"

int main()
{

    // Initialize singletons
    DATABASEMANAGER &dbMan = DATABASEMANAGER::getInstance();
    CACHE &cache = CACHE::getInstance();

    // for (const auto &inst : cache.getInstitutionMap())
    // {
    //     std::cout << inst.second.getInstitutionName() << "(" << inst.second.getInstitutionCode() << ")" << std::endl;
    //     for (const auto &deg : *(inst.second.getInstitutionDegrees()))
    //     {
    //         std::cout << deg.getDegreeCode() << " " << deg.getDegreeName() << std::endl;
    //         for (const auto &cour : *(deg.getCourses()))
    //         {
    //             std::cout << cour.getCourseCode() << " " << cour.getCourseName() << std::endl;
    //         }
    //     }
    // }
    confiureServer();
    return EXIT_SUCCESS;
}