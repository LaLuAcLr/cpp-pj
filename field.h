#ifndef FIELD_H
#define FIELD_H

#include "hero.h"

class Field {
    
public:
    enum State
    {
        Orig,
        Hoed,
        Seeded,
        Poted,
        Harvest
    };
    Field() : _state{ Orig } {}
    Field(State s) : _state{ s } {}

    State get_state() const { return _state; }
    void set_state(State s) { _state = s; }

private:
    State _state;
};
#endif