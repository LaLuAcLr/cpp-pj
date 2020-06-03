#include "storewidget.h"

StoreWidget::StoreWidget(QWidget *parent) : QWidget(parent)
{
        initialStoreWin();
}
void StoreWidget::initialStoreWin()
{
    StoreWin=new QWidget(this);
    QFont font("Consolas", 12, 30);
    this->setFont(font);
    StoreWin->setStyleSheet("color:white;background-color:black");
    text1=new QLabel(StoreWin);
    text2=new QLabel(StoreWin);
    OptionBox=new QGraphicsView(StoreWin);
    OptionBox->setStyleSheet("border:3px solid #FFFFFF;background-color:transparent;");
    text1->setGeometry(init_x,10,length,width);
    text2->setGeometry(init_x,50,length,width);

    for (int i=0; i<MaxOption; ++i)
    {
        op[i] = new QLabel(StoreWin);
        op[i]->hide();
    }
    exitOption = new QLabel(StoreWin);
    exitOption->hide();

    text1->setAlignment(Qt::AlignCenter);
    text2->setAlignment(Qt::AlignCenter);

    text1->setText("store");
    text2->setText("I can help you");


    OptionBox->setGeometry(init_x, init_y, length, width);

    chooseOption = 0;//选择的选项
    haveBuyTimer=new QTimer(this);
    setChooseEnable=true;
}

void StoreWidget::set_store(const QStringList& item, const QVector<int>& price)
{
    if (item.size() != price.size()) qDebug()<<"wrong item num";
    QFont font("Consolas", 12, 30);
    for (int i=0; i<MaxOption; ++i)
    {
        op[i]->hide();
    }
    exitOption->hide();
    for (int i=0; i<item.size(); ++i)
    {
        op[i] = new QLabel(StoreWin);
        op[i]->setAlignment(Qt::AlignCenter);
        op[i]->setFont(font);
        op[i]->setText(item[i] + " $" + QString::number(price[i]));
        op[i]->setGeometry(init_x, init_y+i*interval, length, width);
        op[i]->show();
    }
    exitOption->setAlignment(Qt::AlignCenter);
    exitOption->setText("Leave");
    exitOption->setGeometry(init_x, init_y+item.size()*interval, length, width);
    exitOption->show();
    OptionBox->raise();
    OptionNum = item.size()+1;
}

void StoreWidget::keyPressEvent(QKeyEvent *event)
{   
    if(event->key() == Qt::Key_W)
    { //向上
        if (chooseOption > 0)
        {
            chooseOption -= 1;
            OptionBox->setGeometry(init_x, init_y + interval * chooseOption, length, width);
        }
        else
            chooseOption = 0;
    }
    else if (event->key() == Qt::Key_S)
    { //向下
        if (chooseOption <= OptionNum - 2)
        {
            chooseOption += 1;
            OptionBox->setGeometry(init_x, init_y + interval * chooseOption, length, width);
        }
        else
            chooseOption = OptionNum - 1;
    }
    else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Space)
    {
        if (chooseOption != OptionNum - 1)//不是选择的离开商店选项
        {
            if(!setChooseEnable)//金币不够，则不能购买
                return;
            haveBuyTimer->start(100);
        }
        else
        {
            this->hide();
            parentWidget()->setFocus();
            chooseOption=0;//选项框回到起始位置
            OptionBox->setGeometry(init_x,init_y,length,width);
            return;
        }
    }
}
void StoreWidget::showEvent(QShowEvent *)
{
    this->setFocus();//设置焦点在当前窗口
}
