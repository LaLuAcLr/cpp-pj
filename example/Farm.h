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
#include <QMessageBox>
#include <QStringList>
#include <QDebug>

#include "map.h"
#include "StartMenu.h"
#include "storewidget.h"
#include "dialogue.h"
#include "character.h"
#include "Field.h"
#include "collect.h"

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
    void init_pickhead();
    void init_sp();
    void init_rod();
    void init_GetitemWin();

private:
    QGridLayout *MapLayout;
    QHBoxLayout *MainLayout;
public:
    void refresh_Character();
    void refresh_Character_Load(QJsonObject);
    void regenarate_Character();
    void regenarate_Map();
    void regenerate_Info();
    void regenerate_Info_Load(QJsonObject);
    void interact_field(int i, int j);
    void show_field();
    void hide_field();
    void set_message(QString m) { msg = m; }
    QString get_message() const { return msg; }
    void start_msgtimer() { GetitemTimer->start(100); }
    void set_store_veg();
    void set_store_pickhead();
    void set_store_rod();
    const QMap<QString, QHash<QString, int>>& get_fruit_list() const { return fruit_list; }
    const QMap<QString, int>& get_sp_list() const { return sp_list; }
    const QMap<QString, int>& get_pickhead_list() const { return pickhead_list; }
    const QMap<QString, int>& get_rod_list() const { return rod_list; }
    void check_stamina();
    void check_money();
    void add_seed();
    void remove_seed();
    void set_princess();
    void reset_field(QJsonArray);
    void reset_veg(QJsonArray);
    void reset_day(int);
private:
    QWidget *mainWidget;
    QWidget *mapWidget;
    QLabel  *map[17][15];
    Field   *field[10][10];
    Veg     *veg[10][10];
    QString msg;
    QTimer  *GetitemTimer;
    QLabel  *GetitemsShow;
    QMap<QString, QHash<QString, int>> fruit_list;
    QMap<QString, int> pickhead_list;
    QMap<QString, int> sp_list;
    QMap<QString, int> rod_list;
    int GetitemNum;
    int Day;
public slots:
    void add_day_func();
    void save_func();
    void update_veg();
    void change_seed(QString);
    void change_tool(QString);
    void change_dic(int n, int x, int y);
    void GetitemWinshow();

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
    mining mine;
    fishing fishes;
    QPushButton *mainmenu;


};

#endif // FARM_H
