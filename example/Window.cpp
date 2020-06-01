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
    farm->refresh_Character();
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

    connect(startmenu->button_start, SIGNAL(clicked()), this, SLOT(show_farm()));
    connect(farm->mainmenu, SIGNAL(clicked()), this, SLOT(show_mainmenu()));
    connect(farm->Store->haveBuyTimer,SIGNAL(timeout()),this,SLOT(BuyinStore()));
}
bool Window::check_outbound()
{
    if (farm->Character->get_curr_dir()==0 && farm->m.x==0)
        return true;
    if (farm->Character->get_curr_dir()==1 && farm->m.x==16)
        return true;
    if (farm->Character->get_curr_dir()==2 && farm->m.y==16)
        return true;
    if (farm->Character->get_curr_dir()==3 && farm->m.y==0)
        return true;
    return false;
}
bool Window::judge_interaction(bool op(int))
{
    if (farm->Character->get_curr_dir()==0 && op(farm->m.map[farm->m.floor][(farm->m.x)-1][farm->m.y]))
        return true;
    if (farm->Character->get_curr_dir()==1 && op(farm->m.map[farm->m.floor][(farm->m.x)+1][(farm->m.y)]))
        return true;
    if (farm->Character->get_curr_dir()==2 && op(farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]))
        return true;
    if (farm->Character->get_curr_dir()==3 && op(farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)-1]))
        return true;
    return false;
}
void Window::keyPressEvent(QKeyEvent *ev)
{
    if (farm->Character->get_isWalking()) return;
    switch(ev->key())
    {
    case Qt::Key_W:
    {
        qDebug()<<"W";
        Charactermove(0);
        break;
    }
    case Qt::Key_S:
    {
        qDebug()<<"S";
        Charactermove(1);
        break;
    }
    case Qt::Key_D:
    {
        qDebug()<<"D";
        Charactermove(2);
        break;
    }
    case Qt::Key_A:
    {
        qDebug()<<"A";
        Charactermove(3);
        break;
    }
    case Qt::Key_E:
    {
        qDebug()<<"E";
        PortalJump();
        farm->set_store_veg();
        farm->regenarate_Map();
        break;
    }
    case Qt::Key_F:
    {
        qDebug()<<"F";
        direction_field();
        break;
    }
    case Qt::Key_G:
    {
        if(check_outbound()) return;
        if(judge_interaction([](int x) { return x==40; }))
        {
            OpenStore();
            qDebug()<<"g";
        }
        farm->regenarate_Map();
        break;
    }
    case Qt::Key_Q:
    {
        if(check_outbound()) return;
        if(judge_interaction([](int x) { return x>=20 && x<=30; }))
        {
            int n=0;
            if(farm->Character->get_curr_dir()==0)
            {
                n=farm->m.map[farm->m.floor][(farm->m.x)-1][farm->m.y]-20;
                farm->change_dic(0,(farm->m.x)-1,farm->m.y);
            }
            else if(farm->Character->get_curr_dir()==1)
            {
                n=farm->m.map[farm->m.floor][(farm->m.x)+1][(farm->m.y)]-20;
                farm->change_dic(1,(farm->m.x)+1,farm->m.y);
            }
            else if(farm->Character->get_curr_dir()==2)
            {
                n=farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]-20;
                farm->change_dic(2,farm->m.x,(farm->m.y)+1);
            }
            else
            {
                n=farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)-1]-20;
                farm->change_dic(3,farm->m.x,(farm->m.y)-1);
            }
            Opendialogue(n);
            qDebug()<<"Q";
        }
        break;
    }
    default: break;
    }
}

void Window::OpenStore()
{
    farm->Store->show();
}
void Window::BuyinStore()
{
    QStringList keys = farm->get_fruit_list().keys();
    int opt = farm->Store->chooseOption;
    farm->m.role.money -= farm->get_fruit_list()[keys[opt]]["seed_price"];
    farm->m.role.item.seed[keys[opt]]++;
    farm->add_seed();
    farm->regenerate_Info();
    qDebug()<<"buy"<<farm->Store->chooseOption;
    farm->Store->haveBuyTimer->stop();
    farm->check_money();
    farm->Store->setFocus();
}
void Window::Opendialogue(int n)
{
    farm->dialogue->initialStoreWin(n);
    farm->dialogue->show();
}
void Window::Charactermove(int dir)
{
    switch(dir)
    {
    case 0:
    {
        if(farm->Character->get_curr_dir()==0)     // up
        {
            if(farm->m.x == 0) {
                farm->Character->total_move(0);
                return;
            }
            if(farm->m.map[farm->m.floor][(farm->m.x)-1][farm->m.y]<10
                    ||farm->m.map[farm->m.floor][(farm->m.x)-1][farm->m.y]>=50)
            {
                farm->m.x -= 1;
                farm->Character->total_move(0);
            }
        }
        else
        {
            farm->Character->turn_direction(0);
        }
        break;
    }
    case 1:
    {
        if(farm->Character->get_curr_dir()==1)     // down
        {
            if(farm->m.x == 16) {   // 17-1 tile
                farm->Character->total_move(1);
                return;
            }
            if(farm->m.map[farm->m.floor][(farm->m.x)+1][farm->m.y]<10
                    ||farm->m.map[farm->m.floor][(farm->m.x)+1][farm->m.y]>=50)
            {
                farm->m.x += 1;
                farm->Character->total_move(1);
            }
        }
        else
        {
            farm->Character->turn_direction(1);
        }
        break;
    }
    case 2:
    {
        if(farm->Character->get_curr_dir()==2)     // right
        {
            if(farm->m.y == 14) {
                farm->Character->total_move(2);
                return;
            }
            if(farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]<10
                    ||farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)+1]>=50)
            {
                farm->m.y += 1;
                farm->Character->total_move(2);
            }
        }
        else
        {
            farm->Character->turn_direction(2);
        }
        break;
    }
    case 3:
    {
        if(farm->Character->get_curr_dir()==3)     // left
        {
            if(farm->m.y == 0) {
                farm->Character->total_move(3);
                return;
            }
            if(farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)-1]<10
                    ||farm->m.map[farm->m.floor][farm->m.x][(farm->m.y)-1]>=50)
            {
                farm->m.y -= 1;
                farm->Character->total_move(3);
            }
        }
        else
        {
            farm->Character->turn_direction(3);
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

void Window::direction_field()
{
    if(check_outbound()) return;
    if (farm->Character->get_curr_dir()==0 && farm->m.map[farm->m.floor][farm->m.x-1][farm->m.y]==2)   // up
        farm->interact_field(farm->m.x-5, farm->m.y-4);   // veg[i][j]
    else if (farm->Character->get_curr_dir()==1 && farm->m.map[farm->m.floor][farm->m.x+1][farm->m.y]==2)  // down
        farm->interact_field(farm->m.x-3, farm->m.y-4);
    else if (farm->Character->get_curr_dir()==2 && farm->m.map[farm->m.floor][farm->m.x][farm->m.y+1]==2)  // right
        farm->interact_field(farm->m.x-4, farm->m.y-3);
    else if (farm->Character->get_curr_dir()==3 && farm->m.map[farm->m.floor][farm->m.x][farm->m.y-1]==2)  // left
        farm->interact_field(farm->m.x-4, farm->m.y-5);
}

