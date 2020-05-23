﻿#include "Window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setMinimumSize(840, 680);
    init_window();
}

void Window::show_farm()
{
    startmenu->hide();
    farm->show();
    this->resize(1140, 680);
}

void Window::show_mainmenu()
{
    farm->hide();
    startmenu->show();
    this->resize(840, 680);
}

void Window::init_window()
{
    startmenu = new StartMenu(this);
    farm = new Farm(this);
    farm->hide();
    startmenu->show();
    Direction = 0;

    connect(startmenu->button_start, SIGNAL(clicked()), this, SLOT(show_farm()));
    connect(farm->mainmenu, SIGNAL(clicked()), this, SLOT(show_mainmenu()));
}
void Window::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key())
    {
    case Qt::Key_W:
    {
        qDebug()<<"W";
        Direction = 1;
        Charactermove();
        farm->regenarate_Character();
        break;
    }
    case Qt::Key_S:
    {
        qDebug()<<"S";
        Direction = 2;
        Charactermove();
        farm->regenarate_Character();
        break;
    }
    case Qt::Key_A:
    {
        qDebug()<<"A";
        Direction = 3;
        Charactermove();
        farm->regenarate_Character();
        break;
    }
    case Qt::Key_D:
    {
        qDebug()<<"D";
        Direction = 4;
        Charactermove();
        farm->regenarate_Character();
        break;
    }
    default: break;
    }
}
void Window::Charactermove()
{
    switch(Direction)
    {
    case 1:
    {
        if(farm->m.map[farm->m.floor][(farm->m.x)-1][farm->m.y]<10)
            farm->m.x -= 1;
        break;
    }
    case 2:
    {
        if(farm->m.map[farm->m.floor][(farm->m.x)+1][farm->m.y]<10)
            farm->m.x += 1;
        break;
    }
    case 3:
    {
        if(farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)-1]<10)
            farm->m.y -= 1;
        break;
    }
    case 4:
    {
        if(farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]<10)
            farm->m.y += 1;
        break;
    }
    default:break;
    }
}
