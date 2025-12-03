#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(LibraryService* service, QtEnums::SearchBookMode mode,  QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SearchDialog)
    , library(service)
    , mode(mode)
{
    ui->setupUi(this);
    this->setWindowTitle("Search Book");

    switch (mode) {
    case QtEnums::SearchBookMode::Title:
        ui->labelTitle->show();
        ui->lineEditTitle->show();
        ui->labelAuthor->hide();
        ui->lineEditAuthor->hide();
        break;

    case QtEnums::SearchBookMode::Author:
        ui->labelTitle->hide();
        ui->lineEditTitle->hide();
        ui->labelAuthor->show();
        ui->lineEditAuthor->show();
        break;

    case QtEnums::SearchBookMode::Both:
        ui->labelTitle->show();
        ui->lineEditTitle->show();
        ui->labelAuthor->show();
        ui->lineEditAuthor->show();
    }
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_buttonBox_accepted()
{
    std::string title, author;
    std::vector<Book> books;

    switch(mode) {
        case QtEnums::SearchBookMode::Title:
            if (ui->lineEditTitle->text().trimmed().isEmpty()) {
                QMessageBox::critical(this, "Error",  "Title field cannot be empty!");
                return;
            }
            title = ui->lineEditTitle->text().trimmed().toStdString();
            books = library->findMatchingBooks(title, "");
            break;
        case QtEnums::SearchBookMode::Author:
            if (ui->lineEditAuthor->text().trimmed().isEmpty()) {
                QMessageBox::critical(this, "Error",  "Author field cannot be empty!");
                return;
            }
            author = ui->lineEditAuthor->text().trimmed().toStdString();
            books = library->findMatchingBooks("", author);
            break;
        case QtEnums::SearchBookMode::Both:
            if (ui->lineEditTitle->text().trimmed().isEmpty()) {
                QMessageBox::critical(this, "Error",  "Title field cannot be empty!");
                return;
            }
            if (ui->lineEditAuthor->text().trimmed().isEmpty()) {
                QMessageBox::critical(this, "Error",  "Author field cannot be empty!");
                return;
            }
            title = ui->lineEditTitle->text().trimmed().toStdString();
            author = ui->lineEditAuthor->text().trimmed().toStdString();
            books = library->findMatchingBooks(title, author);
            break;
    }

    std::vector<std::string> tableHeaders = {"ID", "Title", "Author", "Release Year", "Available Copies"};
    std::vector<std::vector<QString>> booksData;

    for (auto& book : books) {
        booksData.push_back({
            QString::number(book.getBookId()),
            QString::fromStdString(book.getBookTitle()),
            QString::fromStdString(book.getBookAuthor()),
            QString::number(book.getBookYear()),
            QString::number(book.getBookCopies())
        });
    }

    ShowDataWindow* win = new ShowDataWindow(tableHeaders, booksData);
    win->setAttribute(Qt::WA_DeleteOnClose);
    win->show();
}

