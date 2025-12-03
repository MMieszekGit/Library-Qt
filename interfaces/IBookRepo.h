#pragma once
#include "../models/Book.h"
#include <vector>
#include <string>

class IBookRepo {
public:
	~IBookRepo() = default;
	virtual void addBook(const int id, const std::string& title, const std::string& author, const int year, const int copies) = 0;
	virtual std::vector<Book> listAllBooks() = 0;

	virtual std::vector<Book> findBooksByAuthor(const std::string& author) = 0;
	virtual std::vector<Book> findBooksByTitle(const std::string& title) = 0;
	virtual std::vector<Book> findBooksByAuthorAndTitle(const std::string& title, const std::string& author) = 0;

	virtual Book* findSingleBookById(const int id) = 0;
	virtual Book* findSingleBookByTitle(const std::string& title) = 0;
};