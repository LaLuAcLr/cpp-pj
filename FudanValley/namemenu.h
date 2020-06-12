#ifndef NAMEMENU_H
#define NAMEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QPainter>
#include <QMessageBox>
#include <QApplication>
class Namemenu : public QWidget
{
    Q_OBJECT
public:
    explicit Namemenu(QWidget *parent = nullptr);

public:
    QPushButton *SetDone;
    QLineEdit *NameEdit;
private:
    void paintEvent(QPaintEvent *);
private:
    QLabel *nameLabel;

    QPainter *painter;

};

#endif // NAMEMENU_H
