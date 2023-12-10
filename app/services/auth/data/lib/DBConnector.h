#pragma once

#include<stdlib.h>
#include<string>
#include<iostream>
#include<vector>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "../models/user.h"

using namespace std;
using namespace sql;

class DBConnector{

	private:
        	Driver *driver;
        	Connection *con;
        	Statement *stmt;
        	PreparedStatement *prep_stmt;
        	ResultSet *res;

    	public:

            DBConnector(); 
            
            bool createConnection();
        
            Connection* getConnection();

			void setConnection(Connection *con);

			void deleteConnections();

			bool addUser(User *user);

            bool destroyDatabase(string);
};
