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
#include <QHash>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include "map.h"
#include "StartMenu.h"
#include "storewidget.h"
#include "dialogue.h"
#include "character.h"
#include "Field.h"

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
    void init_dialogue();
    void init_infowidget(); // info column
    void init_fruit();
private:
    QGridLayout *MapLayout;
    QHBoxLayout *MainLayout;
public:
    void refresh_Character();
    void regenarate_Character();
    void regenarate_Map();
    void regenerate_Info();
    void interact_field(int i, int j);
private:
    QWidget *mainWidget;
    QWidget *mapWidget;
    QWidget *map[17][15];
    Field   *field[10][10];
    Veg     *veg[10][10];
    QHash<QString, QHash<QString, int>> fruit_list;
    int Day;
public slots:
    void add_day_func();
    void update_veg();
    void change_seed(QString);
    void change_tool(QString);
    void change_dic(int n, int x, int y);

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
    character *Character;
    Dialogue *dialogue;
    StoreWidget *Store;
    QPushButton *mainmenu;
};

#endif // FARM_H
