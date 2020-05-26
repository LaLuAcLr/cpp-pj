#include "map.h"

void Map::initialtool(struct Tools& tool)
{
    tool.name = "hands";
    tool.function = 0;
    tool.level = 0;
}
void Map::initialitem(struct Items& item)
{
    item.money = 100;
    item.gold = 0;
    item.sliver = 0;
    item.iron = 0;
    item.stone = 0;
    item.seed = 10;
    item.fruit = 0;
    item.manure = 0;
}
void Map::initialrole()
{
    role.name = "LaLuAcLr";
    role.money = 2000;
    role.stamina = 100;
    initialtool(role.tool);
    initialitem(role.item);
}
void Map::initialregion()
{
    region[0].name = "undetermined";
    region[0].num = 0;
    region[0].status = 0;
}
void Map::initialnpc()
{
    npc[0].name = "npc.no1";//npc1
    npc[0].num = 0;
    npc[0].status = 0;

    npc[0].name = "npc.no2";//npc2
    npc[0].num = 1;
    npc[0].status = 0;

    npc[0].name = "npc.no3";//npc3
    npc[0].num = 2;
    npc[0].status = 0;

    npc[0].name = "npc.no4";//npc4
    npc[0].num = 3;
    npc[0].status = 0;

    npc[0].name = "npc.no5";//npc5
    npc[0].num = 4;
    npc[0].status = 0;
}
void Map::initialportal()
{
    p[0].num = 0;//传送门组编号
    p[0].if_jump = 1;
    p[0].floor0 = 0;
    p[0].x0 = 6;
    p[0].y0 = 0;
    p[0].floor1 = 2;
    p[0].x1 = 0;
    p[0].y1 = 4;

    p[1].num = 1;//传送门组编号
    p[1].if_jump = 1;
    p[1].floor0 = 0;
    p[1].x0 = 12;
    p[1].y0 = 3;
    p[1].floor1 = 1;
    p[1].x1 = 8;
    p[1].y1 = 14;
}

void Map::initialTerrainString()//动态贴图（地图物件）
{
    TerrainString[0]="border-image:url(:/now/greenmushroom.png);";
    TerrainString[1]="border-image:url(:/now/orangemushroom.png);";
    TerrainString[2]="border-image:url(:/now/badmushroom.png);";
    TerrainString[3]="border-image:url(:/now/box.png);";
    TerrainString[4]="border-image:url(:/now/redmushroom.png);";
}
void Map::initialCharacterString()
{
    CharacterString[0]="border-image:url(:/man/front_1.png);";
    CharacterString[1]="border-image:url(:/image/DungeonNew/Mario/down00.png);";
    CharacterString[2]="border-image:url(:/image/DungeonNew/Mario/left00.png);";
    CharacterString[3]="border-image:url(:/image/DungeonNew/Mario/left01.png);";
    CharacterString[4]="border-image:url(:/image/DungeonNew/Mario/right00.png);";
    CharacterString[5]="border-image:url(:/image/DungeonNew/Mario/right01.png);";
}
/*
void Map::initialNPCpic()//动态贴图（npc）
{

}
*/
string Map::dialogue(struct NPC& c)
{
    string s[5][4] = {
        "hello","how are you","good luck","bye",
        "welcome","see you","","",
        "what's up","that's good","","",
        "amazing!","......","","",
        "are you crazy?","go ahead!","good luck",""
    };
    return s[c.num][c.status];
}

