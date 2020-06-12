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
    farm->m.role.name=namemenu->NameEdit->text();
    farm->regenerate_Info();
    farm->restart_farm();
    namemenu->hide();
    farm->show();
    farm->setFocus();
    this->resize(1140, 680);
    BGM->pause();
    BGM->setMedia(QUrl("qrc:/bgm/BGM2.mp3"));
    BGM->play();
    BGMTimer->start(10);
}
void Window::load_func() {
    QFile file(QApplication::applicationDirPath() + "/json/save.json");
    if(!file.open(QIODevice::ReadOnly))
        qDebug() << "read json file failed";
    QByteArray ba = file.readAll();
    QJsonParseError e;
    QJsonDocument json_doc = QJsonDocument::fromJson(ba, &e);
    QJsonObject root_object = json_doc.object();
    QJsonObject role_object = root_object.value("role").toObject();
    QJsonArray field_object = root_object.value("field").toArray();
    QJsonArray veg_object = root_object.value("veg").toArray();
    farm->regenerate_Info_Load(role_object);
    farm->refresh_Character_Load(role_object);
    qDebug()<<"day:";
    farm->reset_day(root_object.value("days").toInt());
    qDebug()<<"field:";
    farm->reset_field(field_object);
    qDebug()<<"veg:";
    farm->reset_veg(veg_object);
    farm->show();
    farm->setFocus();
    this->resize(1140, 680);
    file.close();
}
void Window::show_nameset()
{
    startmenu->hide();
    namemenu->show();
    namemenu->setFocus();

    qDebug()<<"name";
    qDebug()<<namemenu->NameEdit->text();
    farm->regenerate_Info();
}
void Window::show_mainmenu()
{
    farm->hide();
    startmenu->show();
    this->resize(840, 680);

    BGM->pause();
    BGM->setMedia(QUrl("qrc:/bgm/BGM3.mp3"));
    BGM->play();
    BGMTimer->start(10);
}

void Window::init_window()
{
    namemenu =new Namemenu(this);
    startmenu = new StartMenu(this);
    farm = new Farm(this);
    farm->hide();
    startmenu->show();
    BGM=new QMediaPlayer(this);//背景音乐
    BGM->setMedia(QUrl("qrc:/bgm/BGM3.mp3"));
    BGM->setVolume(30);

    BGMTimer=new QTimer(this);
    connect(BGMTimer,SIGNAL(timeout()),this,SLOT(CheckBGMstate()));
    connect(startmenu->button_start, SIGNAL(clicked()), this, SLOT(show_nameset()));
    connect(startmenu->button_load, SIGNAL(clicked()), this, SLOT(load_func()));
    connect(namemenu->SetDone,SIGNAL(clicked()), this, SLOT(show_farm()));
    connect(farm->mainmenu, SIGNAL(clicked()), this, SLOT(show_mainmenu()));
    connect(farm->Store->haveBuyTimer,SIGNAL(timeout()),this,SLOT(BuyinStore()));

    BGM->play();
    BGMTimer->start(10);
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
        mine_or_fish();
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
        if(judge_interaction([](int x) { return x>=20 && x<30; }))
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
            if(n >= 4 && farm->m.role.item.sp > n-4)
            {
                farm->set_princess();
            }
            else
                Opendialogue(n);
            qDebug()<<"Q";
        }
        break;
    }
    case Qt::Key_F12:
    {
        farm->m.role.money += 99999999999;
        farm->regenerate_Info();
    }
    default: break;
    }
}

