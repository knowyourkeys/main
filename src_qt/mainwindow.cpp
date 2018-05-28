#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QPixmap>
#include <QLabel>
#include<windows.h>

#include <QFile>
#include <fstream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/diogo/Desktop/Project/logo_mainwindow.png");
    ui->label_pic->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Login_clicked()
{
    std::ifstream file;

    QString username = ui->lineEdit_userame ->text();
    QString password = ui->lineEdit_password->text();
    std::string pass= password.toStdString();

    std::string temp_user,temp_pass,temp;

    file.open("user_list.txt");

    if(file.is_open())
    {
          std::getline(file,temp_user);
    }
    file.close();

    if(username == QString::fromStdString(temp_user))
    {
        std::vector<Site> vec;
        std::string path="enc.exe";
        std::string dec = "dec";
        path = path + " " + password.toStdString() + " " + dec;
        QProcess process;
        process.start(path.c_str());
        process.waitForFinished();
        process.close();
        vec = output_temp_to_vector();
        clear_file();
        if(vec[0].getUsername() == "ERROR_PASS")
                 QMessageBox::warning(this,"Login","Username and password incorrect");
        else{
        hide();
        Secondwindow = new secondWindow(this,vec,pass);
        Secondwindow->show();

    }
}}


void MainWindow::on_pushButton_clicked()
{
    signupwindow Signupwindow;
    Signupwindow.setModal(true);
    Signupwindow.exec();
}
