#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondwindow.h"
#include "signupwindow.h"
#include<QProcessEnvironment>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Login_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    secondWindow *Secondwindow;
    signupwindow Signupwindow;

};

#endif // MAINWINDOW_H
