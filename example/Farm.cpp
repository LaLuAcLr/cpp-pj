#include "Farm.h"
#include <QPixmap>
#include <QRectF>
#include <QStringList>

Farm::Farm(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(1040, 680);
    init_farm();
}

void Farm::init_farm()
{
    MapLayout = new QGridLayout;
    MapLayout->setContentsMargins(0, 0, 0, 0);
    MapLayout->setSpacing(0);
    MainLayout = new QHBoxLayout;
    MainLayout->setContentsMargins(0, 0, 0, 0);
    MainLayout->setSpacing(0);

    init_mapWidget();
    init_infowidget();

    MapLayout->addWidget(mapWidget);
    MainLayout->addLayout(MapLayout);
    MainLayout->addWidget(infoWidget);

    this->setLayout(MainLayout);

}

void Farm::init_mapWidget()
{
    mapWidget = new QWidget(this);
    mapWidget->setMinimumSize(840, 680);
    mapWidget->setStyleSheet("border-image:url(:/interface/image/interface/farm.png)");
}

void Farm::init_infowidget()
{
    infoWidget = new QWidget(this);
    QFont fontLabel("Consolas", 12);
    QFont fontNum("Consolas", 10);
    QFont fontName("Consolas", 10);
    QString button_style="QPushButton{border-image:url(:/interface/image/interface/labelbg.png);color:white;border-radius:10px;}"
                         "QPushButton:hover{border-image:url(:/interface/image/interface/PushButtonhoverbg.png); color: black;}"
                         "QPushButton:pressed{border-image:url(:/interface/image/interface/PushButtonPressbg.png);}";

    avatar = new QLabel(infoWidget);
    avatar->setStyleSheet("border-image:url(:/interface/image/interface/man.png);");
    avatar->setGeometry(20, 20, 40, 40);

    name = new QLabel(infoWidget);
    name->setFont(fontName);
    name->setText("LaLuAcLr");
    name->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    name->setGeometry(150, 20, 100, 40);

    label_stamina = new QLabel(infoWidget);
    label_stamina->setFont(fontLabel);
    label_stamina->setText("Stamina:");
    label_stamina->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    label_stamina->setGeometry(20, 70, 100, 40);

    label_money = new QLabel(infoWidget);
    label_money->setFont(fontLabel);
    label_money->setText("Money:");
    label_money->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    label_money->setGeometry(20, 110, 100, 40);

    label_tool = new QLabel(infoWidget);
    label_tool->setFont(fontLabel);
    label_tool->setText("Tool:");
    label_tool->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    label_tool->setGeometry(20, 150, 100, 40);

    stamina = new QLabel(infoWidget);
    stamina->setFont(fontNum);
    stamina->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    stamina->setText("100");
    stamina->setGeometry(150, 70, 40, 40);

    money = new QLabel(infoWidget);
    money->setFont(fontNum);
    money->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    money->setText("2000");
    money->setGeometry(150, 110, 40, 40);

    tool = new QComboBox(infoWidget);
    tool->addItems(QStringList{"None", "Hoe", "Seed", "Knife", "Pot"});
    tool->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    tool->setGeometry(150, 160, 100, 20);

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
    infoWidget->setStyleSheet("color:white;border-image: url(:/interface/image/interface/infobg.png);");
}
