#include "Window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    init_window();
}

Window::~Window()
{

}

void Window::init_window()
{
    startmenu = new StartMenu(this);
    farm = new Farm(this);
    farm->setMinimumSize(1140, 680);
    farm->show();
    startmenu->hide();
}
