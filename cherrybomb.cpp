#include "cherrybomb.h"

cherryBomb::cherryBomb()
{
    name = "CherryBomb";

    cost=150;
    life=9999;
    range=1;
    damage=90;
    rate=1;
    seeding=50;

    splash = true;
    slow=false;
    bomb=true;
    sun=false;
    need=false;
}
