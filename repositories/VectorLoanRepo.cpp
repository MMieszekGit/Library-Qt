#include "VectorLoanRepo.h"

void VectorLoanRepo::addLoan(const int loanId, const int userId, const int bookId, const std::chrono::year_month_day loanDate, const std::chrono::year_month_day dueDate) {
	Loan new_loan = { loanId, userId, bookId, loanDate, dueDate };
	loanBase.push_back(new_loan);
}
std::vector<Loan> VectorLoanRepo::listUserLoans(const int userId) {
	std::vector<Loan> userLoans;
	for (auto& loan : loanBase) {
		if (loan.getUserId() == userId) { userLoans.push_back(loan); }
	}
	return userLoans;
}
Loan* VectorLoanRepo::findLoanById(const int loanId) {
	for (auto& loan : loanBase) {
		if (loan.getLoanId() == loanId) { return &loan; }
	}
	return nullptr;
}
void VectorLoanRepo::removeLoan(const int loanId) {
	for (auto ptr = loanBase.begin(); ptr != loanBase.end(); ptr++) {
		if (ptr->getLoanId() == loanId) {
			loanBase.erase(ptr);
			break;
		}
	}
}
void VectorLoanRepo::renewLoan(const int loanId) {
	for (auto& loan : loanBase) {
		if (loan.getLoanId() == loanId) {
			auto days = std::chrono::sys_days(loan.getLoanDueDate());
			loan.setDueDate(std::chrono::year_month_day{ days + std::chrono::days{ 30 } });
			return;
		}
	}
}
