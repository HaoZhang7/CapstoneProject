#include "widget2.h"
#include <math.h>
#include "ui_widget2.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QMouseEvent>



Widget2::Widget2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget2)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("player");
    if (!db.open())
    {
    qDebug() << "Failed to connect to database.";
    }
    size = 80;
    lamps[0] = QPoint(220, 100);
    lamps[1] = QPoint(220 + size, 100);
    lamps[2] = QPoint(220 + size + size, 100);
    lamps[3] = QPoint(220, 100 + size);
    lamps[4] = QPoint(220 + size, 100 + size);
    lamps[5] = QPoint(220 + size + size, 100 + size);
    lamps[6] = QPoint(220, 100 + size + size);
    lamps[7] = QPoint(220 + size, 100 + size + size);
    lamps[8] = QPoint(220 + size + size, 100 + size + size);
    for(int i = 0; i < 9; i++)
    {
        status[i] = 0;
    }
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, QColor(255, 255, 255));
    this->setPalette(pal);
    setMouseTracking(true);
    presentation = 0;
    presentation_time = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(100);
    if(!on_img.load("on.png"))
    {
        QMessageBox::critical(this, "Error", "on.png not found!");
    }
    if(!off_img.load("off.png"))
    {
        QMessageBox::critical(this, "Error", "off.png not found!");
    }
}

void Widget2::timeout()
{

    if(presentation)
    {
        presentation_time += 1;
        if(presentation_time == 10)
        {
            for(int i = 0; i < 9; i++)
            {
                status[i] = dest_status[i];
            }
        }
        if(presentation_time == 40)
        {
            for(int i = 0; i < 9; i++)
            {
                status[i] = qrand() % 2;
            }
            presentation = 0;
        }
    }
    update();
}

Widget2::~Widget2()
{
    timer->stop();
    delete timer;
    delete ui;
}

double Widget2::distance(QPoint pos1, QPoint pos2)
{
    return sqrt((pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) + (pos1.y() - pos2.y()) * (pos1.y() - pos2.y()));
}


void Widget2::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setBackground(QColor(255, 255, 255));
    for(int i = 0; i < 9; i++)
    {
        if(status[i] == 0)
        {
            painter.drawImage(QRect(lamps[i].x() - 30, lamps[i].y() - 30, 60, 60), off_img, QRect(0, 0, 104, 104));
        }
        else
        {
            painter.drawImage(QRect(lamps[i].x() - 30, lamps[i].y() - 30, 60, 60), on_img, QRect(0, 0, 104, 104));
        }
    }
    painter.setFont(QFont("Times New Roman", 20));
    QString str = "Not started";
    if(presentation == 0)
        str = QString("Click time");
    else
        str = QString("Show time");
    painter.drawText(0, 0, 600, 60, Qt::AlignCenter, str);
    painter.end();
    update();
}

void Widget2::mousePressEvent(QMouseEvent* event)
{

    if(presentation)
        return;

    for(int i = 0; i < 10; i++)
    {
        if(distance(lamps[i], event->pos()) < 30)
        {
            status[i] = 1 - status[i];
        }
    }
    update();
}

void Widget2::mouseReleaseEvent(QMouseEvent*)
{

    if(presentation)
        return;
    update();
}

void Widget2::mouseMoveEvent(QMouseEvent* event)
{

    if(presentation)
        return;
}

void Widget2::leaveEvent(QEvent *)
{
}

void Widget2::on_startButton_clicked()
{

    for(int i = 0; i < 9; i++)
    {
        dest_status[i] = qrand() % 2;
    }
    presentation = 1;
    presentation_time = 0;
}

void Widget2::on_stopButton_clicked()
{
    QString name = ui->name->text();
    int right = 0;
    for(int i = 0; i < 9; i++)
    {
        if(dest_status[i] == status[i])
            right += 1;
    }
    if(right == 9)
    {
        QSqlQuery query;
        QSqlQuery query2;
        int score;
        query2.prepare("SELECT score2 from playerinfo WHERE name = :name");
        query2.bindValue(":name",name);
        query2.exec();
        while(query2.next()){
            score = query2.value(0).toInt();
        }
        if(score ==0){
        query.prepare("UPDATE playerinfo SET score2 =1 WHERE name = :name");
        query.bindValue(":name",name);
        query.exec();
        }
        QMessageBox::information(this, "Right", "Congratulations!");
        for(int i = 0; i < 9; i++)
        {
            status[i] = 0;
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Not right!");
        for(int i = 0; i < 9; i++)
        {
            status[i] = 0;
        }
    }
}

void Widget2::on_backbutton_clicked()
{
    emit back();
}

