#include "../lib/factory.h"

DBConnector::DBConnector() : driver(nullptr), con(nullptr), stmt(nullptr), prep_stmt(nullptr), res(nullptr)
{
}

int DBConnector::getEnvConfig(string path)
{
	// Read the JSON file
	std::ifstream jsonFile(path);
	if (!jsonFile.is_open())
	{
		std::cerr << "Error opening JSON file: " << path << "\n";
		return 1;
	}

	// Parse the JSON data from the file
	Json::Value jsonData;
	Json::CharReaderBuilder readerBuilder;
	try
	{
		Json::parseFromStream(readerBuilder, jsonFile, &jsonData, nullptr);

		// Access individual fields
		this->DATABASE_URL = jsonData["DATABASE_URL"].asString();
		this->DATABASE_PASSWORD = jsonData["DATABASE_PASSWORD"].asString();
		this->DATABASE_USER = jsonData["DATABASE_USER"].asString();
		this->DATABASE_NAME = jsonData["DATABASE_NAME"].asString();
	}
	catch (const Json::Exception &e)
	{
		std::cerr << "Error parsing JSON: " << e.what() << "\n";
		return 1;
	}

	return 1;
}

bool DBConnector::createConnection()
{
	getEnvConfig("config/config.json");
	try
	{
		if ((this->driver = get_driver_instance()))
		{
		}
		if ((this->con = driver->connect(this->DATABASE_URL, this->DATABASE_USER, this->DATABASE_PASSWORD)))
		{
			/*Connect to the MySQL test database */
			con->setSchema(this->DATABASE_NAME);
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
		this->prep_stmt = this->con->prepareStatement("INSERT INTO users(passport, username, email, password, avatar_url) VALUES(?,?,?,?,?)");
		this->prep_stmt->setString(1, user->getCookie());
		this->prep_stmt->setString(2, user->getUsername());
		this->prep_stmt->setString(3, user->getEmail());
		this->prep_stmt->setString(4, user->getPassword());
		this->prep_stmt->setString(5, user->getAvatarURL());

		this->prep_stmt->execute();
		delete this->prep_stmt;
		return true;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error adding user: " << e.what() << std::endl;
		delete this->prep_stmt;
		return false;
	}
}

User *DBConnector::getUserData(string cookie)
{
	User *data = nullptr;
	try
	{
		this->stmt = con->createStatement();
		this->res = this->stmt->executeQuery("SELECT passport, username, email, password, avatar_url FROM users WHERE passport = '" + cookie + "'");
		while (this->res->next())
		{
			data = new User(this->res->getString("username"),
							this->res->getString("email"),
							this->res->getString("password"),
							cookie,
							this->res->getString("avatar_url"));
		}
	}
	catch (const sql::SQLException &e)
	{
		// Handle the exception, e.g., print error message
		std::cerr << "SQLException: " << e.what() << std::endl;
	}
	delete this->stmt;
	delete this->res;
	return data;
}

User *DBConnector::searchUsername(string username)
{
	User *data = nullptr;

	try
	{
		this->stmt = con->createStatement();
		this->res = this->stmt->executeQuery("SELECT  username, avatar_url FROM users WHERE username = '" + username + "'");
		while (this->res->next())
		{
			data = new User(this->res->getString("username"), "", "", "", this->res->getString("avatar_url"));
		}
	}
	catch (const sql::SQLException &e)
	{
		// Handle the exception, e.g., print error message
		std::cerr << "SQLException: " << e.what() << std::endl;
	}
	delete this->stmt;
	delete this->res;
	return data;
}

bool DBConnector::checkFriendship(string userID_1, string userID_2)
{
	try
	{
		this->stmt = con->createStatement();
		this->res = this->stmt->executeQuery("SELECT status FROM user_connections WHERE user_id = '" + userID_1 + "' AND  following_id= '" + userID_2 + "'");
		bool check = false;
		bool isFriend = false;
		while (this->res->next())
		{
			check = true; // if found
			isFriend = this->res->getBoolean("status");
		}

		if (check && isFriend)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (const sql::SQLException &e)
	{
		// Handle the exception, e.g., print error message
		std::cerr << "SQLException: " << e.what() << std::endl;
	}
	delete this->stmt;
	delete this->res;
	return false;
}

bool DBConnector::addFriendshipToDatabase(string key, string userID, string followerID, bool status)
{
	try
	{
		this->prep_stmt = this->con->prepareStatement("INSERT INTO user_connections(connection_key, user_id, following_id, status) VALUES(?,?,?,?)");

		// User who sent the request
		this->prep_stmt->setString(1, key);
		this->prep_stmt->setString(2, userID);
		this->prep_stmt->setString(3, followerID);
		this->prep_stmt->setBoolean(4, status);
		this->prep_stmt->execute();

		delete this->prep_stmt;
		return true;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error adding user: " << e.what() << std::endl;
		delete this->prep_stmt;
		return false;
	}
}

std::unordered_map<string, User *> *DBConnector::getUsersCacheData()
{
	User *data = nullptr;
	unordered_map<string, User *> *cachemap = nullptr;
	try
	{
		cachemap = new std::unordered_map<std::string, User *>;
		this->stmt = con->createStatement();
		this->res = this->stmt->executeQuery("SELECT passport, username, email, password, avatar_url FROM users");
		while (this->res->next())
		{
			data = new User(this->res->getString("username"),
							this->res->getString("email"),
							this->res->getString("password"),
							this->res->getString("passport"),
							this->res->getString("avatar_url"));
			(*cachemap)[this->res->getString("passport")] = data;
		}
	}
	catch (const sql::SQLException &e)
	{
		// Handle the exception, e.g., print error message
		std::cerr << "SQLException: " << e.what() << std::endl;
	}
	delete this->stmt;
	delete this->res;
	return cachemap;
}

bool DBConnector::updatePassport(string newCookie, User *data)
{
	try
	{
		this->prep_stmt = this->con->prepareStatement("UPDATE users SET passport = ? WHERE passport=?");
		this->prep_stmt->setString(1, newCookie);
		this->prep_stmt->setString(2, data->getCookie());

		this->prep_stmt->execute();
		delete this->prep_stmt;
		return true;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error adding user: " << e.what() << std::endl;
		delete this->prep_stmt;
		return false;
	}
}