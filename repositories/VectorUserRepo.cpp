#include "VectorUserRepo.h"

void VectorUserRepo::addUser(const int id, const std::string& name, const std::string& mail) {
	User new_user{ id, 0, name, mail };
	userBase.push_back(new_user);
}
void VectorUserRepo::removeUser(const std::string& name) {
	for (auto ptr = userBase.begin(); ptr != userBase.end(); ptr++) {
		if (ptr->getUserName() == name) {
			userBase.erase(ptr);
			break;
		}
	}
}
std::vector<User> VectorUserRepo::listAllUsers() { return userBase; }
User* VectorUserRepo::findUserById(const int id) {
	for (auto& user : userBase) {
		if (user.getUserId() == id) { return &user; }
	}
	return nullptr;
}
User* VectorUserRepo::findUserByName(const std::string& name) {
	for (auto& user : userBase) {
		if (user.getUserName() == name) { return &user; }
	}
	return nullptr;
}
