#include "Farm.h"
#include <QStringList>
#include <QKeyEvent>

Farm::Farm(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(1140, 680);
    init_farm();
}

void Farm::init_farm()
{
    Day = 1;

    MainLayout = new QHBoxLayout(this);
    MainLayout->setContentsMargins(0, 0, 0, 0);
    MainLayout->setSpacing(0);

    init_mapWidget();
    init_infowidget();

    MainLayout->addWidget(mapWidget);
    MainLayout->addWidget(infoWidget);

    MapLayout = new QGridLayout(mapWidget);
    MapLayout->setContentsMargins(0, 0, 0, 0);
    MapLayout->setSpacing(0);
    init_map();
    init_Character();
    init_store();
}

void Farm::init_mapWidget()
{
    mapWidget = new QWidget();
    mapWidget->setMinimumSize(840, 680);
    mapWidget->setStyleSheet("border-image:url(:/now/farm.png);");

}

void Farm::init_store()
{
    Store=new StoreWidget(this);
    Store->setGeometry(292,192,256,352);
    Store->hide();
}

void Farm::init_map()
{
    int i, j;
    for (i=0;i<13;++i)
    {
        for (j=0;j<15;++j)
        {
            map[i][j] = new QWidget();
            map[i][j]->setMinimumSize(64, 45);

            if(m.map[m.floor][i][j]>=10&&m.map[m.floor][i][j]<20)
                map[i][j]->setStyleSheet(m.TerrainString[m.map[m.floor][i][j]-10]);
            else if(m.map[m.floor][i][j]>=50)
                map[i][j]->setStyleSheet("border-image:url(:/now/box.png);");
            else if(m.map[m.floor][i][j]>=40&&m.map[m.floor][i][j]<50){
                map[i][j]->setStyleSheet("border-image:url(:/now/man.png);");
                //map[i][j]->setMinimumSize(100,100);
            }
            else
                map[i][j]->setStyleSheet("border-image:url();");
            MapLayout->addWidget(map[i][j],i,j);
        }
    }
}
void Farm::init_Character()
{
    Character = new QWidget();
    Character->setMinimumSize(64, 45);
    Character->setStyleSheet(m.CharacterString[m.direction-1]);
    MapLayout->addWidget(Character,m.x,m.y);
}
void Farm::regenarate_Character()
{
    Character->hide();
    Character = new QWidget();
    Character->setMinimumSize(64, 45);
    Character->setStyleSheet(m.CharacterString[m.direction-1]);
    MapLayout->addWidget(Character,m.x,m.y);
}
void Farm::regenarate_Map()
{
    int i, j;
    for (i=0;i<13;++i)
    {
        for (j=0;j<15;++j)
        {
            map[i][j]->hide();
        }
    }
    for (i=0;i<13;++i)
    {
        for (j=0;j<15;++j)
        {
            map[i][j] = new QWidget();
            map[i][j]->setMinimumSize(64, 45);

            if(m.map[m.floor][i][j]>=10&&m.map[m.floor][i][j]<20)
                map[i][j]->setStyleSheet(m.TerrainString[m.map[m.floor][i][j]-10]);
            else if(m.map[m.floor][i][j]>=50)
                map[i][j]->setStyleSheet("border-image:url(:/now/box.png);");
            else if(m.map[m.floor][i][j]>=40&&m.map[m.floor][i][j]<50)
                map[i][j]->setStyleSheet("border-image:url(:/now/man.png);");
            else
                map[i][j]->setStyleSheet("border-image:url();");
            MapLayout->addWidget(map[i][j],i,j);
        }
    }
    regenarate_Character();
}
void Farm::add_day_func()
{
    Day++;
    QString day_string = QString::number(Day);
    label_day->setText("This is Day " + day_string);
}
void Farm::init_infowidget()
{
    infoWidget = new QWidget(this);
    infoWidget->setFocusPolicy(Qt::NoFocus);
    QFont fontLabel("Consolas", 12);
    QFont fontNum("Consolas", 10);
    QFont fontName("Consolas", 10);
    QString button_style="QPushButton{border-image:url(:/now/labelbg.png);color:white;border-radius:10px;}"
                         "QPushButton:hover{border-image:url(:/now/PushButtonhoverbg.png); color: black;}"
                         "QPushButton:pressed{border-image:url(:/now/PushButtonPressbg.png);}";

    avatar = new QLabel(infoWidget);
    avatar->setStyleSheet("border-image:url(:/now/man.png);");
    avatar->setGeometry(20, 20, 40, 40);

    name = new QLabel(infoWidget);
    name->setFont(fontName);
    name->setText("LaLuAcLr");
    name->setStyleSheet("border-image: url(:/now/labelbg.png);");
    name->setGeometry(150, 20, 100, 40);

    label_stamina = new QLabel(infoWidget);
    label_stamina->setFont(fontLabel);
    label_stamina->setText("Stamina:");
    label_stamina->setStyleSheet("border-image: url(:/now/labelbg.png);");
    label_stamina->setGeometry(20, 70, 100, 40);

    label_money = new QLabel(infoWidget);
    label_money->setFont(fontLabel);
    label_money->setText("Money:");
    label_money->setStyleSheet("border-image: url(:/now/labelbg.png);");
    label_money->setGeometry(20, 110, 100, 40);

    label_tool = new QLabel(infoWidget);
    label_tool->setFont(fontLabel);
    label_tool->setText("Tool:");
    label_tool->setStyleSheet("border-image: url(:/now/labelbg.png);");
    label_tool->setGeometry(20, 150, 100, 40);

    label_seed = new QLabel(infoWidget);
    label_seed->setFont(fontLabel);
    label_seed->setText("Seed:");
    label_seed->setStyleSheet("border-image: url(:/now/labelbg.png);");
    label_seed->setGeometry(20, 190, 100, 40);

    stamina = new QLabel(infoWidget);
    stamina->setFont(fontNum);
    stamina->setStyleSheet("border-image: url(:/now/labelbg.png);");
    stamina->setText("100");
    stamina->setGeometry(150, 70, 40, 40);

    money = new QLabel(infoWidget);
    money->setFont(fontNum);
    money->setStyleSheet("border-image: url(:/now/labelbg.png);");
    money->setText("2000");
    money->setGeometry(150, 110, 40, 40);

    tool = new QComboBox(infoWidget);
    tool->addItems(QStringList{"None", "Hoe", "Seed", "Knife", "Pot"});
    tool->setStyleSheet("border-image: url(:/now/labelbg.png);");
    tool->setGeometry(150, 160, 100, 20);

    seed = new QComboBox(infoWidget);
    seed->addItems(QStringList{"Apple", "Pear"});
    seed->setStyleSheet("border-image: url(:/now/labelbg.png);");
    seed->setGeometry(150, 200, 100, 20);

    label_day = new QLabel(infoWidget);
    label_day->setFont(fontLabel);
    label_day->setStyleSheet("border-image: url(:/now/labelbg.png);");
    QString day_string = QString::number(Day);
    label_day->setText("This is Day " + day_string);
    label_day->setGeometry(20, 400, 200, 40);

    add_day = new QPushButton(infoWidget);
    add_day->setText("Add a Day");
    add_day->setStyleSheet(button_style);
    add_day->setGeometry(20, 450, 100, 40);
    connect(add_day, SIGNAL(clicked()), this, SLOT(add_day_func()));

    save = new QPushButton(infoWidget);
    save->setText("Save");
    save->setStyleSheet(button_style);
    save->setGeometry(20, 500, 100, 40);

    load = new QPushButton(infoWidget);
    load->setText("Load");
    load->setStyleSheet(button_style);
    load->setGeometry(20, 550, 100, 40);

    mainmenu = new QPushButton(infoWidget);
    mainmenu->setText("MainMenu");
    mainmenu->setStyleSheet(button_style);
    mainmenu->setGeometry(20, 600, 100, 40);

    infoWidget->setMinimumSize(300,680);
    infoWidget->setStyleSheet("color:white; border-image: url(:/now/infobg.png);");
}


