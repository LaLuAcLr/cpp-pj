﻿#ifndef WINDOW_H
#define WINDOW_H
#include "StartMenu.h"
#include "Farm.h"
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>
#include <QDebug>

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);

private:
    StartMenu *startmenu;
    Farm *farm;
    QWidget *MainWidget;
    int Direction;
public slots:
    void show_farm();
    void show_mainmenu();
    void keyPressEvent(QKeyEvent *ev);
private:
    void init_window();
    void Charactermove();


};

#endif // WINDOW_H