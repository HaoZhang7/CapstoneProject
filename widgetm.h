#ifndef WIDGETm_H
#define WIDGETm_H
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class Widgetm; }
QT_END_NAMESPACE

class Widgetm : public QWidget
{
    Q_OBJECT

public:
    Widgetm(QWidget *parent = nullptr);
    ~Widgetm();
    void paintEvent(QPaintEvent*);          //绘图
    void mousePressEvent(QMouseEvent*);          //鼠标点击
    void mouseReleaseEvent(QMouseEvent*);          //鼠标释放
    void mouseMoveEvent(QMouseEvent*);          //鼠标移动
    void leaveEvent(QEvent *event);          //鼠标离开
    double distance(QPoint pos1, QPoint pos2);      //获取两点之间的距离
public slots:
    void timeout();

private slots:
    void on_startButton_clicked();          //开始按钮

    void on_stopButton_clicked();           //测试按钮

    void on_back_clicked();

private:
    Ui::Widgetm *ui;
    QPoint lamps[16];                        //九个灯泡位置
    int size;                               //大小
    int presentation;                   //正在演示否？
    int presentation_time;              //演示了多久
    QTimer *timer;                      //时钟
    int status[16];                      //现在灯泡状态
    int dest_status[16];                      //目标灯泡状态
    QImage on_img;                  //打开图像
    QImage off_img;                  //关闭图像
    QSqlDatabase db;
    bool connected;
    int currentID;

signals:
   void back();
};
#endif // WIDGETm_H
