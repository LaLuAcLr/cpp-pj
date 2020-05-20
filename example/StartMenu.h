#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include <QLabel>
#include <QPainter>
#include <QMessageBox>
#include <QApplication>

class StartMenu : public QWidget
{
    Q_OBJECT
public:
    explicit StartMenu(QWidget *parent = 0);
public:
    QTimer *timer;
    void ShowMainMenu();

private:
    QLabel *msgLabel;
    QPushButton *button_start;
    QPushButton *button_load;
    QPushButton *button_quit;
    QPushButton *button_about;
    QProgressBar *probar;
    QPainter *painter;
private:
    void paintEvent(QPaintEvent *);
public slots:
    void Quit();
    void ShowAbout();
    void NewGame();
};




#endif // STARTMENU_H
