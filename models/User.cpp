#include "User.h"
#include <iostream>

User::User(const int id, const int loanCounter, const std::string& name, const std::string& mail)
	: userId(id), loanCounter(0), userName(name), userMail(mail) {};

int User::getUserId() const { return userId; }
int User::getUserLoanCount() const { return loanCounter; }
const std::string& User::getUserName() const { return userName; }
const std::string& User::getUserMail() const { return userMail; }

void User::setUserId(const int id) { userId = id; }
void User::setUserName(const std::string& name) { userName = name; }
void User::setUserLoanCount(const int counter) { loanCounter = counter; }
void User::setUserMail(const std::string& mail) { userMail = mail; }

std::ostream& operator<<(std::ostream& os, const User& user) {
	os << "ID: " << user.getUserId() << '\n'
		<< "Username: " << user.getUserName() << '\n'
		<< "Active loans: " << user.getUserLoanCount() << '\n'
		<< "Email: " << user.getUserMail() << '\n'
		<< std::endl;
	return os;
}