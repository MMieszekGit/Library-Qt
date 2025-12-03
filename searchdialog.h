#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include "../services/LibraryService.h"
#include "../enums/QtEnums.h"
#include "showdatawindow.h"

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(LibraryService* service, QtEnums::SearchBookMode mode, QWidget *parent = nullptr);
    ~SearchDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SearchDialog *ui;
    LibraryService* library;
    QtEnums::SearchBookMode mode;
};

#endif // SEARCHDIALOG_H