void Window::OpenStore()
{
    farm->Store->show();
    farm->set_store_veg();
    farm->set_store_pickhead();
    farm->set_store_rod();
}
void Window::BuyinStore()
{
    farm->sound->stop();
    farm->sound->setMedia(QUrl("qrc:/bgm/pay.mp3"));
    farm->sound->play();
    if(farm->m.floor==0)
    {
        QStringList keys = farm->get_fruit_list().keys();
        int opt = farm->Store->chooseOption;
        int t = farm->m.role.money - farm->get_fruit_list()[keys[opt]]["seed_price"];
        if (t < 0) {
            farm->out_of_money();
            farm->Store->haveBuyTimer->stop();
            farm->Store->setFocus();
            return;
        }
        farm->m.role.money -= farm->get_fruit_list()[keys[opt]]["seed_price"];
        farm->m.role.item.seed[keys[opt]]++;
        farm->add_seed();
        farm->regenerate_Info();
        qDebug()<<"buy"<<farm->Store->chooseOption;
        farm->Store->haveBuyTimer->stop();
        farm->check_money();
        farm->Store->setFocus();
    }
    else if(farm->m.floor==1)
    {
        int opt = farm->Store->chooseOption;
        if(opt == 0){
            if (farm->m.role.item.tool["Pickhead"] == 3) return;
            QStringList keys = farm->get_pickhead_list().keys();
            qDebug()<<keys[2-farm->m.role.item.tool["Pickhead"]];
            int t = farm->m.role.money - farm->get_pickhead_list()[keys[2-farm->m.role.item.tool["Pickhead"]]];
            if (t < 0) {
                farm->out_of_money();
                farm->Store->haveBuyTimer->stop();
                farm->Store->setFocus();
                return;
            }
            farm->m.role.money -= farm->get_pickhead_list()[keys[2-farm->m.role.item.tool["Pickhead"]]];
            farm->m.role.item.tool["Pickhead"]++;
        }
        else if(opt == 1){
            if (farm->m.role.item.sp == 4) return;
            QStringList keys = farm->get_sp_list().keys();
            int t[4] = {1, 3, 0, 2};    // jewel, spoon, jade, ring
            qDebug()<<keys[t[farm->m.role.item.sp]];
            int ti = farm->m.role.money - farm->get_sp_list()[keys[t[farm->m.role.item.sp]]];
            if (ti < 0) {
                farm->out_of_money();
                farm->Store->haveBuyTimer->stop();
                farm->Store->setFocus();
                return;
            }
            farm->m.role.money -= farm->get_sp_list()[keys[t[farm->m.role.item.sp]]];
            farm->m.role.item.sp++;
        }
        farm->regenerate_Info();
        //qDebug()<<"buy"<<farm->Store->chooseOption;
        farm->Store->haveBuyTimer->stop();
        farm->check_money();
        farm->Store->setFocus();
        farm->set_store_pickhead();
    }
    else if(farm->m.floor == 3)
    {
        int opt = farm->Store->chooseOption;
        if(opt == 0){
            if (farm->m.role.item.tool["Rod"] == 3) return;
            QStringList keys = farm->get_rod_list().keys();
            qDebug()<<keys[2-farm->m.role.item.tool["Rod"]];
            int t = farm->m.role.money - farm->get_rod_list()[keys[2-farm->m.role.item.tool["Rod"]]];
            if (t < 0) {
                farm->out_of_money();
                farm->Store->haveBuyTimer->stop();
                farm->Store->setFocus();
                return;
            }
            farm->m.role.money -= farm->get_rod_list()[keys[2-farm->m.role.item.tool["Rod"]]];
            farm->m.role.item.tool["Rod"]++;
        }
        farm->regenerate_Info();
        //qDebug()<<"buy"<<farm->Store->chooseOption;
        farm->Store->haveBuyTimer->stop();
        farm->check_money();
        farm->Store->setFocus();
        farm->set_store_rod();
    }
}
void Window::Opendialogue(int n)
{
    //farm->dialogue->hide();
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
    {
        if(farm->m.floor == 2)
        {
            BGM->pause();
            BGM->setMedia(QUrl("qrc:/bgm/BGM2.mp3"));
            BGM->play();
            BGMTimer->start(10);
        }
        else if(farm->m.floor == 3)
        {
            BGM->pause();
            BGM->setMedia(QUrl("qrc:/bgm/BGM2.mp3"));
            BGM->play();
            BGMTimer->start(10);
        }
        farm->m.initialCharacterPos(farm->m.p[farm->m.map[farm->m.floor][farm->m.x][farm->m.y]-50]);
        if (farm->m.floor == 5)
            BGM->setVolume(4);
        else if(farm->m.floor == 2)
        {
            BGM->pause();
            BGM->setMedia(QUrl("qrc:/bgm/BGM4.mp3"));
            BGM->play();
            BGMTimer->start(10);
        }
        else if(farm->m.floor == 3)
        {
            BGM->pause();
            BGM->setMedia(QUrl("qrc:/bgm/BGM5.mp3"));
            BGM->play();
            BGMTimer->start(10);
        }
        else
        {
            BGM->setVolume(30);
        }

    }
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

void Window::mine_or_fish()
{
    if(check_outbound()) return;
    if(!judge_interaction([](int x) { return (x==30 || x==31); })) return;
    if(farm->m.role.stamina >= 10)
    {
        if(farm->m.role.tool.name=="Pickhead" && judge_interaction([](int x) { return x==30; }))
        {
            farm->sound->stop();
            farm->sound->setMedia(QUrl("qrc:/bgm/parry.mp3"));
            farm->sound->play();
            farm->mine.do_mining(farm->m.role.item.tool["Pickhead"]);
            farm->set_message(farm->mine.get_mineral[farm->mine.mineral]);
            farm->start_msgtimer();
            farm->m.role.stamina -= 10;
            farm->m.role.money += farm->mine.minemoney[farm->mine.mineral];
            farm->regenerate_Info();
        }
        else if(farm->m.role.tool.name=="Rod" && judge_interaction([](int x) { return x==31; }))
        {
            farm->sound->stop();
            farm->sound->setMedia(QUrl("qrc:/bgm/stomp.mp3"));
            farm->sound->play();
            farm->fishes.do_fishing(farm->m.role.item.tool["Rod"]);
            farm->set_message(farm->fishes.get_fish[farm->fishes.fish]);
            farm->start_msgtimer();
            farm->m.role.stamina -= 10;
            farm->m.role.money += farm->fishes.fishmoney[farm->fishes.fish];
            farm->regenerate_Info();
        }
    }
    else
    {
        farm->set_message("You don't have enough stamina to do that");
        farm->start_msgtimer();
    }
}
void Window::CheckBGMstate()
{
   if(BGM->state()==0)//0代表停止 1代表播放 2代表暂停
   {
       BGM->play();
   }
}

