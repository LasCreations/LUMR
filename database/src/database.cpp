#include "database.h"

DATABASEMANAGER::DATABASEMANAGER() : driver(nullptr), con(nullptr)
{
    getEnvConfig("config/config.json");
    createConnection();
}

bool DATABASEMANAGER::getEnvConfig(std::string path)
{
    // Read the JSON file
    std::ifstream jsonFile(path);
    if (!jsonFile.is_open())
    {
        std::cerr << "Error opening JSON file: " << path << "\n";
        return false;
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
        return true;
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
        return false;
    }

    return false;
}

bool DATABASEMANAGER::createConnection()
{
    try
    {
        if ((this->driver = get_driver_instance()))
        {
            // std::cout << "MySQL Connector/C++ initialized successfully." << std::endl;
        }
        else
        {
            std::cout << "MySQL Connector/C++ failed to be initialized." << std::endl;
        }
        if ((this->con = this->driver->connect(this->DATABASE_URL, this->DATABASE_USER, this->DATABASE_PASSWORD)))
        {
            // std::cout << "Connected to the MySQL database successfully." << std::endl;
            this->con->setSchema(this->DATABASE_NAME);
        }
        else
        {
            std::cout << "Failed to connect to MySQL database." << std::endl;
        }
    }
    catch (sql::SQLException &e)
    {
        e.getErrorCode();
        return false;
    }
    return true;
}

sql::Connection *DATABASEMANAGER::getConnection()
{
    return this->con;
}

DATABASEMANAGER &DATABASEMANAGER::getInstance()
{
    static DATABASEMANAGER instance;
    return instance;
}
