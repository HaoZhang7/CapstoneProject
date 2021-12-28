#include "widget1.h"
#include "mainwindow.h"
#include "afterlogin.h"
#include "signup.h"
#include "widget22.h"
#include "widget2.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    m.show();
    return a.exec();

}
