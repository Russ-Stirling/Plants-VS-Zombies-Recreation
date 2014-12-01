#include "zombie.h"
#include "plant.h"
#include <QDebug>
zombie::zombie()
{
}
zombie::zombie(QString filename)
{
    QPixmap zombieimage("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/"+filename+".png");
    setPixmap(zombieimage.scaled(100,100));

    name=filename;
    if (filename=="Zombie1")
    {
        life=10;
        attack=1;
        rate=0.5;
        setVelocity(1);
        defaultVelocity=1;
    }
    else if (filename=="Zombie2")
    {
        life=10;
        attack=1;
        rate=0.5;
        setVelocity(0.75);
        defaultVelocity=0.75;

    }
    else if (filename=="Zombie3")
    {
        life=28;
        attack=1;
        rate=0.5;
        setVelocity(1);
        defaultVelocity=1;


    }
    else if (filename=="Zombie4")
    {
        life=65;
        attack=1;
        rate=0.5;
        setVelocity(1);
        defaultVelocity=1;

    }
    else if (filename=="Zombie5")
    {
        life=16;
        attack=1;
        rate=0.5;
        setVelocity(1);
        defaultVelocity=1;

    }
}

void zombie::advance(int phase)
{

    if (name=="Zombie5")
    {
        if (life<=8)
        {
            defaultVelocity=2;
            setVelocity(2);
        }
    }

    setPos(x()-velocity,y());


}
