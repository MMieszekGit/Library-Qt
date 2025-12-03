#pragma once
#include <vector>
#include <string>
#include "../interfaces/IBookRepo.h"
#include "../models/Book.h"

class VectorBookRepo :public IBookRepo {
	std::vector<Book> bookBase;
public:
	void addBook(const int id, const std::string& title, const std::string& author, const int year, const int copies) override;
	std::vector<Book> listAllBooks() override;
	std::vector<Book> findBooksByAuthor(const std::string& author) override;
	std::vector<Book> findBooksByTitle(const std::string& title) override;
	std::vector<Book> findBooksByAuthorAndTitle(const std::string& title, const std::string& author) override;
	Book* findSingleBookById(const int id) override;
	Book* findSingleBookByTitle(const std::string& title) override;
};