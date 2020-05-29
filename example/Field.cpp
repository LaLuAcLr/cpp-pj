#include "Field.h"

Field::Field(QWidget *parent)
    : QLabel(parent)
{
    setFixedSize(56, 40);
    setAlignment(Qt::AlignCenter);
    hoe_pic = QPixmap(":/veg/field_hoed.png").scaled(45, 32, Qt::KeepAspectRatio);
    seed_pic = QPixmap(":/veg/field_seeded.png").scaled(45, 32, Qt::KeepAspectRatio);
    status = 0;
}

void Field::set_bg()
{
    switch(status)
    {
    case 0:
        setPixmap(QPixmap());
        break;
    case 1:
        setPixmap(hoe_pic);
        break;
    case 2:
        setPixmap(seed_pic);
        break;
    case 3:
        setPixmap(hoe_pic);
        break;
    }
}

Veg::Veg(QWidget *parent)
    : QLabel(parent)
{
    setFixedSize(56, 40);
    setAlignment(Qt::AlignCenter);
    name = "";
    setPixmap(QPixmap());
    big_grass = QPixmap(":/veg/grass_big.png").scaled(45, 32, Qt::KeepAspectRatio);
    small_grass = QPixmap(":/veg/grass_small.png").scaled(45, 32, Qt::KeepAspectRatio);
    isRipe = false;
    small_grass_day = -1;
    big_grass_day = -1;
    ripe_day = -1;
    plant_day = -1;
}

void Veg::refresh(QString n, int plantday, int smallgrassday, int biggrassday, int ripeday)
{
    name = n;
    plant_day = plantday;
    small_grass_day = smallgrassday;
    big_grass_day = biggrassday;
    ripe_day = ripeday;
    QString veg_path = QString(":/veg/veg_") + name.toLower() + QString(".png");
    veg_pic = QPixmap(veg_path).scaled(45, 32, Qt::KeepAspectRatio);
}

void Veg::restart()
{
    name = "";
    plant_day = -1;
    small_grass_day = -1;
    big_grass_day = -1;
    ripe_day = -1;
    veg_pic = QPixmap();
    setPixmap(veg_pic);
}

bool Veg::update_pic(int Day)
{
    if (Day - plant_day == small_grass_day)
    {
        show_small_grass();
        return true;
    }
    else if (Day - plant_day == big_grass_day)
    {
        show_big_grass();
        return true;
    }
    else if (Day - plant_day == ripe_day)
    {
        show_ripe();
        isRipe = true;
        return true;
    }
    return false;
}
