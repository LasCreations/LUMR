#include "../lib/notificationCache.h"

NOTIFICATIONCACHE::NOTIFICATIONCACHE(){

}
void NOTIFICATIONCACHE::preloadNotificationData(DATABASEMANAGER *dbMan){
    this->cacheData = getNotificationCacheData(dbMan);
}

vector <NOTIFICATION> NOTIFICATIONCACHE::getNotifications(string username){
    vector<NOTIFICATION> notifications;
    for (const auto &pair : *(this->cacheData))
    {
        if (username == pair.second->getRecieverID())
            notifications.push_back((*pair.second));
    }
    return notifications;
}

bool NOTIFICATIONCACHE::updateNotificationStatus(NOTIFICATION notification){
    auto data = this->cacheData->find(notification.getNotificationID());
    if (data != this->cacheData->end()) {
        (*data).second->setStatus(true);
        return true;
    } else {
        return false;
    }
}

bool NOTIFICATIONCACHE::hasNewNotification(string username){
    for (const auto &pair : *(this->cacheData))
    {
        if (username == pair.second->getRecieverID() && !pair.second->getStatus())
            return true;
    }
    return false;
}

void NOTIFICATIONCACHE::addNotificationToCache(NOTIFICATION *notification){
    this->cacheData->insert({ notification->getNotificationID(), notification });
}