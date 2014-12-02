#include "lawnmower.h"

lawnMower::lawnMower()
{
    QPixmap lawnimage("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/Lawn_Mower.png");
    setPixmap(lawnimage.scaled(100,100));
}

void lawnMower::advance(int phase)
{
    setPos(x()+velocity,y());
}
