#ifndef FIELD_H
#define FIELD_H
#include <QLabel>
#include <QString>
#include <QDebug>

class Field : public QLabel
{
    Q_OBJECT

public:
    Field(QWidget *parent = 0);
public:
    void set_bg();
    void restart();
    void set_status(int s) { status = s; }
    int get_status() const { return status; }
private:
    int status; // 0=orig, 1=hoe, 2=seed, 3=grown
    QPixmap hoe_pic;
    QPixmap seed_pic;
};

class Veg : public QLabel
{
    Q_OBJECT

public:
    Veg(QWidget *parent = 0);
public:
    bool update_pic(int Day); // 当前天数
    void refresh(QString, int, int, int, int);
    void restart();
    bool get_isRipe() const { return isRipe; }
    const QString& get_name() const { return name; }
    int get_ripe_day() const { return ripe_day; }
    int get_big_grass_day() const { return big_grass_day; }
    int get_small_grass_day() const { return small_grass_day; }
    int get_plant_day() const { return plant_day; }
private:
    void show_big_grass() { setPixmap(big_grass); }
    void show_small_grass() { setPixmap(small_grass); }
    void show_ripe() { setPixmap(veg_pic); }
private:
    QPixmap veg_pic;
    QPixmap big_grass;
    QPixmap small_grass;

    bool isRipe;
    QString name;
    int ripe_day;
    int big_grass_day;
    int small_grass_day;
    int plant_day;
};

#endif // FIELD_H