Map::Map()
{
    Total_Floor = 7;
    //开辟堆上三维数组
    map = new int** [Total_Floor];
    for (int i = 0; i < Total_Floor; i++)
    {
        map[i] = new int* [17];
        for (int j = 0; j < 17; j++)
        {
            map[i][j] = new int[15];
            for (int k = 0; k < 15; k++)
            {
                map[i][j][k] = 0;
            }
        }
    }
    initialMap();
    initialportal();
    initialTerrainString();
    initialCharacterString();
    //initialMapString();
    initialrole();
    initialnpc();
    initialregion();
}
void Map::initialMap()
{
    floor = 0;
    x = 3;
    y = 0;
    int num = 0;
    while (1)
    {

        if (num == 1)
        {
            int tempmap[17][15] = {
                14,14,14,14,14,14,14,14,14,14,14,1,1,1,1,
                14,14,14,14,14,14,14,14,14,14,14,1,1,1,1,
                14,14,14,14,14,14,14,14,14,14,14,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,14,14,14,
                1,1,1,1,1,1,10,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                50,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,11,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,40,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,51,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,51,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,51,1,1,1,1,1,1,1,1,1,1,1

            };
            for (int i = 0; i < 17; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    map[num - 1][i][j] = tempmap[i][j];
                }
            }
        }
        if (num == 2)
        {
            int tempmap[17][15] = {
                1,1,1,1,11,11,11,11,11,11,11,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,14,14,14,14,1,1,1,1,
                1,1,1,1,1,1,1,14,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,14,1,1,1,1,1,1,1,
                1,1,1,1,14,14,14,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,51,
                1,1,1,1,1,1,1,1,1,12,12,12,12,12,12,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
            };
            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 17; j++)
                {
                    map[num - 1][i][j] = tempmap[i][j];
                }
            }
        }
        /*if (num == 3)
        {
            int tempmap[13][15] = {
                1,1,1,1,50,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,11,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,11,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,11,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,11,10,10,10,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                12,12,12,12,12,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,12,12,12,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,14,14,1,1,1,1,1,1,1,1,1,1,
                1,1,1,14,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,14,1,1,1,1,1,1,1,1,1,1,1
            };

            for (int i = 0; i < 13; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    map[num - 1][i][j] = tempmap[i][j];
                }
            }
        }
        if (num == 4)
        {
            int tempmap[13][15] = {
                14,14,14,14,14,14,14,14,1,1,1,1,1,1,1,
                14,14,14,14,14,14,14,14,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,10,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                50,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,11,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,51,1,1,1,1,1,1,1,1,1,1,1
            };
            for (int i = 0; i < 13; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    map[num - 1][i][j] = tempmap[i][j];
                }
            }
        }
        if (num == 5)
        {
            int tempmap[13][15] = {
                14,14,14,14,14,14,14,14,1,1,1,1,1,1,1,
                14,14,14,14,14,14,14,14,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,10,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                50,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,11,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,51,1,1,1,1,1,1,1,1,1,1,1
            };
            for (int i = 0; i < 13; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    map[num - 1][i][j] = tempmap[i][j];
                }
            }
        }
        if (num == 6)
        {
            int tempmap[13][15] = {
                14,14,14,14,14,14,14,14,1,1,1,1,1,1,1,
                14,14,14,14,14,14,14,14,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,10,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                50,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,11,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,51,1,1,1,1,1,1,1,1,1,1,1
            };
            for (int i = 0; i < 13; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    map[num - 1][i][j] = tempmap[i][j];
                }
            }
        }
        if (num == 7)
        {
            int tempmap[13][15] = {
                14,14,14,14,14,14,14,14,1,1,1,1,1,1,1,
                14,14,14,14,14,14,14,14,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,10,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                50,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,11,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,51,1,1,1,1,1,1,1,1,1,1,1
            };
            for (int i = 0; i < 13; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    map[num - 1][i][j] = tempmap[i][j];
                }
            }
        }*/
        num++;
        if (num > Total_Floor)
        {
            break;
        }
    }
}
void Map::initialCharacterPos(struct portal& p)//经过传送门后地址重置
{
    if (p.if_jump)
    {
        if (floor == p.floor0)
        {
            floor = p.floor1;
            x = p.x1;
            y = p.y1;
        }
        else if (floor == p.floor1)
        {
            floor = p.floor0;
            x = p.x0;
            y = p.y0;
        }
        p.if_jump = true;
    }
}
