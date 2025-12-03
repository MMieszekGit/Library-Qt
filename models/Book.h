#pragma once
#include <iostream>
#include <string>

class Book {
	int bookId;
	std::string bookTitle;
	std::string bookAuthor;
	int bookYear;
	int bookCopies;
public:
	Book(const int id, const std::string& title, const std::string& author, const int year, const int copies);

	int getBookId() const;
	std::string getBookTitle() const;
	std::string getBookAuthor() const;
	int getBookYear() const;
	int getBookCopies() const;

	void setBookId(const int id);
	void setBookTitle(const std::string& title);
	void setBookAuthor(const std::string& author);
	void setBookDate(const int year);
	void setBookCopies(const int copies);
};

std::ostream& operator<<(std::ostream& os, const Book& book);