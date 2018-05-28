#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "keygenerate.h"
#include "table.h"
#include <windows.h>
#include <QFile>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QTextStream>
#include <QMessageBox>
#include <QSpinBox>
#include <QProcess>
#include <ctime>
#include <fstream>
#include <iostream>
#include<QProcess>
#include<QMessageBox>
qreal i=0;

unsigned int next = 0;
secondWindow::secondWindow(QWidget *parent,std::vector<Site> &vec, std::string &password) :
    QMainWindow(parent),
    ui(new Ui::secondWindow)
{
    _vec = vec;
    _password = password;
    ui->setupUi(this);

}

secondWindow::~secondWindow()
{
    delete ui;
}

void secondWindow::on_pushButton_clicked()
{
    QString spin=ui->spinBox->text();
    int num,upp,low,spe;
    int size_key=spin.toInt();
    srand(time(NULL));
    bool special=rand_pb();
    int count=0,progress;

    if(ui->checkBox_number->isChecked())
    {
        num=1;
        count+=2;
    }

    else num=0;

    if(ui->checkBox_upper->isChecked())
    {
        upp=1;
        count++;
    }

    else upp=0;

    if(ui->checkBox_lower->isChecked())
    {
        low=1;
        count++;
    }

    else low=0;

    if(ui->checkBox_special->isChecked())
    {
        spe=1;
        count+=3;
    }
    else spe=0;

    string mdp=key_gener(size_key,special,num,upp,low,spe);
    progress=password_security(size_key,count);
    ui->progressBar->setValue(progress);
    QString password=QString::fromStdString(mdp);    

    ui->lineEdit->setText(password);
}

void secondWindow::on_pushButton_3_clicked()
{

    if( (0+ next) < _vec.size())
    {


        ui->site0->setText(QString::fromStdString(_vec[0+next].getSiteName()));
        ui->user0->setText(QString::fromStdString(_vec[0+next].getUsername()));
        ui->pass0->setText(QString::fromStdString(_vec[0+next].getPassword()));
        _vec[0+next].changeSiteName(ui->site0->text().toStdString());
        _vec[0+next].changeUsername(ui->user0->text().toStdString());
        _vec[0+next].changePassword(ui->pass0->text().toStdString());

    }

    if((1+ next) < _vec.size())
    {
        ui->site1->setText(QString::fromStdString(_vec[1+next].getSiteName()));
        ui->user1->setText(QString::fromStdString(_vec[1+next].getUsername()));
        ui->pass1->setText(QString::fromStdString(_vec[1+next].getPassword()));
        _vec[1+next].changeSiteName(ui->site1->text().toStdString());
        _vec[1+next].changeUsername(ui->user1->text().toStdString());
        _vec[1+next].changePassword(ui->pass1->text().toStdString());
    }

    else
    {
        ui->site1->setText(" ");
        ui->user1->setText(" ");
        ui->pass1->setText(" ");
    }


    if((2+ next) < _vec.size())
    {
        ui->site2->setText(QString::fromStdString(_vec[2+next].getSiteName()));
        ui->user2->setText(QString::fromStdString(_vec[2+next].getUsername()));
        ui->pass2->setText(QString::fromStdString(_vec[2+next].getPassword()));
        _vec[2+next].changeSiteName(ui->site2->text().toStdString());
        _vec[2+next].changeUsername(ui->user2->text().toStdString());
        _vec[2+next].changePassword(ui->pass2->text().toStdString());

    }
    else
    {
        ui->site2->setText(" ");
        ui->user2->setText(" ");
        ui->pass2->setText(" ");
    }


    if((3+ next) < _vec.size())
    {
        ui->site3->setText(QString::fromStdString(_vec[3+next].getSiteName()));
        ui->user3->setText(QString::fromStdString(_vec[3+next].getUsername()));
        ui->pass3->setText(QString::fromStdString(_vec[3+next].getPassword()));
        _vec[3+next].changeSiteName(ui->site3->text().toStdString());
        _vec[3+next].changeUsername(ui->user3->text().toStdString());
        _vec[3+next].changePassword(ui->pass3->text().toStdString());

    }
    else
    {
        ui->site3->setText(" ");
        ui->user3->setText(" ");
        ui->pass3->setText(" ");
    }


    if((4+ next) < _vec.size())
    {
        ui->site4->setText(QString::fromStdString(_vec[4+next].getSiteName()));
        ui->user4->setText(QString::fromStdString(_vec[4+next].getUsername()));
        ui->pass4->setText(QString::fromStdString(_vec[4+next].getPassword()));
        _vec[4+next].changeSiteName(ui->site4->text().toStdString());
        _vec[4+next].changeUsername(ui->user4->text().toStdString());
        _vec[4+next].changePassword(ui->pass4->text().toStdString());

    }
    else
    {
        ui->site4->setText(" ");
        ui->user4->setText(" ");
        ui->pass4->setText(" ");
    }

}


void secondWindow::on_pushButton_2_clicked()
{
    QString user = ui->lineEdit_3->text();
    QString site = ui->lineEdit_2->text();
    QString password=ui->lineEdit->text();

    if(user!=NULL && site!=NULL && password!=NULL)
    {
        Site temp(user.toStdString(), password.toStdString(), site.toStdString());
        _vec.push_back(temp);
    }

}

void secondWindow::on_pushButton_4_clicked()
{
    vector_to_temp_output(_vec);
    std::string enc = "enc";
    std::string path="enc.exe";
    path = path + " " + _password + " " + enc;
    QProcess process;
    process.start(path.c_str());
    process.waitForFinished();
    process.close();
    clear_file();
    QMessageBox::warning(this,"Pass","Passwords saved correctly");
}

void secondWindow::on_pushButton_5_clicked()
{
    next +=5;
}

void secondWindow::on_pushButton_6_clicked()
{
    if(next>0)
    next -=5;
}
