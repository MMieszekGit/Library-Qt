#include "VectorBookRepo.h"

void VectorBookRepo::addBook(const int id, const std::string& title, const std::string& author, const int year, const int copies) {
	Book new_book{ id, title, author, year, copies };
	bookBase.push_back(new_book);
}
std::vector<Book> VectorBookRepo::listAllBooks() {
	return bookBase;
}
std::vector<Book> VectorBookRepo::findBooksByAuthor(const std::string& author) {
	std::vector<Book> matchingBooks;
	for (const auto& book : bookBase) {
		if (book.getBookAuthor().find(author) != std::string::npos) {
			matchingBooks.push_back(book);
		}
	}
	return matchingBooks;
}
std::vector<Book> VectorBookRepo::findBooksByTitle(const std::string& title)  {
	std::vector<Book> matchingBooks;
	for (const auto& book : bookBase) {
		if (book.getBookTitle().find(title) != std::string::npos) {
			matchingBooks.push_back(book);
		}
	}
	return matchingBooks;
}
std::vector<Book> VectorBookRepo::findBooksByAuthorAndTitle(const std::string& title, const std::string& author) {
	std::vector<Book> matchingBooks;
	for (const auto& book : bookBase) {
		if (book.getBookTitle().find(title) != std::string::npos && book.getBookAuthor().find(author) != std::string::npos) {
			matchingBooks.push_back(book);
		}
	}
	return matchingBooks;
}
Book* VectorBookRepo::findSingleBookById(const int id) {
	for (auto& book : bookBase) {
		if (book.getBookId() == id) { return &book; }
	}
	return nullptr;
}
Book* VectorBookRepo::findSingleBookByTitle(const std::string& title) {
	for (auto& book : bookBase) {
		if (book.getBookTitle() == title) { return &book; }
	}
	return nullptr;
}