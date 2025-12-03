#ifndef USERMANAGEDIALOG_H
#define USERMANAGEDIALOG_H

#include "../services/LibraryService.h"
#include "../enums/QtEnums.h"
#include "../utils/inpuUtils/inputUtils.h"

#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>

namespace Ui {
class UserManageDialog;
}

class UserManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserManageDialog(LibraryService* service, QtEnums::UserManageMode mode, QWidget *parent = nullptr);
    ~UserManageDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::UserManageDialog *ui;
    LibraryService* library;
    QtEnums::UserManageMode mode;
};

#endif // USERMANAGEDIALOG_H
