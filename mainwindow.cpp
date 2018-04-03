#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_userame ->text();
    QString password = ui->lineEdit_password->text();

    if(username == "admin" && password == "admin")
    {
        hide();
        Secondwindow = new secondWindow(this);
        Secondwindow->show();
    }

    else
    {
        QMessageBox::warning(this,"Login","Username and password incorrect");
    }
}
