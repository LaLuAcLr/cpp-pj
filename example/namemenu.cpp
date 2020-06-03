#include "namemenu.h"

Namemenu::Namemenu(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(840, 680);
    NameEdit=new QLineEdit(this);
    SetDone=new QPushButton(this);
    QString button_style="QPushButton{background-color:palegreen; color: orangered;border-radius:5px}"
                         "QPushButton:pressed{background-color:aquamarine;border-style:inset;}";
    QFont font("Microsoft YaHei" ,12, 35);
    NameEdit->setGeometry(320,260,200,40);
    NameEdit->setFont(font);
    NameEdit->setStyleSheet("color:black");
    SetDone->setGeometry(360,320,120,30);
    SetDone->setText("确定");
    SetDone->setFont(font);
    SetDone->setStyleSheet(button_style);
}
void Namemenu::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    QImage pixmap(":/now/bg.png");
    painter->drawImage(QRectF(0, 0, 840, 680), pixmap);
    painter->end();
}
