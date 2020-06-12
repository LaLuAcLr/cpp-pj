#include "character.h"
#include <QDebug>

character::character(QWidget *parent)
    : QLabel(parent)
{
    setFixedSize(56, 40);
    setAlignment(Qt::AlignCenter);
    isWalking = false;
    init_hash();
    init_vec();
    current_dir = 1;
    setPixmap(QPixmap::fromImage(pic_hash[4]));
}

void character::init_hash() {
    for (int k = 0; k < 16; ++k) {
        int i = k/4,j = k%4;
        QImage image(num2pic(i,j));
        image = image.scaled(56, 40, Qt::KeepAspectRatio);
        pic_hash.insert(k,image);
    }
}

void character::init_vec() {
    walk_pos = {0,0,0,0};
}
QString character::num2pic (int i,int j) {
    QString s;
    QTextStream out(&s);
    out << ":/man/";
    switch(i){
        case(0): out << "back"; break;
        case(1): out << "front"; break;
        case(2): out << "right"; break;
        case(3): out << "left"; break;
        default: qDebug() << "error not support input"; break;
    }
    out << "_";
    switch(j){
        case(0): out << "1"; break;
        case(1): out << "2"; break;
        case(2): out << "3"; break;
        case(3): out << "4"; break;
        default: qDebug() << "error not support input"; break;
    }
    out << ".png";
    return s;
}

void character::turn_direction(int i) {
    current_dir = i;
    setPixmap(QPixmap::fromImage(pic_hash[walk_pos[current_dir]%4+4*current_dir]));
}

void character::total_move (int i) {
    move_timer = new QTimer();
    isWalking = true;
    current_dir = i;
    QObject::connect(move_timer, SIGNAL(timeout()),this, SLOT(move_update()) );
    move_timer->start(40);
}

void character::move_update () {
    walk_pos[current_dir] += 1;
    setPixmap(QPixmap::fromImage(pic_hash[walk_pos[current_dir]%4+4*current_dir]));
    int x, y;
    switch(current_dir) {
    case 0: // up
        y = this->y() - 10;
        if(y >= 0) {
            move(this->x(), y);
        }
        break;
    case 1: // down
        y = this->y() + 10;
        if(y <= parentWidget()->height() - 40)
        {
            move(this->x(), y);
        }
        break;
    case 2: // right
        x = this->x() + 14;
        if(x <= parentWidget()->width() - 56)
        {
            move(x, this->y());
        }
        break;
    case 3: // left
        x = this->x() - 14;
        if(x >= 0) {
            move(x, this->y());
        }
        break;
    default: break;
}
    if (!(walk_pos[current_dir]%4)) {
        move_timer -> stop();   // mod4=0停止
        isWalking = false;
    }
}
