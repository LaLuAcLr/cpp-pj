#include "mainwindow.h"
#include "StartMenu.h"
#include "Farm.h"
#include <QDesktopWidget>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //一般如果建立在栈上不能运行，建立在堆上就能运行时，出现问题的原因是：变量没有初始化或者出现访问越界的情况
    StartMenu startmenu;
    startmenu.move((a.desktop()->width() - startmenu.width()) / 2, (a.desktop()->height() - 702) / 2);//移动窗口到屏幕中央
    //startmenu.show();
    Farm farm;
    farm.move((a.desktop()->width() - farm.width()) / 2, (a.desktop()->height() - 702) / 2);//移动窗口到屏幕中央
    farm.show();
    return a.exec();
}
