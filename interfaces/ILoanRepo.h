#pragma once
#include "../models/Loan.h"
#include <chrono>
#include <vector>

class ILoanRepo {
public:
	~ILoanRepo() = default;
	virtual void addLoan(const int loanId, const int userId, const int bookId, const std::chrono::year_month_day date, const std::chrono::year_month_day dueDate) = 0;
	//virtual void removeLoan() = 0;
	//virtual void extendLoan() = 0;

	virtual std::vector<Loan> listUserLoans(const int userId) = 0;
	virtual Loan* findLoanById(const int id) = 0;
	virtual void removeLoan(const int loanId) = 0;
	virtual void renewLoan(const int loanId) = 0;
};
