#ifndef MAP_H
#define MAP_H
#include <QString>
#include <QStringList>
#include <QMap>
using namespace std;

struct Tools
{
    QString name;
    int function;
    int level;
};
struct Items
{
    QMap<QString, int> seed;

};
struct charactor
{
    QString name;
    int money;
    int stamina;//疲劳度
    Tools tool;//手持工具
    QString seed;
    Items item;
};
struct NPC  //可交互角色
{
    int num;//编号
    QString name;
    int status;
};
struct portal//双向传送门组
{
    int num;//传送门组编号
    bool if_jump;//是否跳转
    int floor0;
    int x0;
    int y0;//传送门0位置
    int floor1;
    int x1;
    int y1;//传送门1位置
};
class Map  //地图
{
public:
    Map();
    void initialMap();
    void initialCharacterPos(struct portal& p);//经过传送门后位置跳转
    void initialseed(const QStringList&);
    string dialogue(struct NPC& c);
private:
    void initialrole();
    void initialtool(struct Tools& tool);
    void initialportal();
    void initialTerrainString();
    void initialMapFloor();
    void initialNPCpic();//初始化npc图片
    void initialnpc();
public:
    charactor role;
    NPC npc[10];
    portal p[10];
    QString TerrainString[20];
    QString MapFloor[10];
    QString CharacterString[10];
    QString NPC_pic[10][4];//npc贴图字符串
    int floor;
    int Total_Floor;
    int*** map;//三维数组
    int x;//角色位置
    int y;

};

#endif // MAP_H

