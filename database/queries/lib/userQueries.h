#ifndef USER_QUERIES_H
#define USER_QUERIES_H

#include"../../connection/lib/DBManager.h"


extern DATABASEMANAGER *dbMan;

extern Statement *stmt;
extern PreparedStatement *prep_stmt;
extern ResultSet *res;

bool addUserToDatabase();

#endif