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