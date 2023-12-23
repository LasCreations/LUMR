#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "../../../utils/database.h"

class DATABASEMANAGER
{
private:
    Driver *driver;
    Connection *con;
    string DATABASE_URL, DATABASE_USER, DATABASE_PASSWORD, DATABASE_NAME;

public:
    DATABASEMANAGER();

    bool getEnvConfig(string path);

    bool createConnection();

    Connection *getConnection();
    
    bool deleteConnections();
};


extern DATABASEMANAGER *dbMan;
extern Statement *stmt;
extern PreparedStatement *prep_stmt;
extern ResultSet *res;

#endif