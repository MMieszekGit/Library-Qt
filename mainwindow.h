#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../repositories/VectorBookRepo.h"
#include "../repositories/VectorUserRepo.h"
#include "../repositories/VectorLoanRepo.h"
#include "../services/LibraryService.h"
#include "../enums/QtEnums.h"

#include "showdatawindow.h"
#include "searchbookwindow.h"
#include "addbookdialog.h"
#include "usermanagedialog.h"
#include "loanmanagedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddBook_clicked();

    void on_btnListAllBooks_clicked();

    void on_btnSearchBook_clicked();

    void on_btnAddUser_clicked();

    void on_btnDeleteUser_clicked();

    void on_btnListAllUsers_clicked();

    void on_btnListAllUsersLoans_clicked();

    void on_btnBorrowBook_clicked();

    void on_btnReturnBook_clicked();

    void on_btnRenewBook_clicked();

private:
    Ui::MainWindow *ui;
    VectorBookRepo bookRepo;
    VectorUserRepo userRepo;
    VectorLoanRepo loanRepo;

    LibraryService library;
};
#endif // MAINWINDOW_H
