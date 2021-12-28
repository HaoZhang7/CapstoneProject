#ifndef WIDGET1_H
#define WIDGET1_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget1; }
QT_END_NAMESPACE

class Widget1 : public QWidget
{
    Q_OBJECT

public:
    Widget1(QWidget *parent = nullptr);
    ~Widget1();
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void leaveEvent(QEvent *event);
    double distance(QPoint pos1, QPoint pos2);
    int round;
public slots:
    void timeout();

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_back_clicked();

    void on_back_2_clicked();

private:
    Ui::Widget1 *ui;
    QPoint buttons[10];
    int pressed;
    QPoint mousePos;
    int size;
    int numbers[10000];
    int presentation;
    int presentation_time;
    QTimer *timer;
    int right_cnt;
    QSqlDatabase db;
    bool connected;
    int currentID;


signals:
   void back();


};
#endif // WIDGET1_H
