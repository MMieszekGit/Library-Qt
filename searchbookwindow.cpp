#include "searchbookwindow.h"
#include "ui_searchbookwindow.h"

SearchBookWindow::SearchBookWindow(LibraryService* service, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SearchBookWindow)
    , library(service)
{
    ui->setupUi(this);
    this->setWindowTitle("Search Book");
}

SearchBookWindow::~SearchBookWindow()
{
    delete ui;
}

void SearchBookWindow::on_btnSearchByT_clicked()
{
    auto* dialog = new SearchDialog(library, QtEnums::SearchBookMode::Title, this);
    dialog->exec();
}


void SearchBookWindow::on_btnSearchByA_clicked()
{
    auto* dialog = new SearchDialog(library, QtEnums::SearchBookMode::Author, this);
    dialog->exec();
}


void SearchBookWindow::on_btnSearchByTA_clicked()
{
    auto* dialog = new SearchDialog(library, QtEnums::SearchBookMode::Both, this);
    dialog->exec();
}

