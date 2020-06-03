#ifndef COLLECT_H
#define COLLECT_H
#include <QString>
#include <QStringList>
class mining
{
private:
    void initialmineral();
    void initialminemoney();
public:
    mining();
    int mineral;
    int minemoney[5];
    QString get_mineral[5];
    void do_mining(int n);
};

class fishing
{
private:
    void initialfish();
    void initialfishmoney();
public:
    fishing();
    int fish;
    int fishmoney[5];
    QString get_fish[5];
    void do_fishing(int n);
};

#endif // COLLECT_H
