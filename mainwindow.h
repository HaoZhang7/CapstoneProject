#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <widget1.h>
#include <widget2.h>
#include <widget22.h>
#include <widgetm.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString uniname;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void backhome();
    void on_profile_clicked();

    void on_backtom_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    Widget1 w1;
    Widget2 w2;
    Widget22 w22;
    Widgetm wm;

};

#endif // MAINWINDOW_H
