#ifndef WINDOW_H
#define WINDOW_H
#include "StartMenu.h"
#include "Farm.h"
#include "storewidget.h"
#include "character.h"
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "namemenu.h"
class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);

private:
    StartMenu *startmenu;
    Farm *farm;
    Namemenu *namemenu;
    QWidget *MainWidget;
public slots:
    void show_farm();
    void show_mainmenu();
    void show_nameset();
    void keyPressEvent(QKeyEvent *ev);
    void OpenStore();
    void Opendialogue(int n);
    void BuyinStore();
    void load_func();
    void CheckBGMstate();//检查音乐状态
private:
    void init_window();
    void Charactermove(int);
    void PortalJump();
    void direction_field();
    void mine_or_fish();
    bool check_outbound();
    bool judge_interaction(bool op(int));
    void soundPlay(int CurrentIndex);
private://音效
    QMediaPlayer *BGM;
    QTimer *BGMTimer;
    QMediaPlayer *sound;

};

#endif // WINDOW_H
