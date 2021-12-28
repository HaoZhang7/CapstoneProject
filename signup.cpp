#include "signup.h"
#include "ui_signup.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    this->setWindowTitle("SignUp");
    setWindowIcon(QIcon("signup.png"));
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("player");
    connected = db.open();
     if (connected)
     {
        ui->connectionStatus->setText("Connected To Database, Ready to Signup!!!");
     }

     else
     {
        qDebug() << "Failed to connect to database.";
     }
    }


signup::~signup()
{
    delete ui;
}

void signup::on_pushButton_2_clicked()
{
    close();

}


void signup::on_pushButton_clicked()
{
    if (connected)
     {
     QString name = ui->name->text();
     QString username = ui->uname->text();
     QString password = ui->pwd->text();

     qDebug() << "INSERT INTO `playerinfo`(`name`, `username`, `password`, `score`, `score2`) VALUES  ('" + name + "','" + username + "','" + password + "',0,0)";

     QSqlQuery query;
     if (query.exec("INSERT INTO `playerinfo`(`name`, `username`, `password`, `score`) VALUES  ('" + name + "','" + username + "','" + password + "',0)") )
     {
     ui->signuptrue->setText("Signup Success!");
     qDebug() << "Insert success.";
     }
     else
     {
     qDebug() << query.lastError().text();
     }
     }
     else
     {
     qDebug() << "Failed to connect to database.";
     }
    }


