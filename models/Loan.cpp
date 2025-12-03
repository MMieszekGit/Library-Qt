#include "Loan.h"
#include <chrono>
#include <iostream>

Loan::Loan(const int lid, int uid, int bid, std::chrono::year_month_day date, std::chrono::year_month_day dueDate) :
	loanId(lid), userId(uid), bookId(bid), loanDate(date), loanDueDate(dueDate) {
};

int Loan::getLoanId() const { return loanId; }
int Loan::getUserId() const { return userId; }
int Loan::getBookId() const { return bookId; }
std::chrono::year_month_day Loan::getLoanDate() const { return loanDate; }
std::chrono::year_month_day Loan::getLoanDueDate() const { return loanDueDate; }

void Loan::setDueDate(std::chrono::year_month_day newDate) { loanDueDate = newDate; }

std::ostream& operator<<(std::ostream& os, const std::chrono::year_month_day& ymd) {
	os << int(ymd.year()) << "-" << unsigned(ymd.month()) << "-" << unsigned(ymd.day());
	return os;
}

std::ostream& operator<<(std::ostream& os, const Loan& loan) {
	os << "Loan ID: " << loan.getLoanId() << '\n'
		<< "User ID: " << loan.getUserId() << '\n'
		<< "Book ID: " << loan.getBookId() << '\n'
		<< "Loan date: " << loan.getLoanDate() << '\n'
		<< "Return date: " << loan.getLoanDueDate() << '\n'
		<< std::endl;
	return os;
}