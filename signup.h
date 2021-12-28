#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <mainwindow.h>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::signup *ui;
    MainWindow *w;
    QSqlDatabase db;
    bool connected;
     int currentID;

};

#endif // SIGNUP_H
