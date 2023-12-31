#ifndef NOTIFICATION_QUERIES_H
#define NOTIFICATION_QUERIES_H

#include"../../connection/lib/DBManager.h"

bool addNotificationToDatabase(DATABASEMANAGER *dbMan, NOTIFICATION *data);

std::unordered_map<string, NOTIFICATION*> *getNotificationCacheData(DATABASEMANAGER *dbMan);

bool updateNotificationStatus(NOTIFICATION notification, DATABASEMANAGER *dbMan);
#endif