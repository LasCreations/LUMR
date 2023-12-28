#include "../lib/userConnectionQueries.h"

bool addConnectionToDatabase(DATABASEMANAGER *dbMan, CONNECTION *data){
    try
	{
		prep_stmt = dbMan->getConnection()->prepareStatement("INSERT INTO connections(user_1_id, user_2_id, user1_status, user2_status) VALUES(?,?,?,?)");
		
        prep_stmt->setString(1, data->getUser1()->getUsername());
		prep_stmt->setString(2, data->getUser2()->getUsername());
		prep_stmt->setBoolean(3, data->getUser1Status());
		prep_stmt->setBoolean(4, data->getUser2Status());
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

std::unordered_map<string, CONNECTION *> *getConnectionCacheData(DATABASEMANAGER *dbMan, USERCACHE *userCacheData){	
	unordered_map<string, CONNECTION *> *connectionmap = nullptr;
	try
	{
		connectionmap = new unordered_map<string, CONNECTION *>;

		stmt = dbMan->getConnection()->createStatement();
		
		res = stmt->executeQuery("SELECT * FROM connections");
		while (res->next()){
			USER *user1 = userCacheData->getUserFromCache(res->getString("user_1_id"));
			USER *user2 = userCacheData->getUserFromCache(res->getString("user_2_id"));
			CONNECTION *userCon = new CONNECTION(user1, user2, res->getBoolean("user1_status"), res->getBoolean("user2_status"));
			(*connectionmap)[generateRandomCode(13)] = userCon;
		}
	}
	catch (const sql::SQLException &e)
	{
		std::cerr << "SQLException: " << e.what() << std::endl;
	}
	delete stmt;
	delete res;
	return connectionmap;
}