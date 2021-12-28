#include "widgetn.h"
#include "ui_widgetn.h"

widgetn::widgetn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetn)
{
    ui->setupUi(this);
}

widgetn::~widgetn()
{
    delete ui;
}
