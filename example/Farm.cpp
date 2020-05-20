#include "Farm.h"
#include <QPixmap>
#include <QRectF>

Farm::Farm(QWidget *parent) :
    QMainWindow(parent)
{
    this->setMinimumSize(1040, 680);
    this->setMaximumSize(1040, 680);
    this->setWindowFlag(Qt::FramelessWindowHint);
    init_window();
    ShowFarm();
}

void Farm::init_window()
{
    MapLayout = new QHBoxLayout;
    MapLayout->setSpacing(0);

    init_mapWidget();
    init_infowidget();

    MapLayout->addWidget(mapWidget);
    MapLayout->addWidget(infoWidget);

    mainWidget->setLayout(MapLayout);
    mainWidget->setFocusPolicy(Qt::StrongFocus);

    this->setCentralWidget(mainWidget);
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
    QPixmap pixmap(":/interface/image/interface/man.png");
    avatar->setPixmap(pixmap);
    avatar->setGeometry(20, 20, 40, 40);

    label_stamina = new QLabel(infoWidget);
    label_stamina->setFont(fontLabel);
    label_stamina->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    label_stamina->setGeometry(140, 20, 40, 40);

    label_money = new QLabel(infoWidget);
    label_money->setFont(fontLabel);
    label_money->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    label_money->setGeometry(20, 70, 100, 30);

    label_tool = new QLabel(infoWidget);
    label_tool->setFont(fontLabel);
    label_tool->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    label_tool->setGeometry(20, 110, 65, 30);

    stamina = new QLabel(infoWidget);
    stamina->setFont(fontNum);
    stamina->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    stamina->setText("100");
    stamina->setGeometry(80, 20, 40, 40);

    money = new QLabel(infoWidget);
    money->setFont(fontNum);
    money->setStyleSheet("border-image: url(:/interface/image/interface/labelbg.png);");
    money->setText("2000");
    money->setGeometry(130, 70, 170, 30);

    infoWidget->setMinimumSize(300,680);
    infoWidget->setStyleSheet("color:white;border-image: url(:/interface/image/interface/infobg.png);");
}

void Farm::ShowFarm()
{
    mainWidget->show();
    mapWidget->show();
    infoWidget->show();
}
