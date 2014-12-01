#include "bullet.h"

bullet::bullet()
{
    QPixmap pea("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/bullet1.png");
    setPixmap(pea.scaled(50,50));

}
bullet::bullet(bool isSlow)
{
    setSlow(isSlow);
    QPixmap pea("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/bullet2.png");
    setPixmap(pea.scaled(50,50));
}

void bullet::advance(int phase)
{


        setPos(this->x()+velocity, this->y());


}
