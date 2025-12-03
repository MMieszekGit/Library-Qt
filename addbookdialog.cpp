#include "addbookdialog.h"
#include "ui_addbookdialog.h"

#include <QString>
#include <QMessageBox>
#include <QLineEdit>

AddBookDialog::AddBookDialog(LibraryService* service, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddBookDialog)
    , library(service)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Book");
}

AddBookDialog::~AddBookDialog()
{
    delete ui;
}

void AddBookDialog::on_buttonBox_accepted()
{
    QList<QLineEdit*> edits = this->findChildren<QLineEdit*>();
    for (QLineEdit* edit : edits) {
        if (edit->text().trimmed().isEmpty()) {
            QMessageBox::critical(this, "Error",  "Fields cannot be empty!");
            return;
        }
    }
    QString bookId = ui->lineEditBookId->text().trimmed();
    if (!verifyIntInput(bookId)) {
        QMessageBox::critical(this, "Error", "Book ID out of range or not a number!");
        return;
    }
    QString bookYear = ui->lineEditBookYear->text().trimmed();
    if (!verifyIntInput(bookYear, 0, 2026)) {
        QMessageBox::critical(this, "Error", "Book Year out of range or not a number!");
        return;
    }
    QString bookCopies = ui->lineEditBookCopies->text().trimmed();
    if (!verifyIntInput(bookCopies, 1, 100)) {
        QMessageBox::critical(this, "Error", "Book Copies out of range or not a number!");
        return;
    }
    std::string bookTitle = ui->lineEditBookTitle->text().trimmed().toStdString();
    std::string bookAuthor = ui->lineEditBookAuthor->text().trimmed().toStdString();

    Library::AddResult result = library->addBook(
        bookId.toInt(), bookTitle, bookAuthor, bookYear.toInt(), bookCopies.toInt()
        );
    switch(result) {
    case Library::AddResult::Success:
        QMessageBox::information(this, "Success", "Book added!");
        break;
    case Library::AddResult::DuplicatedId:
        QMessageBox::critical(this, "Error", "Duplicated Book ID!" );
        break;
    case Library::AddResult::DuplicatedTitle:
        QMessageBox::critical(this, "Error", "Duplicated Book Title!");
        break;
    }
}

