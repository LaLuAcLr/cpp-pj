#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QShowEvent>
class Dialogue : public QWidget
{
    Q_OBJECT
public:
    explicit Dialogue(QWidget *parent = 0);
    int chooseOption; //选择了第几项
    int Times;
    QTimer *haveBuyTimer;//购买计时器
    bool setChooseEnable;//是否可以购买
    bool StoreWinisShow;//商店窗口是否显示
private:
    int OptionNum; //有多少个选项
    int border_color_it;
    int npcchoose;
    QString OptionBoxColor[6]= {"FFFFFF", "CCCCCC", "999999", "666666", "999999", "CCCCCC"};
    QString NPC_name[5]={"NPC1","NPC2","NPC3","NPC4","NPC5"};
    QString NPC_words[10][5];
    QTimer *OptionBoxTimer;
    QGraphicsView *OptionBox;
    QWidget *StoreWin;
    QLabel *text1;
    QLabel *text2;
    QLabel *op1;
    QLabel *exitOption;
private:
    void keyPressEvent(QKeyEvent *event);//当前类中的键盘事件与mainwindow中的键盘事件互不影响
    void showEvent(QShowEvent *);//重写窗口显示事件,为了使当前窗口获得焦点
    void initialwords();
public slots:
    void initialStoreWin(int n);//初始化对话界面
    void OptionBoxborderChanged();
};
#endif // DIALOGUE_H
