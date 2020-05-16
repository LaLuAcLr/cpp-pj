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
    Hero() : _stamina{100}, _money{0}, _tool{None} {}
    Hero(int s, int m, Tool t=None) : _stamina{s}, _money{m}, _tool{t} {}

    int get_stamina() const { return _stamina; }
    int get_money() const { return _money; }
    Tool get_tool() const { return _tool; }

private:
    int _stamina;
    int _money;
    Tool _tool;
}

#endif
