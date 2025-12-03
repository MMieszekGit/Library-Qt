#include "showdatawindow.h"
#include "ui_showdatawindow.h"

ShowDataWindow::ShowDataWindow(const std::vector<std::string>& headers
                               , const std::vector<std::vector<QString>>& data
                               , QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ShowDataWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Data");
    showData(headers, data);
}

ShowDataWindow::~ShowDataWindow()
{
    delete ui;
}

void ShowDataWindow::showData(const std::vector<std::string>& headers,
                              const std::vector<std::vector<QString>>& data)
{
    if (data.empty()) {
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(0);
        return;
    }

    ui->tableWidget->setRowCount(data.size());
    ui->tableWidget->setColumnCount(data[0].size());

    QStringList qHeaders;
    for (const auto& h : headers)
        qHeaders << QString::fromStdString(h);
    ui->tableWidget->setHorizontalHeaderLabels(qHeaders);

    for (int row = 0; row < data.size(); ++row) {
        for (int col = 0; col < data[row].size(); ++col) {
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(data[row][col]));
        }
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    ui->tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    ui->tableWidget->adjustSize();
    this->adjustSize();
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
}

