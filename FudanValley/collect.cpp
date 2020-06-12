#include "collect.h"

void mining::initialmineral()
{

    get_mineral[0]="You have got nothing";
    get_mineral[1]="You have got a iron mine";
    get_mineral[2]="You have got a sliver mine";
    get_mineral[3]="You have got a gold mine";
    get_mineral[4]="You have got a diamond mine";
}

void mining::initialminemoney()
{
    minemoney[0]=0;
    minemoney[1]=50;
    minemoney[2]=100;
    minemoney[3]=200;
    minemoney[4]=400;
}
mining::mining()
{
    mineral=0;
    initialmineral();
    initialminemoney();
}

void mining::do_mining(int n)
{
    int level0 = 60 + 40 * n;
    int level1 = 30 + 25 * n;
    int level2 = 10 + 15 * n;
    int level3 = 1 + 9 * n;
    int random = rand()% 100;
    if(random > level0)
        mineral = 0;
    else if(random > level1)
        mineral = 1;
    else if(random > level2)
        mineral = 2;
    else if(random > level3)
        mineral = 3;
    else
        mineral = 4;
}

void fishing::initialfish()
{

    get_fish[0]="You have got a conch";
    get_fish[1]="You have got a crab";
    get_fish[2]="You have got a Starfish";
    get_fish[3]="You have got a tunas";
    get_fish[4]="You have got a lobster";
}

void fishing::initialfishmoney()
{
    fishmoney[0]=0;
    fishmoney[1]=50;
    fishmoney[2]=100;
    fishmoney[3]=200;
    fishmoney[4]=400;
}
fishing::fishing()
{
    fish=0;
    initialfish();
    initialfishmoney();
}

void fishing::do_fishing(int n)
{
    int level0 = 60 + 40 * n;
    int level1 = 30 + 25 * n;
    int level2 = 10 + 15 * n;
    int level3 = 1 + 9 * n;
    int random = rand()% 100;
    if(random > level0)
        fish = 0;
    else if(random > level1)
        fish = 1;
    else if(random > level2)
        fish = 2;
    else if(random > level3)
        fish = 3;
    else
        fish = 4;
}
