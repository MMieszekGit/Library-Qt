#ifndef LOANMANAGEDIALOG_H
#define LOANMANAGEDIALOG_H

#include "../services/LibraryService.h"
#include "../enums/QtEnums.h"
#include "../utils/inpuUtils/inputUtils.h"

#include "showdatawindow.h"

#include <QString>
#include <QDialog>
#include <QMessageBox>
#include <QDate>

namespace Ui {
class LoanManageDialog;
}

class LoanManageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoanManageDialog(LibraryService* service,  QtEnums::LoanManageMode mode, QWidget *parent = nullptr);
    ~LoanManageDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LoanManageDialog *ui;
    LibraryService* library;
    QtEnums::LoanManageMode mode;
};

#endif // LOANMANAGEDIALOG_H
