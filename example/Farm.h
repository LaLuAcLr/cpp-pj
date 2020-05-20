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

class Farm : public QMainWindow
{
    Q_OBJECT
public:
    explicit Farm(QWidget *parent = 0);
public:
    void ShowFarm();
    void init_window();
private:
    QPainter *painter;
    QHBoxLayout *MapLayout;
private:
    //void paintEvent(QPaintEvent *);
public:
    void init_mapWidget();
private:
    QWidget *mainWidget;
    QWidget *mapWidget;
public:
    void init_infowidget();

private:
    QWidget *infoWidget;
    QLabel *avatar;
    QLabel *stamina;
    QLabel *label_stamina;
    QLabel *money;
    QLabel *label_money;
    QComboBox *tool;
    QLabel *label_tool;
    QPushButton *mainmenu;

};

#endif // FARM_H
