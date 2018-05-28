#include "signupwindow.h"
#include "ui_signupwindow.h"

#include <QMessageBox>
#include <QFile>
#include <fstream>
#include <QTextStream>

signupwindow::signupwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signupwindow)
{
    ui->setupUi(this);
}

signupwindow::~signupwindow()
{
    delete ui;
}

void signupwindow::on_pushButton_clicked()
{
    std::ofstream file;

    QString use = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();
    QString pass_verif = ui->lineEdit_3->text();

    std::string tempu=use.toStdString();
    std::string tempp=pass.toStdString();



    if(pass != pass_verif)
    {
        QMessageBox::warning(this,"Error","The passwords are not the same !");
    }

    else
    {
        file.open("C:/Users/diogo/Desktop/Project/User_list.txt");

        if(file.is_open())
        {
            file <<  tempu <<  "\n" << tempp << "\n"  ;
        }

        else
        {
            QMessageBox::warning(this,"Error","Couldn't open file!");
        }

        file.close();
        hide();
    }

}

void signupwindow::on_pushButton_2_clicked()
{
    hide();
}
