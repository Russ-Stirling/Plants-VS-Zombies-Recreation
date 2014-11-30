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
}

void zombie::advance(int phase)
{


    setPos(x()-velocity,y());
    if (velocity==0)
    {
        qDebug()<<velocity;
    }

}
