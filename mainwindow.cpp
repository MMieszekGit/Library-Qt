#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , bookRepo()
    , userRepo()
    , loanRepo()
    , library(bookRepo, userRepo, loanRepo)
{
    ui->setupUi(this);
    this->setWindowTitle("Library QT");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddBook_clicked()
{
    auto* dialog = new AddBookDialog(&library, this);
    dialog->exec();
}

void MainWindow::on_btnListAllBooks_clicked()
{
    std::vector<Book> books = library.listAllBooks();

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

    auto* window = new ShowDataWindow(tableHeaders, booksData);
    window->show();
}

void MainWindow::on_btnSearchBook_clicked()
{
    auto* window = new SearchBookWindow(&library);
    window->show();
}


void MainWindow::on_btnAddUser_clicked()
{
    auto* dialog = new UserManageDialog(&library, QtEnums::UserManageMode::AddUser, this);
    dialog->exec();
}


void MainWindow::on_btnDeleteUser_clicked()
{
    auto* dialog = new UserManageDialog(&library, QtEnums::UserManageMode::DeleteUser, this);
    dialog->exec();
}


void MainWindow::on_btnListAllUsers_clicked()
{
    std::vector<User> users = library.listAllUsers();
    std::vector<std::string> tableHeaders = {"ID", "Username", "E-mail"};
    std::vector<std::vector<QString>> usersData;

    for (auto& user : users) {
        usersData.push_back({
            QString::number(user.getUserId()),
            QString::fromStdString(user.getUserName()),
            QString::fromStdString((user.getUserMail()))
        });
    }

    auto* window = new ShowDataWindow(tableHeaders, usersData);
    window->show();
}


void MainWindow::on_btnListAllUsersLoans_clicked()
{
    auto* dialog = new LoanManageDialog(&library, QtEnums::LoanManageMode::ListUsersLoans, this);
    dialog->exec();
}


void MainWindow::on_btnBorrowBook_clicked()
{
    auto* dialog = new LoanManageDialog(&library, QtEnums::LoanManageMode::AddLoan, this);
    dialog->exec();
}


void MainWindow::on_btnReturnBook_clicked()
{
    auto* dialog = new LoanManageDialog(&library, QtEnums::LoanManageMode::RemoveLoan, this);
    dialog->exec();
}


void MainWindow::on_btnRenewBook_clicked()
{
    auto* dialog = new LoanManageDialog(&library, QtEnums::LoanManageMode::RenewLoan, this);
    dialog->exec();
}

