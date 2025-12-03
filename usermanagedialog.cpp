#include "usermanagedialog.h"
#include "ui_usermanagedialog.h"

UserManageDialog::UserManageDialog(LibraryService* service, QtEnums::UserManageMode mode, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserManageDialog)
    , library(service)
    , mode(mode)
{
    ui->setupUi(this);

    switch(mode) {
        case::QtEnums::UserManageMode::AddUser: {
            this->setWindowTitle("Add User");
            ui->labelUserId->show();
            ui->labelUsername->show();
            ui->labelUserMail->show();
            ui->lineEditUserId->show();
            ui->lineEditUsername->show();
            ui->lineUserMail->show();
            break;
        }
        case::QtEnums::UserManageMode::DeleteUser: {
            this->setWindowTitle("Remove User");
            ui->labelUserId->hide();
            ui->labelUsername->show();
            ui->labelUserMail->hide();
            ui->lineEditUserId->hide();
            ui->lineEditUsername->show();
            ui->lineUserMail->hide();
            break;
        }
    }
}

UserManageDialog::~UserManageDialog()
{
    delete ui;
}

void UserManageDialog::on_buttonBox_accepted()
{
    switch(mode) {
    case QtEnums::UserManageMode::AddUser: {
        QList<QLineEdit*> edits = this->findChildren<QLineEdit*>();
        for(QLineEdit* edit : edits) {
            if (edit->text().trimmed().isEmpty()) {
                QMessageBox::critical(this, "Error", "Fields cannot be empty!");
                return;
            }
        }
        QString userId = ui->lineEditUserId->text().trimmed();
        if (!verifyIntInput(userId)) {
            QMessageBox::critical(this, "Error", "User ID out of range or not a number!");
            return;
        }
        std::string userName = ui->lineEditUsername->text().trimmed().toStdString();
        QString userMail = ui->lineUserMail->text().trimmed();
        if (!verifyEmailInput(userMail)) {
            QMessageBox::critical(this, "Error", "Inserted value is not an email!");
            return;
        }

        Library::AddResult result = library->addUser(
            userId.toInt(), userName, userMail.toStdString()
        );
        switch(result) {
        case Library::AddResult::Success:
            QMessageBox::information(this, "Success", "User Added!");
            break;
        case Library::AddResult::DuplicatedId:
            QMessageBox::critical(this, "Error", "Duplicated ID!");
            break;
        case Library::AddResult::DuplicatedTitle:
            QMessageBox::critical(this, "Error", "Duplicated Username!");
            break;
        }
        break;
    }
    case QtEnums::UserManageMode::DeleteUser: {
        if (ui->lineEditUsername->text().trimmed().isEmpty()) {
            QMessageBox::critical(this, "Error", "Username field cannot be empty!");
            return;
        }
        std::string userName = ui->lineEditUsername->text().trimmed().toStdString();
        Library::RemoveUserResult result = library->removeUser(userName);
        switch(result) {
        case Library::RemoveUserResult::Success:
            QMessageBox::information(this, "Success", "User removed!");
            break;
        case Library::RemoveUserResult::InvalidUserName:
            QMessageBox::critical(this, "Error", "Invalid Username!");
            break;
        case Library::RemoveUserResult::HasActiveLoans:
            QMessageBox::critical(this, "Error", "Removal failed - user has active loans!");
            break;
        }
        break;
    }
    }
}
