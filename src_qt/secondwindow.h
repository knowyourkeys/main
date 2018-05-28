#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include "site.h"

extern unsigned int next;

namespace Ui {
class secondWindow;
}

class secondWindow : public QMainWindow
{
    Q_OBJECT

public:
    std::vector<Site> _vec;
    std::string _password;
    secondWindow(QWidget *parent, std::vector<Site> &vec, std::string &password);
    ~secondWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::secondWindow *ui;

};

#endif // SECONDWINDOW_H
