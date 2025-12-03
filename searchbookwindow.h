#ifndef SEARCHBOOKWINDOW_H
#define SEARCHBOOKWINDOW_H

#include "../services/LibraryService.h"
#include "../enums/QtEnums.h"
#include "searchdialog.h"

#include <QMainWindow>

namespace Ui {
class SearchBookWindow;
}

class SearchBookWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchBookWindow(LibraryService* service, QWidget *parent = nullptr);
    ~SearchBookWindow();

private slots:
    void on_btnSearchByT_clicked();

    void on_btnSearchByA_clicked();

    void on_btnSearchByTA_clicked();

private:
    Ui::SearchBookWindow *ui;
    LibraryService* library;
};

#endif // SEARCHBOOKWINDOW_H
