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

bool USERCONNECTIONCACHE::isFollowing(string user1_ID, string user2_ID)
{
    for (const auto &pair : *(this->cacheConnectionData))
    {
        if (user1_ID == pair.second->getUser1()->getUsername() &&
            user2_ID == pair.second->getUser2()->getUsername())
        {
            return pair.second->getUser1Status();
        }

        if (user1_ID == pair.second->getUser2()->getUsername() &&
            user2_ID == pair.second->getUser1()->getUsername())
        {
            return pair.second->getUser2Status();
        }
    }
    return false;
}

uint32_t USERCONNECTIONCACHE::followerCount(string username)
{
    uint32_t count = 0;
    for (const auto &pair : *(this->cacheConnectionData))
    {
        if (username == pair.second->getUser1()->getUsername() && pair.second->getUser2Status())
            count++;

        if (username == pair.second->getUser2()->getUsername() && pair.second->getUser1Status())
            count++;
    }
    return count;
}

uint32_t USERCONNECTIONCACHE::followingCount(string username)
{
    uint32_t count = 0;
    for (const auto &pair : *(this->cacheConnectionData))
    {
        if (username == pair.second->getUser1()->getUsername() && pair.second->getUser1Status())
            count++;

        if (username == pair.second->getUser2()->getUsername() && pair.second->getUser2Status())
            count++;
    }
    return count;
}

vector<CONNECTION> USERCONNECTIONCACHE::getFollowerConnections(string username)
{
    vector<CONNECTION> followers;
    for (const auto &pair : *(this->cacheConnectionData))
    {

        if (username == pair.second->getUser1()->getUsername() && pair.second->getUser2Status())
            followers.push_back((*pair.second));

        if (username == pair.second->getUser2()->getUsername() && pair.second->getUser1Status())
            followers.push_back((*pair.second));

    }
    return followers;
}

vector<CONNECTION> USERCONNECTIONCACHE::getFollowingConnections(string username)
{
    vector<CONNECTION> following;
    for (const auto &pair : *(this->cacheConnectionData))
    {
        if (username == pair.second->getUser1()->getUsername() && pair.second->getUser1Status())
            following.push_back((*pair.second));

        if (username == pair.second->getUser2()->getUsername() && pair.second->getUser2Status())
            following.push_back((*pair.second));
    }
    return following;
}

USER USERCONNECTIONCACHE::getConnectionUser(string username, CONNECTION con){
    if (username == con.getUser1()->getUsername())
            return con.getUser2();

    if (username == con.getUser2()->getUsername())
            return con.getUser1();
    return NULL;
}