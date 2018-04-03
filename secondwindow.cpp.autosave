#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "keygenerate.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSpinBox>
#include <QProcess>
#include <ctime>

secondWindow::secondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::secondWindow)
{
    ui->setupUi(this);
}

secondWindow::~secondWindow()
{
    delete ui;
}

void secondWindow::on_pushButton_clicked()
{

    QString spin=ui->spinBox->text();
    int size_key=spin.toInt();
    srand(time(NULL));
    bool special=rand_pb();

    string mdp=key_gener(size_key,special);
    QString password=QString::fromStdString(mdp);

    ui->lineEdit->setText(password);
}

void secondWindow::on_pushButton_3_clicked()
{
    QFile file("C:/Users/diogo/Desktop/Project/passwords.txt");
    if(!file.open(QIODevice::ReadOnly))
        QMessageBox::information(0,"information",file.errorString());

    QTextStream in(&file);

    ui->textBrowser->setText(in.readAll());
}


