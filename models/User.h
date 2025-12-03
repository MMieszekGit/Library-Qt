#pragma once
#include <string>
#include <iostream>

class User {
	int userId, loanCounter;
	std::string userName;
	std::string userMail;

public:
	User(const int id, const int loanCounter, const std::string& name, const std::string& mail);

	int getUserId() const;
	int getUserLoanCount() const;
	const std::string& getUserName() const;
	const std::string& getUserMail() const;

	void setUserId(const int id);
	void setUserName(const std::string& name);
	void setUserMail(const std::string& mail);
	void setUserLoanCount(const int counter);
};

std::ostream& operator<<(std::ostream& os, const User& user);