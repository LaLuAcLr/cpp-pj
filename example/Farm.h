#ifndef FARM_H
#define FARM_H
#include <QWidget>
#include "StartMenu.h"
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QGridLayout>
#include <QKeyEvent>
#include <QDebug>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QKeyEvent>
#include <QResizeEvent>//QResizeEvent 是主窗口的变化事件
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QPoint>
#include <QProgressBar>
#include "map.h"

class Farm : public QWidget
{
    Q_OBJECT
public:
    explicit Farm(QWidget *parent = 0);
    ~Farm();
public:
    void init_farm();
private:
    QPainter *painter;
    QGridLayout *MapLayout;
    QHBoxLayout *MainLayout;
    QGridLayout *CharacterLayout;
public:
    void init_mapWidget();  // farm map
    void init_map();
    void init_Character();
    void regenarate_Character();
private:
    QWidget *mainWidget;
    QWidget *mapWidget;
    QWidget *map[10][10];
    QWidget *Character;
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
    QPushButton *save;
    QPushButton *load;
public:
    Map m;
    QPushButton *mainmenu;
};

#endif // FARM_H
