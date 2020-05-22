#include "Window.h"

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
    farm->setMinimumSize(1140, 680);
    farm->hide();
    startmenu->show();

    connect(startmenu->button_start, SIGNAL(clicked()), this, SLOT(show_farm()));
    connect(farm->mainmenu, SIGNAL(clicked()), this, SLOT(show_mainmenu()));
}



