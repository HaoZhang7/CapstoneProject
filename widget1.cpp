#include "widget1.h"
#include <math.h>
#include "ui_widget1.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QMouseEvent>
#include "mainwindow.h"


Widget1::Widget1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget1)
{
    ui->setupUi(this);


    pressed = -1;
    size = 80;
    mousePos = QPoint(0, 0);
    buttons[0] = QPoint(300, 100 + size + size + size);
    buttons[1] = QPoint(220, 100);
    buttons[2] = QPoint(220 + size, 100);
    buttons[3] = QPoint(220 + size + size, 100);
    buttons[4] = QPoint(220, 100 + size);
    buttons[5] = QPoint(220 + size, 100 + size);
    buttons[6] = QPoint(220 + size + size, 100 + size);
    buttons[7] = QPoint(220, 100 + size + size);
    buttons[8] = QPoint(220 + size, 100 + size + size);
    buttons[9] = QPoint(220 + size + size, 100 + size + size);
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, QColor(255, 255, 255));
    this->setPalette(pal);
    setMouseTracking(true);
    round = 0;
    presentation = 0;
    presentation_time = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(100);
    right_cnt = 0;
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

void Widget1::timeout()
{

    if(presentation)
    {
        presentation_time += 1;
        if(presentation_time >= 10 && (presentation_time - 10) % 20 == 0)
        {
            pressed = numbers[(presentation_time - 10) / 20];
        }
        if(presentation_time >= 10 && (presentation_time - 20) % 20 == 0)
        {
            pressed = -1;
            if((presentation_time - 20) / 20 == round - 1)
            {
                presentation = 0;
            }
        }
    }
    update();
}

Widget1::~Widget1()
{
    timer->stop();
    delete timer;
    delete ui;
}

double Widget1::distance(QPoint pos1, QPoint pos2)
{
    return sqrt((pos1.x() - pos2.x()) * (pos1.x() - pos2.x()) + (pos1.y() - pos2.y()) * (pos1.y() - pos2.y()));
}

void paintButton(QPainter& painter, QPoint center, int status, int num)
{
    char str[2] = "0";
    str[0] = '0' + num;
    painter.setPen(QPen(Qt::black, 2));
    if(status == 0)
    {
        painter.setBrush(QColor(245, 245, 245));
    }
    if(status == 1)
    {
        painter.setBrush(QColor(245, 245, 245));

    }
    if(status == 2)
    {
        painter.setBrush(QColor(200, 200, 200));
    }
    painter.drawEllipse(center.x() - 30, center.y() - 30, 60, 60);
    painter.setFont(QFont("Times New Roman", 20));
    painter.drawText(center.x() - 30, center.y() - 30, 60, 60, Qt::AlignCenter, str);
}


void Widget1::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setBackground(QColor(255, 255, 255));
    for(int i = 0; i < 10; i++)
    {
        if(pressed == i)
        {
            paintButton(painter, buttons[i], 2, i);
        }
        else if(distance(buttons[i], mousePos) < 30)
        {
            paintButton(painter, buttons[i], 1, i);
        }
        else
        {
            paintButton(painter, buttons[i], 0, i);
        }
    }
    painter.setFont(QFont("Times New Roman", 20));
    QString str = "Not started";
    if(round > 0)
    {
        if(presentation == 0)
            str = QString("Round %1-Click time").arg(round);
        else
            str = QString("Round %1-Memorize").arg(round);
    }
    painter.drawText(0, 0, 600, 60, Qt::AlignCenter, str);
    painter.end();
    update();
}

void Widget1::mousePressEvent(QMouseEvent*)
{

    if(presentation)
        return;

    pressed = -1;
    for(int i = 0; i < 10; i++)
    {
        if(distance(buttons[i], mousePos) < 30)
        {
            pressed = i;
        }
    }
    update();
}
void Widget1::on_back_2_clicked()
{
    QString name = ui->name->text();

}
void Widget1::mouseReleaseEvent(QMouseEvent*)
{

    if(presentation)
        return;
    if(pressed >= 0)
    {
        if(pressed == numbers[right_cnt])
        {
            right_cnt += 1;

            if(round == right_cnt)
            {
                numbers[round] = qrand() % 10;
                round += 1;
                presentation = 1;
                presentation_time = 0;
                right_cnt = 0;
                pressed = -1;
                QString name = ui->name->text();
                QSqlQuery query;
                query.prepare("UPDATE playerinfo SET score =:score WHERE name = :name");
                query.bindValue(":score",round);
                query.bindValue(":name",name);
                query.exec();
            }
        }
        else
        {
            QMessageBox::critical(this, "Error!", "Not right");
        }
    }
    pressed = -1;
    update();
}

void Widget1::mouseMoveEvent(QMouseEvent* event)
{

    if(presentation)
        return;
    mousePos = event->pos();
    if(pressed >= 0)
    {
        if(distance(buttons[pressed], mousePos) >= 30)
        {
            pressed = -1;
        }
    }
    update();
}

void Widget1::leaveEvent(QEvent *)
{

    pressed = -1;
    update();
}

void Widget1::on_startButton_clicked()
{

    round = 1;
    numbers[0] = qrand() % 10;
    presentation = 1;
    presentation_time = 0;
    right_cnt = 0;
}

void Widget1::on_stopButton_clicked()
{
    round = 0;
    presentation = 0;
}

void Widget1::on_back_clicked()
{
    emit back();
}



