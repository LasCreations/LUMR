#include "../lib/userQueries.h"



DATABASEMANAGER *dbMan = new DATABASEMANAGER();
Statement *stmt = nullptr;
PreparedStatement *prep_stmt = nullptr;
ResultSet *res = nullptr;

bool addUserToDatabase(){
try
	{
		prep_stmt = dbMan->getConnection()->prepareStatement("INSERT INTO users(username, token, password) VALUES(?,?,?)");
		prep_stmt->setString(1, "test");
		prep_stmt->setString(2, "test");
        prep_stmt->setString(3, "test");

		prep_stmt->execute();
		delete prep_stmt;
		return true;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error adding user: " << e.what() << std::endl;
		delete prep_stmt;
		return false;
	}
}

