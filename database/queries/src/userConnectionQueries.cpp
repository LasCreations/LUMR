#include "../lib/userConnectionQueries.h"

bool addConnectionToDatabase(DATABASEMANAGER *dbMan, CONNECTION *data){
    try
	{
		prep_stmt = dbMan->getConnection()->prepareStatement("INSERT INTO connections(user_1_id, user_2_id, status) VALUES(?,?,?)");
		
        prep_stmt->setString(1, data->getUser1()->getUsername());
		prep_stmt->setString(2, data->getUser2()->getUsername());
        prep_stmt->setBoolean(3, data->getStatus());

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