#include "../lib/notificationsQueries.h"

bool addNotificationToDatabase(DATABASEMANAGER *dbMan, NOTIFICATION *data)
{
    prep_stmt = dbMan->getConnection()->prepareStatement("INSERT INTO notifications(notification_id, reciever_id, sender_id, type, content, status) VALUES(?,?,?,?,?,?)");
    
    prep_stmt->setString(1, data->getNotificationID());
    prep_stmt->setString(2, data->getRecieverID());
    prep_stmt->setString(3, data->getSenderID());
    prep_stmt->setString(4, data->getType());
    prep_stmt->setString(5, data->getContent());
    prep_stmt->setBoolean(6, data->getStatus());
    prep_stmt->execute();
    delete prep_stmt;
    return true;
}

std::unordered_map<string, NOTIFICATION*> *getNotificationCacheData(DATABASEMANAGER *dbMan)
{
    NOTIFICATION *data = nullptr;
	unordered_map<string, NOTIFICATION*> *cachemap = nullptr;
	try
	{
		cachemap = new unordered_map<string, NOTIFICATION*>;
		stmt = dbMan->getConnection()->createStatement();

		res = stmt->executeQuery("SELECT notification_id, reciever_id, sender_id, type, content, status, timestamp FROM notifications");
		while (res->next())
		{
            data = new NOTIFICATION(res->getString("notification_id"),res->getString("reciever_id"),
                                    res->getString("sender_id"), res->getString("type"), res->getString("content"), 
                                    res->getBoolean("status"), res->getString("timestamp") );
            (*cachemap)[res->getString("notification_id")] = data;
		}
	}
	catch (const sql::SQLException &e)
	{
		std::cerr << "SQLException: " << e.what() << std::endl;
	}
	delete stmt;
	delete res;
	return cachemap;
}

bool updateNotificationStatus(NOTIFICATION notification, DATABASEMANAGER *dbMan){
	try
	{
		prep_stmt = dbMan->getConnection()->prepareStatement("UPDATE notifications SET status = ? WHERE notification_id=?");
		prep_stmt->setBoolean(1, true);
		prep_stmt->setString(2, notification.getNotificationID());

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
	return false;
}