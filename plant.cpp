#include "plant.h"
#include "QPen"
#include "QColor"
#include "QBrush"
#include "QPainter"
#include <QDebug>

plant::plant()
{
}

void plant::setData(QString plantName)
{
    if (plantName=="CherryBomb")
    {
        name = plantName;

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

    else if (plantName=="Chomper")
    {
        name = plantName;
        cost=150;
        life=4;
        range=1;
        damage=150;
        rate=42;
        seeding=7.5;

        splash = false;
        slow=false;
        bomb=false;
        sun=false;
        need=false;

    }
    else if (plantName=="Peashooter")
    {
        name = plantName;
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
    else if (plantName=="PotatoMine")
    {
        name = plantName;
        cost=25;
        life=4;
        range=1;
        damage=90;
        rate=1.5;
        seeding=30;

        splash = false;
        slow=false;
        bomb=true;
        sun=false;
        need=false;

    }
    else if (plantName=="Repeater")
    {
        name = plantName;
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
    else if (plantName=="SnowPea")
    {
        name = plantName;
        cost=175;
        life=4;
        range=9999;
        damage=1;
        rate=1.5;
        seeding=7.5;

        splash = false;
        slow=true;
        bomb=false;
        sun=false;
        need=false;

    }
    else if (plantName=="Sunflower")
    {
        name = plantName;

        cost=50;
        life=4;
        range=0;
        damage=0;
        rate=24;
        seeding=7.5;

        splash = false;
        slow=false;
        bomb=false;
        sun=true;
        need=false;

    }
    else if (plantName=="Wallnut")
    {
        name = plantName;
        cost=50;
        life=72;
        range=0;
        damage=0;
        rate=0;
        seeding=30;

        splash = false;
        slow=false;
        bomb=false;
        sun=false;
        need=false;

    }

}

void plant::damageTaken(int damage)
{
    life=life-damage;
    if (name=="Wallnut")
    {
        this->setPixmap(this->pixmap().scaled(this->pixmap().height()-1, this->pixmap().width()-1));
    }
    else
    {
        this->setPixmap(this->pixmap().scaled(this->pixmap().height()-2, this->pixmap().width()-2));

    }

    this->update();
}
