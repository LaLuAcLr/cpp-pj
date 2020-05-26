#ifndef FARM_H
#define FARM_H
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QKeyEvent>
#include "map.h"
#include "StartMenu.h"
#include "storewidget.h"
class Farm : public QWidget
{
    Q_OBJECT
public:
    explicit Farm(QWidget *parent = 0);
private:
    void init_farm();
    void init_mapWidget();  // farm map
    void init_map();
    void init_Character();
    void init_store();
    void init_infowidget(); // info column
private:
    QGridLayout *MapLayout;
    QHBoxLayout *MainLayout;
public:
    void regenarate_Character();
    void regenarate_Map();
private:
    QWidget *mainWidget;
    QWidget *mapWidget;
    QWidget *map[13][15];
    QWidget *Character;

    int     Day;
public slots:
    void add_day_func();

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
    QComboBox *seed;
    QLabel *label_seed;
    QLabel *label_day;
    QPushButton *add_day;
    QPushButton *save;
    QPushButton *load;
public:
    Map m;
    StoreWidget *Store;
    QPushButton *mainmenu;
};

#endif // FARM_H
