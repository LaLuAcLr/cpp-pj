#include "dialogue.h"

Dialogue::Dialogue(QWidget *parent) : QWidget(parent)
{
    initialStoreWin(0);

}
void Dialogue::initialwords()
{
    NPC_words[0][0]="这里是自己家的农场";
    NPC_words[0][1]="在左侧的下拉菜单中可以选择工具和种子";
    NPC_words[0][2]="按F可以进行耕种和收获，每次行动会消耗一定体力值";
    NPC_words[0][3]="点击右侧的增加天数可以进入新的一天";
    NPC_words[0][4]="加油工作吧！";

    NPC_words[1][0]="这里是连接各个地图的十字路口";
    NPC_words[1][1]="在左边的商店里可以购买珠宝或采矿工具";
    NPC_words[1][2]="左侧通往LaLuAcLr亲王的城堡";
    NPC_words[1][3]="下面通往黑市商人thd的采矿场";
    NPC_words[1][4]="左边通往勇者wm的渔场";

    NPC_words[2][0]="这里是采矿场";
    NPC_words[2][1]="你可以走到矿石前按F进行采矿";
    NPC_words[2][2]="不同的地段会随机产生价格不等的矿石";
    NPC_words[2][3]="更好的装备可以提升你采到好矿石的概率";
    NPC_words[2][4]="祝你好运";

    NPC_words[3][0]="这里是渔场";
    NPC_words[3][1]="在右边红色的商店中你可以购买捕鱼工具";
    NPC_words[3][2]="在左上角的捕鱼屋按F可以进行捕鱼";
    NPC_words[3][3]="更好的装备可以让你钓鱼的成功率增加";
    NPC_words[3][4]="祝你好运";

    NPC_words[4][0]="ass we can";
    NPC_words[4][1]="guaiguai zhanhao";
    NPC_words[4][2]="deep dark fantasy";
    NPC_words[4][3]="boy next door";
    NPC_words[4][4]="take it boy";

    NPC_words[5][0]="";
    NPC_words[5][1]="";
    NPC_words[5][2]="";
    NPC_words[5][3]="";
    NPC_words[5][4]="";
}
void Dialogue::initialStoreWin(int n)
{

    Times=0;//次数
    initialwords();
    npcchoose=n;
    StoreWin=new QWidget(this);
    QFont font("Consolas" ,12, 30);
    this->setFont(font);
    StoreWin->setStyleSheet("color:white;background-color:black");
    QLabel *Store_pic=new QLabel(StoreWin);
    text1=new QLabel(StoreWin);
    text2=new QLabel(StoreWin);
    op1=new QLabel(StoreWin);
    exitOption=new QLabel(StoreWin);
    OptionBox=new QGraphicsView(StoreWin);//最后构造的控件会在最上面
    OptionBox->setStyleSheet("border:3px solid #FFFFFF;");

    Store_pic->setStyleSheet("border-image: url(:/info/image/information/Store.png);");
    Store_pic->setGeometry(10,10,30,30);
    text1->setGeometry(32,10,150,32);
    text2->setGeometry(32,50,780,32);
    op1->setGeometry(32,112,192,32);
    exitOption->setGeometry(32,160,192,32);

    text1->setAlignment(Qt::AlignCenter);
    text2->setAlignment(Qt::AlignCenter);
    op1->setAlignment(Qt::AlignCenter);
    exitOption->setAlignment(Qt::AlignCenter);

    text1->setText(NPC_name[npcchoose]);
    text2->setText(NPC_words[npcchoose][Times]);
    op1->setText("next");
    exitOption->setText("Leave");

    OptionBox->setGeometry(32,112,192,32);

    OptionBoxTimer = new QTimer;
    border_color_it=0;
    OptionNum = 2;//选项数
    chooseOption = 0;//选择的选项
    Times=0;//购买次数
    haveBuyTimer=new QTimer(this);
    StoreWinisShow=false;
    setChooseEnable=true;

    connect(OptionBoxTimer, SIGNAL(timeout()), this, SLOT(OptionBoxborderChanged()));
    OptionBoxTimer->start(100);
}
void Dialogue::OptionBoxborderChanged()
{
    if (border_color_it <= 4)//设置为从0-5，会崩溃，因为当border_color_it=5时，border_color_it++就越界了
        border_color_it++;
    else
        border_color_it = 0;
    //实现选项框边缘颜色的变化（闪烁效果）

    //样式表 setStyleSheet 的组合用法  QString重载了 '+' 号运算符
    OptionBox->setStyleSheet(QString("border:3px solid #") +
                             QString(OptionBoxColor[border_color_it]) + QString(";background-color:transparent;"));
    //OptionBox的背景也为黑色，会遮挡住下面的控件，所以要设置背景为透明
}

void Dialogue::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    { //向上
        if (chooseOption > 0)
        {
            chooseOption -= 1;
            OptionBox->setGeometry(32, 112 + 48 * chooseOption, 192, 32);
        }
        else
            chooseOption = 0;
    }
    else if (event->key() == Qt::Key_S)
    { //向下
        if (chooseOption <= OptionNum - 2)
        {
            chooseOption += 1;
            OptionBox->setGeometry(32, 112 + 48 * chooseOption, 192, 32);
        }
        else
            chooseOption = OptionNum - 1;
    }
    else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Space)
    {
        if (chooseOption != OptionNum - 1)//不是选择的离开商店选项
        {
            haveBuyTimer->start(100);
            Times++;

            if(Times>=5)
            {
                this->hide();
                StoreWinisShow=false;
                parentWidget()->setFocus();
                chooseOption=0;//选项框回到起始位置
                OptionBox->setGeometry(32,112,192,32);
                return;
            }
            text2->setText(NPC_words[npcchoose][Times]);
            return;
        }
        else
        {
            this->hide();
            StoreWinisShow=false;
            parentWidget()->setFocus();
            chooseOption=0;//选项框回到起始位置
            OptionBox->setGeometry(32,112,192,32);
            return;
        }
    }
}
void Dialogue::showEvent(QShowEvent *)
{
    this->setFocus();//设置焦点在当前窗口
}
