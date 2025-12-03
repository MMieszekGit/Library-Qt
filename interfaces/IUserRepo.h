#pragma once
#include "../models/User.h"
#include <vector>
#include <string>

class IUserRepo {
public:
	~IUserRepo() = default;
	virtual void addUser(const int userId, const std::string& userName, const std::string& userMail) = 0;
	virtual void removeUser(const std::string& userName) = 0;
	virtual std::vector<User> listAllUsers() = 0;

	virtual User* findUserById(const int userId) = 0;
	virtual User* findUserByName(const std::string& userName) = 0;
};
