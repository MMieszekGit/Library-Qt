#include "Book.h"

Book::Book(const int id, const std::string& title, const std::string& author, const int year, const int copies) :
	bookId(id), bookTitle(title), bookAuthor(author), bookYear(year), bookCopies(copies) {};

int Book::getBookId() const { return bookId; }
std::string Book::getBookTitle() const { return bookTitle; }
std::string Book::getBookAuthor() const { return bookAuthor;  }
int Book::getBookYear() const { return bookYear; }
int Book::getBookCopies() const { return bookCopies; }

void Book::setBookId(const int id) { bookId = id; }
void Book::setBookTitle(const std::string& title) { bookTitle = title; }
void Book::setBookAuthor(const std::string& author)  { bookAuthor = author; }
void Book::setBookDate(const int year)  { bookYear = year; }
void Book::setBookCopies(const int copies) { bookCopies = copies; }

std::ostream& operator<<(std::ostream& os, const Book& book) {
	os << "ID: " << book.getBookId() << '\n'
		<< "Title: " << book.getBookTitle() << '\n'
		<< "Author: " << book.getBookAuthor() << '\n'
		<< "Release Year: " << book.getBookYear() << '\n'
		<< "Available copies: " << book.getBookCopies() << '\n'
		<< std::endl;
	return os;
}