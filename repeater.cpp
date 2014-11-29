#include "repeater.h"

repeater::repeater()
{
    name = "Repeater";

    cost=200;
    life=4;
    range=9999;
    damage=2;
    rate=1.5;
    seeding=7.5;

    splash = false;
    slow=false;
    bomb=false;
    sun=false;
    need=false;
}
