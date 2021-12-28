#include "widget22.h"
#include <math.h>
#include "ui_widget22.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QMouseEvent>



Widget22::Widget22(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget22)
{
    ui->setupUi(this);
    size = 80;
    lamps[0] = QPoint(180, 100);
    lamps[1] = QPoint(180 + size, 100);
    lamps[2] = QPoint(180 + size + size, 100);
    lamps[3] = QPoint(180 + size + size+ size , 100);
    lamps[4] = QPoint(180 + size + size+ size +size , 100);
    lamps[5] = QPoint(180 , 180);
    lamps[6] = QPoint(180 + size , 180);
    lamps[7] = QPoint(180 + size + size , 180);
    lamps[8] = QPoint(180 + size + size+ size , 180);
    lamps[9] = QPoint(180 + size + size+ size +size , 180);
    lamps[10] = QPoint(180 , 260);
    lamps[11] = QPoint(180 + size , 260);
    lamps[12] = QPoint(180 + size + size , 260);
    lamps[13] = QPoint(180 + size + size+ size , 260);
    lamps[14] = QPoint(180 + size + size+ size +size , 260);
    lamps[15] = QPoint(180 , 340);
    lamps[16] = QPoint(180 + size , 340);
    lamps[17] = QPoint(180 + size + size , 340);
    lamps[18] = QPoint(180 + size + size+ size , 340);
    lamps[19] = QPoint(180 + size + size+ size +size , 340);
    lamps[20] = QPoint(180 , 420);
    lamps[21] = QPoint(180 + size , 420);
    lamps[22] = QPoint(180 + size + size , 420);
    lamps[23] = QPoint(180 + size + size+ size , 420);
    lamps[24] = QPoint(180 + size + size+ size +size , 420);
    for(int i = 0; i < 25; i++)
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

void Widget22::timeout()
{
    if(presentation)
    {
        presentation_time += 1;
        if(presentation_time == 10)
        {
            for(int i = 0; i < 25; i++)
            {
                status[i] = dest_status[i];
            }
        }
        if(presentation_time == 40)
        {
            for(int i = 0; i < 25; i++)
            {
                status[i] = qrand() % 2;
            }
            presentation = 0;
        }
    }
    update();
}

Widget22::~Widget22()
{
    timer->stop();
    delete timer;
    delete ui;
}

double Widget22::distance(QPoint pos1, QPoint pos2)
{
    return sqrt((pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) + (pos1.y() - pos2.y()) * (pos1.y() - pos2.y()));
}

void Widget22::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setBackground(QColor(255, 255, 255));
    for(int i = 0; i < 25; i++)
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
    painter.drawText(0, 0, 660, 60, Qt::AlignCenter, str);
    painter.end();
    update();
}

void Widget22::mousePressEvent(QMouseEvent* event)
{

    if(presentation)
        return;

    for(int i = 0; i < 25; i++)
    {
        if(distance(lamps[i], event->pos()) < 30)
        {
            status[i] = 1 - status[i];
        }
    }
    update();
}

void Widget22::mouseReleaseEvent(QMouseEvent*)
{

    if(presentation)
        return;
    update();
}

void Widget22::mouseMoveEvent(QMouseEvent* event)
{

    if(presentation)
        return;
}

void Widget22::leaveEvent(QEvent *)
{
}

void Widget22::on_startButton_clicked()
{
    for(int i = 0; i < 25; i++)
    {
        dest_status[i] = qrand() % 2;
    }
    presentation = 1;
    presentation_time = 0;
}

void Widget22::on_stopButton_clicked()
{
    QString name = ui->name->text();
    int right = 0;
    for(int i = 0; i < 25; i++)
    {
        if(dest_status[i] == status[i])
            right += 1;
    }
    if(right == 25)
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
        if(score >1){
        query.prepare("UPDATE playerinfo SET score2 =3 WHERE name = :name");
        query.bindValue(":name",name);
        query.exec();
        }
        QMessageBox::information(this, "Right", "Congratulations!");
        for(int i = 0; i < 25; i++)
        {
            status[i] = 0;
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Not right!");
        for(int i = 0; i < 25; i++)
        {
            status[i] = 0;
        }
    }
}

void Widget22::on_back_clicked()
{
    emit back();
}

