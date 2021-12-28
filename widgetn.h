#ifndef WIDGETN_H
#define WIDGETN_H

#include <QWidget>

namespace Ui {
class widgetn;
}

class widgetn : public QWidget
{
    Q_OBJECT

public:
    explicit widgetn(QWidget *parent = nullptr);
    ~widgetn();

private:
    Ui::widgetn *ui;
};

#endif // WIDGETN_H
