#ifndef AFTERLOGIN_H
#define AFTERLOGIN_H

#include <QDialog>

namespace Ui {
class afterlogin;
}

class afterlogin : public QDialog
{
    Q_OBJECT

public:
    explicit afterlogin(QWidget *parent = nullptr);
    ~afterlogin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



    void on_pushButton_4_clicked();

private:
    Ui::afterlogin *ui;
};

#endif // AFTERLOGIN_H
