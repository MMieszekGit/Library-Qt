#pragma once
#include <chrono>
#include <iostream>

class Loan {
	int loanId;
	int userId;
	int bookId;
	std::chrono::year_month_day loanDate;
	std::chrono::year_month_day loanDueDate;
public:
	Loan(const int lid, int uid, int bid, std::chrono::year_month_day date, std::chrono::year_month_day dueDate);

	int getLoanId() const;
	int getUserId() const;
	int getBookId() const;
	std::chrono::year_month_day getLoanDate() const;
	std::chrono::year_month_day getLoanDueDate () const;

	void setDueDate(std::chrono::year_month_day newDate);
};

std::ostream& operator<<(std::ostream& os, const std::chrono::year_month_day& ymd);

std::ostream& operator<<(std::ostream& os, const Loan& loan);

