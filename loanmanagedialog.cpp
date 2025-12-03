#include "loanmanagedialog.h"
#include "ui_loanmanagedialog.h"

LoanManageDialog::LoanManageDialog(LibraryService* service, QtEnums::LoanManageMode mode, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoanManageDialog)
    , library(service)
    , mode(mode)
{
    ui->setupUi(this);

    switch(mode) {
    case QtEnums::LoanManageMode::AddLoan:
        this->setWindowTitle("Borrow Book");
        ui->labelLoanId->show();
        ui->labelBookId->show();
        ui->labelUserId->show();
        ui->lineEditLoanId->show();
        ui->lineEditBookId->show();
        ui->lineEditUserId->show();
        break;
    case QtEnums::LoanManageMode::RemoveLoan:
        this->setWindowTitle("Return Book");
        ui->labelLoanId->show();
        ui->labelBookId->hide();
        ui->labelUserId->hide();
        ui->lineEditLoanId->show();
        ui->lineEditBookId->hide();
        ui->lineEditUserId->hide();
        break;
    case QtEnums::LoanManageMode::ListUsersLoans:
        this->setWindowTitle("List Loans");
        ui->labelLoanId->hide();
        ui->labelBookId->hide();
        ui->labelUserId->show();
        ui->lineEditLoanId->hide();
        ui->lineEditBookId->hide();
        ui->lineEditUserId->show();
        break;
    case QtEnums::LoanManageMode::RenewLoan:
        this->setWindowTitle("Renew Book");
        ui->labelLoanId->show();
        ui->labelBookId->hide();
        ui->labelUserId->hide();
        ui->lineEditLoanId->show();
        ui->lineEditBookId->hide();
        ui->lineEditUserId->hide();
        break;
    }
}

LoanManageDialog::~LoanManageDialog()
{
    delete ui;
}

void LoanManageDialog::on_buttonBox_accepted()
{
    switch(mode) {
    case QtEnums::LoanManageMode::AddLoan: {
        QList<QLineEdit*> edits = this->findChildren<QLineEdit*>();
        for (QLineEdit* edit : edits) {
            if (edit->text().trimmed().isEmpty()) {
                QMessageBox::critical(this, "Error",  "Fields cannot be empty!");
                return;
            }
        }
        QString loanId = ui->lineEditLoanId->text().trimmed();
        if (!verifyIntInput(loanId)) {
            QMessageBox::critical(this, "Error", "Loan ID out of range or not a number!");
            return;
        }
        QString bookId = ui->lineEditBookId->text().trimmed();
        if (!verifyIntInput(bookId)) {
            QMessageBox::critical(this, "Error", "Book ID out of range or not a number!");
            return;
        }
        QString userId = ui->lineEditUserId->text().trimmed();
        if (!verifyIntInput(userId)) {
            QMessageBox::critical(this, "Error", "User ID out of range or not a number!");
            return;
        }

        auto date = std::chrono::system_clock::now();
        auto days = floor<std::chrono::days>(date);
        std::chrono::year_month_day loanDate{ days };
        std::chrono::year_month_day dueDate{ days + std::chrono::days{ 30 } };
        Library::AddLoanResult result = library->addLoan(
                                            loanId.toInt(),
                                            userId.toInt(),
                                            bookId.toInt(),
                                            loanDate,
                                            dueDate);

        switch(result) {
        case Library::AddLoanResult::Success:
            QMessageBox::information(this, "Success", "Book borrowed!");
            return;
        case Library::AddLoanResult::InvalidLoanId:
            QMessageBox::critical(this, "Error", "Loan with given ID already exists!");
            return;
        case Library::AddLoanResult::InvalidBookId:
            QMessageBox::critical(this, "Error", "Book with given ID doesn't exists!");
            return;
        case Library::AddLoanResult::InvalidUserId:
            QMessageBox::critical(this, "Error", "User with given ID doeasn't exists!");
            return;
        case Library::AddLoanResult::NoAvailableUserLoanSlot:
            QMessageBox::critical(this, "Error", "User has reached loan limit of 5!");
            return;
        case Library::AddLoanResult::NoAvailableBook:
            QMessageBox::critical(this, "Error", "No available copies of given book left!");
            return;
        case Library::AddLoanResult::HasBorrowedBook:
            QMessageBox::critical(this, "Error", "User has already borrowed given book!");
            return;
        }
    }
    case QtEnums::LoanManageMode::RemoveLoan: {
        if (ui->lineEditLoanId->text().trimmed().isEmpty()) {
            QMessageBox::critical(this, "Error", "Loan ID field cannot be empty!");
            return;
        }
        QString loanId = ui->lineEditLoanId->text().trimmed();
        if (!verifyIntInput(loanId)) {
            QMessageBox::critical(this, "Error", "Loan ID value not a number or out of range!");
            return;
        }
        Library::RemoveLoanResult result = library->removeLoan(loanId.toInt());

        switch(result) {
        case Library::RemoveLoanResult::Success:
            QMessageBox::information(this, "Success", "Book returned!");
            return;
        case Library::RemoveLoanResult::InvalidLoanId:
            QMessageBox::critical(this, "Error", "Loan with given ID doesn't exist!");
            return;
        }
    }
    case QtEnums::LoanManageMode::ListUsersLoans: {
        if (ui->lineEditUserId->text().trimmed().isEmpty()) {
            QMessageBox::critical(this, "Error", "User ID field cannot be empty!");
            return;
        }

        QString userId = ui->lineEditUserId->text().trimmed();
        std::vector<Loan> userLoans = library->listUserLoans(userId.toInt());
        std::vector<std::string> tableHeaders = {"Loan ID", "Book ID", "Loan Date", "Due Date" };

        std::vector<std::vector<QString>> userLoansData;
        for (auto& loan : userLoans) {
            userLoansData.push_back({
                QString::number(loan.getLoanId()),
                QString::number(loan.getBookId()),
                chronoToQDate(loan.getLoanDate()),
                chronoToQDate(loan.getLoanDueDate())
            });
        }

        auto* window = new ShowDataWindow(tableHeaders, userLoansData);
        window->show();
        break;
    }
    case QtEnums::LoanManageMode::RenewLoan: {
        if (ui->lineEditLoanId->text().trimmed().isEmpty()) {
            QMessageBox::critical(this, "Error", "Loan ID field cannot be empty!");
            return;
        }
        QString loanId = ui->lineEditLoanId->text().trimmed();
        if (!verifyIntInput(loanId)) {
            QMessageBox::critical(this, "Error", "Loan ID value not a number or out of range!");
            return;
        }
        Library::RenewLoanResult result = library->renewLoan(loanId.toInt());
        switch(result) {
        case Library::RenewLoanResult::Success:
            QMessageBox::information(this, "Success", "Book renewed!");
            return;
        case Library::RenewLoanResult::InvalidLoanId:
            QMessageBox::critical(this, "Error", "Loan with given ID doesn't exist!");
            return;
        }
    }
    }
}

