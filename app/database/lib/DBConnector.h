#ifndef DB_CONNECTOR_H
#define DB_CONNECTOR_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include <fstream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>

#include "../models/user.h"

using namespace std;
using namespace sql;


class DBConnector
{

private:
	Driver *driver;
	Connection *con;
	Statement *stmt;
	PreparedStatement *prep_stmt;
	ResultSet *res;
	string DATABASE_URL, DATABASE_USER, DATABASE_PASSWORD, DATABASE_NAME;
	

public:
	DBConnector();

	bool createConnection();

	Connection *getConnection();

	void setConnection(Connection *con);

	void deleteConnections();

	bool addUser(User *user);

	bool destroyDatabase(string);

	int getEnvConfig(string path);

	User *getUserData(string cookie);

	User *searchUsername(string username);
	
	bool loginUser(string username, string password);
	// User getUserData(string username, string password);

};

#endif