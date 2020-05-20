#ifndef WINDOW_H
#define WINDOW_H
#include "StartMenu.h"
#include "Farm.h"
#include <QMainWindow>
#include <QWidget>

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private:
    StartMenu *startmenu;
    Farm *farm;
    QWidget *MainWidget;

private:
    void init_window();
    void show_farm();

};

#endif // WINDOW_H
