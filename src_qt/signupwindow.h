#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QDialog>

namespace Ui {
class signupwindow;
}

class signupwindow : public QDialog
{
    Q_OBJECT

public:
    explicit signupwindow(QWidget *parent = 0);
    ~signupwindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::signupwindow *ui;
};

#endif // SIGNUPWINDOW_H
