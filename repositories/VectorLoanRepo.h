#pragma once
#include "../interfaces/ILoanRepo.h"
#include "../models/Loan.h"
#include <string>
#include <vector>

class VectorLoanRepo : public ILoanRepo{
	std::vector<Loan> loanBase;
public:
	void addLoan(const int loanId, const int userId, const int bookId, const std::chrono::year_month_day loanDate, const std::chrono::year_month_day dueDate) override;
	std::vector<Loan> listUserLoans(const int userId) override;
	Loan* findLoanById(const int loanId) override;
	void removeLoan(const int loanId) override;
	void renewLoan(const int loanId) override;
};
