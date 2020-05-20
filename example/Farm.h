#ifndef FARM_H
#define FARM_H
#include <QWidget>
#include <QPainter>
#include "StartMenu.h"
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QGridLayout>

class Farm : public QWidget
{
    Q_OBJECT
public:
    explicit Farm(QWidget *parent = 0);
public:
    void init_farm();
private:
    QPainter *painter;
    QGridLayout *MapLayout;
    QHBoxLayout *MainLayout;
private:
    //void paintEvent(QPaintEvent *);
public:
    void init_mapWidget();  // farm map
private:
    QWidget *mainWidget;
    QWidget *mapWidget;
public:
    void init_infowidget(); // info column

private:
    QWidget *infoWidget;    // info column
    QLabel *avatar;
    QLabel *name;
    QLabel *stamina;
    QLabel *label_stamina;
    QLabel *money;
    QLabel *label_money;
    QComboBox *tool;
    QLabel *label_tool;
    QPushButton *mainmenu;
    QPushButton *save;
    QPushButton *load;
};

#endif // FARM_H
