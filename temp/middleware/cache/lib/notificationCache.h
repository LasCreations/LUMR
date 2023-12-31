#ifndef NOTIFICATION_CACHE_H
#define NOTIFICATION_CACHE_H

#include "../../../utils/common.h"
#include "../../../database/queries/lib/notificationsQueries.h"


class NOTIFICATIONCACHE{

    private:
        std::unordered_map<string, NOTIFICATION*> *cacheData;
    public:
        NOTIFICATIONCACHE();
        void preloadNotificationData(DATABASEMANAGER *dbMan);
        vector <NOTIFICATION> getNotifications(string username);
        bool updateNotificationStatus(NOTIFICATION notification);
        bool hasNewNotification(string username);
        void addNotificationToCache(NOTIFICATION *notification);
};

#endif