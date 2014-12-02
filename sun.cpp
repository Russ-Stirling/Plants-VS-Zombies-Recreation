#include "sun.h"

sun::sun()
{
    QPixmap sunimage("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/sun.png");
    setPixmap(sunimage.scaled(50,50));
}

void sun::advance(int phase)
{
    if (y()>=stop)
    {
        velocity=0;
        life--;
        life--;
        life--;
        life--;
        if (life<=0)
        {
            setPos(1000,500);
        }
    }

    setPos(x(),y()+velocity);


}
