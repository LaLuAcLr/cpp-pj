#include "StartMenu.h"
#include <QPalette>
#include <QPixmap>
#include <QFont>
#include <QRectF>
#include <QStyleFactory>

StartMenu::StartMenu(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(840, 680);
    this->setMaximumSize(840, 680);
    this->setWindowFlag(Qt::FramelessWindowHint);

    msgLabel = new QLabel(this);
    msgLabel->setGeometry(380,440,100,75);
    msgLabel->setStyleSheet("color:white");
    msgLabel->setFont(QFont("Consolas",13));
    msgLabel->hide();

    probar = new QProgressBar(this);//进度条
    probar->setStyle(QStyleFactory::create("fusion"));
    probar->setGeometry(180,500,480,15);
    probar->setTextVisible(true);
    probar->hide();

    timer = new QTimer(this);

    QFont font("Consolas" ,16, 55);
    QString button_style="QPushButton{background-color:transparent;color:white;border-radius:5px;}"
                         "QPushButton:hover{background-color:palegreen; color: orangered;}"
                         "QPushButton:pressed{background-color:aquamarine;border-style:inset;}";

    button_start = new QPushButton(this);
    button_start->setGeometry(360, 275, 150, 35);
    button_start->setText("Start");
    button_start->setStyleSheet(button_style);
    button_start->setFont(font);
    connect(button_start, SIGNAL(clicked()), this, SLOT(NewGame()));

    button_load = new QPushButton(this);
    button_load->setGeometry(360, 320, 150, 35);
    button_load->setText("Load");
    button_load->setStyleSheet(button_style);
    button_load->setFont(font);

    button_quit = new QPushButton(this);
    button_quit->setGeometry(360, 365, 150, 35);
    button_quit->setText("Quit");
    button_quit->setStyleSheet(button_style);
    button_quit->setFont(font);
    connect(button_quit, SIGNAL(clicked()), this, SLOT(Quit()));

    button_about = new QPushButton(this);
    button_about->setGeometry(360, 410, 150, 35);
    button_about->setText("About");
    button_about->setStyleSheet(button_style);
    button_about->setFont(font);
    connect(button_about, SIGNAL(clicked()), this, SLOT(ShowAbout()));
}

void StartMenu::ShowMainMenu()
{
    button_start->show();
    button_load->show();
    button_quit->show();
    button_about->show();
}

void StartMenu::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    QImage pixmap(":/interface/image/interface/startmenu.png");
    painter->drawImage(QRectF(0, 0, 840, 680), pixmap);
    painter->end();
}

void StartMenu::Quit()
{
    QMessageBox message(QMessageBox::Question, "Quit", "Do you want to quit?",
                        QMessageBox::Yes | QMessageBox::No, this);
    message.setIconPixmap(QPixmap(":/info/image/information/quit.png"));
    message.setWindowIcon(QIcon(":/info/image/information/about.ico"));
    message.setDefaultButton(QMessageBox::No);
    message.setButtonText(QMessageBox::Yes, QString("Yes"));
    message.setButtonText(QMessageBox::No, QString("No"));
    if(message.exec()==QMessageBox::Yes)
        qApp->quit();
    else
        return;
}

void StartMenu::ShowAbout()
{
    QMessageBox message(QMessageBox::Information,"About",
                        "Written By ysr, thd, wm, szj, in FDU, 2020.05",QMessageBox::Ok,this);
    message.setIconPixmap(QPixmap(":/info/image/information/about.ico"));
    message.setButtonText(QMessageBox::Ok, QString("Close"));
    message.setDefaultButton(QMessageBox::Ok);
    message.exec();
}

void StartMenu::NewGame()
{

}
