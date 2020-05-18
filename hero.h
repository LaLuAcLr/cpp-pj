#ifndef HERO_H
#define HERO_H

#include "field.h"

class Hero {
    enum Tool
    {
        None,
        Hoe,
        Knife,
        Pot,
        Seed
    };

public:
    Hero() : _stamina{100}, _money{200}, _tool{None} {}
    Hero(int s, int m, Tool t=None) : _stamina{s}, _money{m}, _tool{t} {}

    int get_stamina() const { return _stamina; }
    int get_money() const { return _money; }
    Tool get_tool() const { return _tool; }

    int &set_stamina(int s) { _stamina = s; }
    int &set_money(int m) { _money = m; }
    Tool &set_tool(Tool t) { _tool = t; }

private:
    int _stamina;
    int _money;
    Tool _tool;
}

#endif
