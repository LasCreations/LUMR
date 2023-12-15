#include "../lib/DBConnector.h"

DBConnector::DBConnector() : driver(nullptr), con(nullptr), stmt(nullptr), prep_stmt(nullptr), res(nullptr) {}

bool DBConnector::createConnection()
{
	try
	{
		if ((this->driver = get_driver_instance()))
		{
		}
		if((this->con = driver->connect("localhost", "lascelle", "password"))){
			/*Connect to the MySQL test database */
			con->setSchema("test");
		}
	}
	catch (sql::SQLException &e)
	{
		e.getErrorCode();
		return false;
	}
	return true;
}

void DBConnector::deleteConnections()
{
	delete res;
	delete stmt;
	delete con;
	delete prep_stmt;
}

Connection *DBConnector::getConnection()
{
	return this->con;
}

void DBConnector::setConnection(Connection *con)
{
	this->con = con;
}

bool DBConnector::addUser(User *user)
{
	try
	{
		this->prep_stmt = this->con->prepareStatement("INSERT INTO User(username, email, password,sessionID) VALUES(?, ?, ?,?)");

		this->prep_stmt->setString(1, user->getUsername());
		this->prep_stmt->setString(2, user->getEmail());
		this->prep_stmt->setString(3, user->getPassword());
		this->prep_stmt->setString(4, user->getCookie());
		this->prep_stmt->execute();
		delete this->stmt;
		return true; // Successful execution
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error adding user: " << e.what() << std::endl;
		delete this->stmt;
		return false; // Error occurred
	}
}
