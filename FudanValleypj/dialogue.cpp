#include "dialogue.h"
#pragma execution_character_set("utf-8")

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
    NPC_words[1][2]="左侧通往亲王的城堡，你可以去里面寻找公主";
    NPC_words[1][3]="下面通往采矿场，你可以消耗体力进行采矿";
    NPC_words[1][4]="右边通往渔场，你可以消耗体力进行捕鱼";

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

    NPC_words[4][0]="你又来找我了吗？";
    NPC_words[4][1]="父亲说，你太穷了";
    NPC_words[4][2]="我们不适合在一起";
    NPC_words[4][3]="。。。。。。";
    NPC_words[4][4]="如果能用宝石向我的家人证明，也许会有转机吧";

    NPC_words[5][0]="你还没有放弃吗？";
    NPC_words[5][1]="这点礼物改变不了我父亲的固执";
    NPC_words[5][2]="父亲说，能娶我的人至少要有金色的汤匙";
    NPC_words[5][3]="可是就凭一个种地的穷小子怎么可能呢。。";
    NPC_words[5][4]="我好苦恼。。";

    NPC_words[6][0]="我很高兴你能为我这么努力";
    NPC_words[6][1]="但是有些东西也许是天生就注定的";
    NPC_words[6][2]="我就要和远东之国的皇子联姻了";
    NPC_words[6][3]="除非能用宝玉收买远东之国的使者";
    NPC_words[6][4]="但是我一个闺中女子怎么才能买到宝玉呢";

    NPC_words[7][0]="谢谢你又来看我";
    NPC_words[7][1]="我已经告诉父亲我真正喜欢的人是你了";
    NPC_words[7][2]="但父亲的要求是你要有精灵宝珠的戒指";
    NPC_words[7][3]="相信如果是你的话，一定可以做到吧";
    NPC_words[7][4]="我在这里等你来接我";
}
void Dialogue::initialStoreWin(int n)
{

    Times=0;//次数
    initialwords();
    npcchoose = n;
    StoreWin=new QWidget(this);
    QFont font("Consolas" ,12, 30);
    this->setFont(font);
    StoreWin->setStyleSheet("color:white;background-color:black");

    text1=new QLabel(StoreWin);
    text2=new QLabel(StoreWin);
    op1=new QLabel(StoreWin);
    exitOption=new QLabel(StoreWin);
    OptionBox=new QGraphicsView(StoreWin);//最后构造的控件会在最上面

    //OptionBox->setStyleSheet("border:3px solid #FFFFFF;");
    OptionBox->setStyleSheet("border:3px solid #FFFFFF;background-color:transparent;");

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
void Dialogue::paintEvent(QPaintEvent *)
{
    painter = new QPainter(this);
    QImage pixmap(":/now/bl.png");
    painter->drawImage(QRectF(0, 0, 840, 680), pixmap);
    painter->end();
}
