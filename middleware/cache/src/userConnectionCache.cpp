#include "../lib/userConnectionCache.h"

USERCONNECTIONCACHE::USERCONNECTIONCACHE()
{
}

void USERCONNECTIONCACHE::preloadConnectionData(DATABASEMANAGER *dbMan, USERCACHE *userCacheData)
{
    this->cacheConnectionData = getConnectionCacheData(dbMan, userCacheData);
}

CONNECTION *USERCONNECTIONCACHE::getConnectionFromCache(string user1_ID, string user2_ID)
{
    for (const auto &pair : *(this->cacheConnectionData))
    {
        if (user1_ID == pair.second->getUser1()->getUsername() &&
            user2_ID == pair.second->getUser2()->getUsername())
        {
            return pair.second;
        }
    }
    return nullptr;
}

bool USERCONNECTIONCACHE::isConnected(string user1_ID, string user2_ID)
{
    for (const auto &pair : *(this->cacheConnectionData))
    {
        if (user1_ID == pair.second->getUser1()->getUsername() &&
            user2_ID == pair.second->getUser2()->getUsername())
        {

            return pair.second->getStatus();
        }
    }
    return false;
}

uint32_t USERCONNECTIONCACHE::followerCount(string username)
{
    uint32_t count = 0;
    for (const auto &pair : *(this->cacheConnectionData))
    {
        if (username == pair.second->getUser2()->getUsername())
        {
            if(pair.second->getStatus())  //if the person is following back
                count++;
        }
    }
    return count;
}

uint32_t USERCONNECTIONCACHE::followingCount(string username)
{
    uint32_t count = 0;
    for (const auto &pair : *(this->cacheConnectionData))
    {
        if (username == pair.second->getUser1()->getUsername())
        {
            if(pair.second->getStatus())  //if the person is following back
                count++;
        }
    }
    return count;
}