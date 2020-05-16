#include "dialog.h"
#include "ui_dialog.h"
#include <QIcon>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QIcon hoe_icon(":/tool/hoe.png");
    ui->hoe->setIcon(hoe_icon);
    ui->hoe->setIconSize(QSize(80, 80));

    QIcon knife_icon(":/tool/knife.png");
    ui->knife->setIcon(knife_icon);
    ui->knife->setIconSize(QSize(80, 80));

    QIcon pot_icon(":/tool/pot.png");
    ui->pot->setIcon(pot_icon);
    ui->pot->setIconSize(QSize(80, 80));

    QIcon seed_icon(":/tool/seed.png");
    ui->seed->setIcon(seed_icon);
    ui->seed->setIconSize(QSize(80, 80));

    QPixmap avatar_icon(":/avatar.png");

}

Dialog::~Dialog()
{
    delete ui;
}

