#include "peashooter.h"

peaShooter::peaShooter()
{
    name = "Peashooter";

    cost=100;
    life=4;
    range=9999;
    damage=1;
    rate=1.5;
    seeding=7.5;

    splash = false;
    slow=false;
    bomb=false;
    sun=false;
    need=false;
}
