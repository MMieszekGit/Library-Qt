#include "LibraryService.h"

LibraryService::LibraryService(IBookRepo& bookRepo, IUserRepo& userRepo, ILoanRepo& loanRepo) : bookRepo(&bookRepo), userRepo(&userRepo), loanRepo(&loanRepo){}

Library::AddResult LibraryService::addBook(const int bookId, const std::string& bookTitle, const std::string& bookAuthor, const int bookYear, const int bookCopies) {
	if (bookRepo->findSingleBookById(bookId) != nullptr) { return Library::AddResult::DuplicatedId; }
	if (bookRepo->findSingleBookByTitle(bookTitle) != nullptr) { return Library::AddResult::DuplicatedTitle; }
	bookRepo->addBook(bookId, bookTitle, bookAuthor, bookYear, bookCopies);
	return  Library::AddResult::Success;
}
std::vector<Book> LibraryService::listAllBooks() { return bookRepo->listAllBooks(); }
std::vector<Book> LibraryService::findMatchingBooks(const std::string& bookTitle, const std::string& bookAuthor) {
	if (!bookTitle.empty() && !bookAuthor.empty()) { return bookRepo->findBooksByAuthorAndTitle(bookTitle, bookAuthor); }
	if (!bookTitle.empty() && bookAuthor.empty()) { return bookRepo->findBooksByTitle(bookTitle); }
	if (bookTitle.empty() && !bookAuthor.empty()) { return bookRepo->findBooksByAuthor(bookAuthor); }
	return {};
}
Library::AddResult LibraryService::addUser(const int id, const std::string& name, const std::string& mail) {
	if (userRepo->findUserById(id) != nullptr) { return Library::AddResult::DuplicatedId; }
	if (userRepo->findUserByName(name) != nullptr) { return Library::AddResult::DuplicatedTitle; }
	userRepo->addUser(id, name, mail);
	return Library::AddResult::Success;
}
Library::RemoveUserResult LibraryService::removeUser(const std::string& userName) {
	User* user = userRepo->findUserByName(userName);
	if (user == nullptr) { return Library::RemoveUserResult::InvalidUserName; }
	if (user->getUserLoanCount() > 0) { return Library::RemoveUserResult::HasActiveLoans; }
	userRepo->removeUser(userName);
	return Library::RemoveUserResult::Success;
}
Library::RemoveLoanResult LibraryService::removeLoan(const int loanId) {
	Loan* loan = loanRepo->findLoanById(loanId);
	if (loan == nullptr) { return Library::RemoveLoanResult::InvalidLoanId; }
	User* user = userRepo->findUserById(loan->getUserId());
	user->setUserLoanCount(user->getUserLoanCount() - 1);
	Book* book = bookRepo->findSingleBookById(loan->getBookId());
	book->setBookCopies(book->getBookCopies() + 1);
	loanRepo->removeLoan(loanId);
	return Library::RemoveLoanResult::Success;
}
std::vector<User> LibraryService::listAllUsers() { return userRepo->listAllUsers(); }
Library::AddLoanResult LibraryService::addLoan(const int loanId, const int userId, const int bookId, std::chrono::year_month_day loanDate, std::chrono::year_month_day loanDueDate) {
	if (loanRepo->findLoanById(loanId) != nullptr) { return Library::AddLoanResult::InvalidLoanId; }
	Book* book = bookRepo->findSingleBookById(bookId);
	if (book == nullptr) { return Library::AddLoanResult::InvalidBookId; }
	if (book->getBookCopies() < 1) { return Library::AddLoanResult::NoAvailableBook; }
	User* user = userRepo->findUserById(userId);
	if (user == nullptr) { return Library::AddLoanResult::InvalidUserId; }
	if (user->getUserLoanCount() > 4) { return Library::AddLoanResult::NoAvailableUserLoanSlot; }

	std::vector<Loan> userLoans = loanRepo->listUserLoans(userId);
	for (auto& loan : userLoans) {
		if (loan.getBookId() == bookId) { return Library::AddLoanResult::HasBorrowedBook; }
	}

	loanRepo->addLoan(loanId, userId, bookId, loanDate, loanDueDate);
	book->setBookCopies(book->getBookCopies() - 1);
	user->setUserLoanCount(user->getUserLoanCount() + 1);
	return Library::AddLoanResult::Success;
}
std::vector<Loan> LibraryService::listUserLoans(const int userId) {
	if (userRepo->findUserById(userId) == nullptr) { return {}; }
	return loanRepo->listUserLoans(userId);
}
Library::RenewLoanResult LibraryService::renewLoan(const int loanId) {
	if (loanRepo->findLoanById(loanId) == nullptr) { return Library::RenewLoanResult::InvalidLoanId; }
	loanRepo->renewLoan(loanId);
	return Library::RenewLoanResult::Success;
}
