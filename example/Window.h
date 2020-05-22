#ifndef WINDOW_H
#define WINDOW_H
#include "StartMenu.h"
#include "Farm.h"
#include <QMainWindow>
#include <QWidget>
#include <QKeyEvent>

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);

private:
    StartMenu *startmenu;
    Farm *farm;
    QWidget *MainWidget;

public slots:
    void show_farm();
    void show_mainmenu();

private:
    void init_window();


};

#endif // WINDOW_H
