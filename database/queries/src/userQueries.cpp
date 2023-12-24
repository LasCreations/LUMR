#include "../lib/userQueries.h"

bool addDataToUserTable(USER *data)
{
	try
	{
		prep_stmt = dbMan->getConnection()->prepareStatement("INSERT INTO users(username, token, password) VALUES(?,?,?)");
		prep_stmt->setString(1, data->getUsername());
		prep_stmt->setString(2, data->getToken());
		prep_stmt->setString(3, data->getPassword());

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

bool addDataToUserProfileTable(USER *data)
{
	try
	{
		prep_stmt = dbMan->getConnection()->prepareStatement("INSERT INTO user_profile(profile_id, user_id, email, avatar_url, bio, gender, status) VALUES(?,?,?,?,?,?,?)");
		prep_stmt->setString(1, data->getProfile()->getProfileID());
		prep_stmt->setString(2, data->getProfile()->getUserID());
		prep_stmt->setString(3, data->getProfile()->getEmail());
		prep_stmt->setString(4, data->getProfile()->getAvatarURL());
		prep_stmt->setString(5, data->getProfile()->getBio());
		prep_stmt->setString(6, data->getProfile()->getGender());
		prep_stmt->setBoolean(7, data->getProfile()->getStatus());

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

std::unordered_map<string, USER *> *getUsersCacheData()
{
	USER *data = nullptr;
	PROFILE *profile = nullptr;
	vector<PROFILE *> *userProfiles = nullptr;
	unordered_map<string, USER *> *cachemap = nullptr;
	try
	{
		cachemap = new std::unordered_map<std::string, USER *>;
		userProfiles = new std::vector<PROFILE*>;
		stmt = dbMan->getConnection()->createStatement();

		res = stmt->executeQuery("SELECT profile_id, user_id, email, avatar_url, bio, gender, status FROM user_profile");
		while (res->next())
		{
			profile = new PROFILE(res->getString("profile_id"), res->getString("user_id"),
								  res->getString("email"), res->getString("avatar_url"),
								  res->getString("bio"), res->getString("gender"),
								  res->getBoolean("status"));
			userProfiles->push_back(profile);
		}

		if (profile != nullptr)
		{
			res = stmt->executeQuery("SELECT username, token, password FROM users");
			while (res->next())
			{
				for (const auto& element : *(userProfiles)) {
					if(res->getString("username") == element->getUserID()){
						data = new USER(res->getString("username"),res->getString("password"), res->getString("token"),element);
						(*cachemap)[res->getString("username")] = data;
					}
				}
			}
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

bool updateToken(USER *data, string token){
	try
	{
		prep_stmt = dbMan->getConnection()->prepareStatement("UPDATE users SET token = ? WHERE token=?");
		prep_stmt->setString(1, token);
		prep_stmt->setString(2, data->getToken());

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


bool updateUserProfile(USER *data){
	try
	{
		prep_stmt = dbMan->getConnection()->prepareStatement("UPDATE user_profile SET email = ? WHERE user_id = ?");
		prep_stmt->setString(1, data->getProfile()->getEmail());
		prep_stmt->setString(2, data->getUsername());
		prep_stmt->execute();

		prep_stmt = dbMan->getConnection()->prepareStatement("UPDATE user_profile SET bio = ? WHERE user_id = ?");
		prep_stmt->setString(1, data->getProfile()->getBio());
		prep_stmt->setString(2, data->getUsername());
		prep_stmt->execute();

		prep_stmt = dbMan->getConnection()->prepareStatement("UPDATE user_profile SET gender = ? WHERE user_id = ?");
		prep_stmt->setString(1, data->getProfile()->getGender());
		prep_stmt->setString(2, data->getUsername());
		prep_stmt->execute();

		prep_stmt = dbMan->getConnection()->prepareStatement("UPDATE user_profile SET avatar_url = ? WHERE user_id = ?");
		prep_stmt->setString(1, data->getProfile()->getAvatarURL());
		prep_stmt->setString(2, data->getUsername());
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