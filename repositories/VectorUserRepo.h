#pragma once
#include "../interfaces/IUserRepo.h"
#include "../models/User.h"
#include <vector>
#include <string>

class VectorUserRepo :public IUserRepo {
	std::vector<User> userBase;

public:
	void addUser(const int id, const std::string& name, const std::string& mail) override;
	void removeUser(const std::string& name) override;
	std::vector<User> listAllUsers() override;
	User* findUserById(const int id) override;
	User* findUserByName(const std::string& name) override;
};
