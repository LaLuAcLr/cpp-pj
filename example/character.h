#ifndef CHARACTER_H
#define CHARACTER_H
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QTimeLine>
#include <QHash>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QLabel>
class character : public QLabel
{
    Q_OBJECT

public:
    character(QWidget *parent = 0);
public slots:
    void move_update ();//单次move函数，声明为slot
public:
    void total_move (int);//整个四帧的移动函数
    void turn_direction(int);
public:
    bool isWalking;
    int current_dir;
private:
    QHash <int, QImage> pic_hash;//图片对应hash
    QVector <int> walk_pos;//人物姿态对应vector
    void init_hash ();//hash 初始化
    void init_vec ();//vec 初始化
    QString num2pic (int,int);//将数据转化为对应内容的string
    QTimer *move_timer;//定时器


};
#endif // CHARACTER_H
