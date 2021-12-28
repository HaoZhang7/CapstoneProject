#include "afterlogin.h"
#include "ui_afterlogin.h"
#include "widget1.h"
#include "widget2.h"
#include "widget22.h"
afterlogin::afterlogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::afterlogin)
{
    ui->setupUi(this);

}

afterlogin::~afterlogin()
{
    delete ui;
}

void afterlogin::on_pushButton_clicked()
{
    hide();
    Widget1 *w = new Widget1;
    w->show();
}


void afterlogin::on_pushButton_2_clicked()
{
    hide();
    Widget2 *w = new Widget2;
    w->show();

}




void afterlogin::on_pushButton_4_clicked()
{
    hide();
    Widget22 *w = new Widget22;
    w->show();
}

