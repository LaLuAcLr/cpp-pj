#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

class myWidget : public QWidget
{
public:
    myWidget();
};


myWidget::myWidget()
{
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color: rgb(255,255, 255)");
    QWidget *leftWidget=new QWidget();
    leftWidget->setStyleSheet("background-color: rgb(255,100, 255)");
    QWidget *rightWidget=new QWidget();
    rightWidget->setStyleSheet("background-color: rgb(255,255, 100)");
    QHBoxLayout *PHBoxLayout=new QHBoxLayout(this);
    PHBoxLayout->addWidget(leftWidget);
    PHBoxLayout->addWidget(rightWidget);

    QWidget *lefttopWidget=new QWidget();
    lefttopWidget->setStyleSheet("background-color: rgb(100,255, 100)");
    QWidget *leftdownWidget=new QWidget();
    leftdownWidget->setStyleSheet("background-color: rgb(255,100, 100)");
    QVBoxLayout *PHVBoxLayout=new QVBoxLayout(leftWidget);
    PHVBoxLayout->addWidget(lefttopWidget);
    PHVBoxLayout->addWidget(leftdownWidget);

    QWidget *rightleftWidget=new QWidget();
    rightleftWidget->setStyleSheet("background-color: rgb(100,100, 100)");
    QWidget *rightrightWidget=new QWidget();
    rightrightWidget->setStyleSheet("background-color: rgb(155,100, 30)");
    QHBoxLayout *PHHBoxLayout=new QHBoxLayout(rightWidget);
    PHHBoxLayout->addWidget(rightleftWidget);
    PHHBoxLayout->addWidget(rightrightWidget);
}
