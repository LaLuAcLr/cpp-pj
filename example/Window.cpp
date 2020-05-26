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
    farm->setFocus();
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
    case Qt::Key_E:
    {
        qDebug()<<"E";
        PortalJump();
        farm->regenarate_Map();
        break;
    }
    case Qt::Key_F:
    {
        qDebug()<<"F";
        Mapadd();
        farm->regenarate_Map();
        break;
    }
    case Qt::Key_G:
    {

        if(farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]>=40&&farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]<50)
        {
            OpenStore();
            qDebug()<<"g";
        }
        farm->regenarate_Map();
        break;
    }
    default: break;
    }
}
void Window::OpenStore()
{
    farm->Store->show();
}
void Window::Charactermove()
{
    switch(Direction)
    {
    case 1:
    {
        if(farm->m.direction==1)
        {
            if(farm->m.map[farm->m.floor][(farm->m.x)-1][farm->m.y]<10
                    ||farm->m.map[farm->m.floor][(farm->m.x)-1][farm->m.y]>=50)
                farm->m.x -= 1;
        }
        else
        {
            farm->m.direction=1;
        }
        break;
    }
    case 2:
    {
        if(farm->m.direction==2)
        {
            if(farm->m.map[farm->m.floor][(farm->m.x)+1][farm->m.y]<10
                    ||farm->m.map[farm->m.floor][(farm->m.x)+1][farm->m.y]>=50)
                farm->m.x += 1;
        }
        else
        {
            farm->m.direction=2;
        }
        break;
    }
    case 3:
    {
        if(farm->m.direction==3)
        {
            if(farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)-1]<10
                    ||farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)-1]>=50)
                farm->m.y -= 1;
            farm->m.direction=4;
        }
        else if(farm->m.direction==4)
        {
            if(farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)-1]<10
                    ||farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)-1]>=50)
                farm->m.y -= 1;
            farm->m.direction=3;
        }
        else
        {
            farm->m.direction=3;
        }
        break;
    }
    case 4:
    {
        if(farm->m.direction==5)
        {
            if(farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]<10
                    ||farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]>=50)
                farm->m.y += 1;
            farm->m.direction=6;
        }
        else if(farm->m.direction==6)
        {
            if(farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]<10
                    ||farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]>=50)
                farm->m.y += 1;
            farm->m.direction=5;
        }
        else
        {
            farm->m.direction=5;
        }
        break;
    }
    default:break;
    }
}
void Window::PortalJump()
{
    if(farm->m.map[farm->m.floor][farm->m.x][farm->m.y]>=50)
        farm->m.initialCharacterPos(farm->m.p[farm->m.map[farm->m.floor][farm->m.x][farm->m.y]-50]);
    else
        qDebug()<<"no portal";
}
void Window::Mapadd()
{
    switch(farm->m.direction)
    {
    case 1:farm->m.map[farm->m.floor][(farm->m.x)-1][farm->m.y]++;break;
    case 2:farm->m.map[farm->m.floor][(farm->m.x)+1][farm->m.y]++;break;
    case 3:farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)-1]++;break;
    case 4:farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)-1]++;break;
    case 5:farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]++;break;
    case 6:farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]++;break;
    default:break;
    }
}
