#ifndef STOREWIDGET_H
#define STOREWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QShowEvent>
#include <QDebug>
class StoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StoreWidget(QWidget *parent = 0);
    int chooseOption; //选择了第几项
    QTimer *haveBuyTimer;//购买计时器
    bool setChooseEnable;//是否可以购买
    QLabel *op[10]; // option

private:
    const int MaxOption = 10;
    const int init_x = 32;
    const int init_y = 92;
    const int interval = 48;
    const int length = 300;
    const int width = 32;
    int OptionNum; //有多少个选项
    int border_color_it;
    QGraphicsView *OptionBox;
    QWidget *StoreWin;
    QPainter *painter;
    QLabel *text1;
    QLabel *text2;
    QLabel *exitOption;
private:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);//当前类中的键盘事件与mainwindow中的键盘事件互不影响
    void showEvent(QShowEvent *);//重写窗口显示事件,为了使当前窗口获得焦点
public:
    void initialStoreWin();//初始化商店界面
    void set_store(const QStringList&, const QVector<int>&);
};

#endif // STOREWIDGET_H
