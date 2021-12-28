#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "widget1.h"
#include "widget2.h"
#include "widget22.h"
#include "widgetm.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Memory Trainer");
    this->setStyleSheet("background-image: url(:/res/bg.png);");
    QPixmap piximap("profile2.png");
    QPixmap piximap2("login.png");
    QPixmap piximap3("signup2.png");
    QIcon profilebtn(piximap);
    QIcon loginbtn(piximap2);
    QIcon signupbtn(piximap3);
    ui->profile->setIcon(profilebtn);
    ui->pushButton->setIcon(loginbtn);
    ui->pushButton_2->setIcon(signupbtn);
    ui->pushButton->setIconSize(QSize(50,30));
    ui->profile->setIconSize(QSize(40,60));
    ui->pushButton_2->setIconSize(QSize(30,50));
    setWindowIcon(QIcon("brain.png"));
    ui->stackedWidget->insertWidget(2,&w1);
    ui->stackedWidget->insertWidget(5,&w2);
    ui->stackedWidget->insertWidget(6,&wm);
    ui->stackedWidget->insertWidget(7,&w22);
    connect(&w1, SIGNAL(back()), this, SLOT(backhome()));
    connect(&w2, SIGNAL(back()), this, SLOT(backhome()));
    connect(&w22, SIGNAL(back()), this, SLOT(backhome()));
    connect(&wm, SIGNAL(back()), this, SLOT(backhome()));
    ui->stackedWidget->setCurrentIndex(0);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("player");
    if (!db.open())
    {
    qDebug() << "Failed to connect to database.";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{


    signup s;
    s.setModal(true);
    s.exec();

}




void MainWindow::on_pushButton_clicked()
{

    QString username = ui->username->text();
    QString password = ui->password->text();
    QSqlQuery query;
    if (query.exec("SELECT * from playerinfo WHERE username = '" + username + "' AND password = '" +password + "'")){
        int count=0;
        while(query.next()){
            uniname = query.value(0).toString();
            count++;
        }
        if(count ==1){
            ui->stackedWidget->setCurrentIndex(1);
            ui->welcome->setText("Welcome "+uniname+"!!!");
        }
        if(count >1){
            ui->stackedWidget->setCurrentIndex(1);
            ui->welcome->setText("Welcome "+uniname+"!!!");
        }
        if(count <1){
            QMessageBox::warning(this, "Login failed","Invalid username or password.");
        }
    }
}




void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_5_clicked()
{

    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::backhome()
{
    QString username = ui->username->text();
    QString password = ui->password->text();
    int oldscore;
    int curscore;
    QSqlQuery query2;
    query2.exec("SELECT score from playerinfo WHERE username = '" + username + "' AND password = '" +password + "'");
    while(query2.next()){
        oldscore = query2.value(0).toInt();


    }
    QSqlQuery query;
    query.prepare("SELECT `gameone` FROM `score` WHERE name =:name;");
    query.bindValue(":name",uniname);
    query.exec();
    while(query.next()){
        curscore= query.value(0).toInt();

    }
    if(curscore>oldscore){
       query.prepare("UPDATE `playerinfo` SET `score`=:score WHERE username = '" + username + "' AND password = '" +password + "'");
       query.bindValue(":score",curscore);
       query.exec();

    }
    ui->stackedWidget->setCurrentIndex(1);


}


void MainWindow::on_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    QString username = ui->username->text();
    QString password = ui->password->text();
    ui->welcome1->setText("Welcome "+uniname+"!!!");
    ui->nname->setText(uniname);
    ui->uusername->setText(username);
    QSqlQuery query2;
    int score;
    int score2;
    query2.exec("SELECT score from playerinfo WHERE username = '" + username + "' AND password = '" +password + "'");
    while(query2.next()){
        score = query2.value(0).toInt();
    }
    query2.exec("SELECT score2 from playerinfo WHERE username = '" + username + "' AND password = '" +password + "'");
    while(query2.next()){
        score2 = query2.value(0).toInt();
    }

    ui->game1score->setText(QString::number(score));
    if(score2 == 1){
        ui->game2score->setText("Easy 3x3");
    }
    if(score2 == 2){
        ui->game2score->setText("Medium 4x4");
    }
    if(score2 == 3){
        ui->game2score->setText("Hard 5x5");
    }
}


void MainWindow::on_backtom_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

