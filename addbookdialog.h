#ifndef ADDBOOKWINDOW_H
#define ADDBOOKWINDOW_H

#include <QDialog>
#include "../services/LibraryService.h"
#include "../utils/inpuUtils/inputUtils.h"

namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog(LibraryService* service, QWidget *parent = nullptr);
    ~AddBookDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddBookDialog *ui;
    LibraryService* library;
};

#endif // ADDBOOKWINDOW_H
