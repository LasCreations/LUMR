#include "../lib/DBConnector.h"



DBConnector::DBConnector() : driver(nullptr), con(nullptr), stmt(nullptr), prep_stmt(nullptr), res(nullptr) {
	
}

int DBConnector::getEnvConfig(string path){
    // Read the JSON file
    std::ifstream jsonFile(path);
    if (!jsonFile.is_open()) {
        std::cerr << "Error opening JSON file: " << path << "\n";
        return 1;
    }

    // Parse the JSON data from the file
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    try {
        Json::parseFromStream(readerBuilder, jsonFile, &jsonData, nullptr);

        // Access individual fields
		this->DATABASE_URL = jsonData["DATABASE_URL"].asString();
		this->DATABASE_PASSWORD = jsonData["DATABASE_PASSWORD"].asString();
		this->DATABASE_USER = jsonData["DATABASE_USER"].asString();
		this->DATABASE_NAME = jsonData["DATABASE_NAME"].asString();
    } catch (const Json::Exception &e) {
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
		this->prep_stmt = this->con->prepareStatement("INSERT INTO USER(Passport, Username, Email, Password, AvatarURL) VALUES(?,?,?,?,?)");

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
		this->res = this->stmt->executeQuery("SELECT Passport, Username, Email, Password, AvatarURL FROM USER WHERE Passport = '" + cookie + "'");
		while (this->res->next())
		{
			data = new User(this->res->getString("Username"),
			 				this->res->getString("Email"),
							this->res->getString("Password"),
							cookie,
							this->res->getString("AvatarURL"));
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

User *DBConnector::searchUsername(string username){
	User *data = nullptr;
	
	try
	{
		this->stmt = con->createStatement();
		this->res = this->stmt->executeQuery("SELECT  Username, AvatarURL FROM USER WHERE Username = '" + username + "'");
		while (this->res->next())
		{
			data = new User(this->res->getString("Username"), "", "", "", this->res->getString("AvatarURL"));
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

bool DBConnector::addFriendshipToDatabase(string friendshipID_1, string friendshipID_2, string userID, string followerID){
try
	{

		cout << "ID 1: " << friendshipID_1 << endl;
		cout << "ID 2: " << friendshipID_2 << endl;

		this->prep_stmt = this->con->prepareStatement("INSERT INTO FRIENDS(FriendshipKey, UserID, FollowerID, Status) VALUES(?,?,?,?)");

		//User who sent the request 
		this->prep_stmt->setString(1, friendshipID_1);
		this->prep_stmt->setString(2, userID);
		this->prep_stmt->setString(3, followerID);
		this->prep_stmt->setInt(4, 1);
		this->prep_stmt->execute();

		//User who recieved the request 
		this->prep_stmt->setString(1, friendshipID_2);
		this->prep_stmt->setString(2, followerID);
		this->prep_stmt->setString(3, userID);
		this->prep_stmt->setInt(4, 0);
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