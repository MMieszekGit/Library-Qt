#ifndef SHOWDATAWINDOW_H
#define SHOWDATAWINDOW_H

#include <QMainWindow>

#include <string>
#include <vector>

namespace Ui {
class ShowDataWindow;
}

class ShowDataWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowDataWindow(const std::vector<std::string>& headers
                            , const std::vector<std::vector<QString>>& data
                            , QWidget *parent = nullptr);
    ~ShowDataWindow();

private:
    Ui::ShowDataWindow *ui;
    void showData(const std::vector<std::string>& headers
                  , const std::vector<std::vector<QString>>& data);
};

#endif // SHOWDATAWINDOW_H
