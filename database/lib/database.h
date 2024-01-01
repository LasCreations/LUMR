#ifndef DATABASE_H
#define DATABASE_H

#include "common.h"

// Using a singleton approach for caching system
class DATABASEMANAGER
{

private:
    DATABASEMANAGER();
    bool getEnvConfig(std::string path);
    bool createConnection();
    sql::Driver *driver;
    sql::Connection *con;
    std::string DATABASE_URL, DATABASE_USER, DATABASE_PASSWORD, DATABASE_NAME;

public:
    static DATABASEMANAGER &getInstance();
    sql::Connection *getConnection();
};

#endif