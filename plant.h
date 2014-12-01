#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsPixmapItem>
#include <QString>

class plant : public QGraphicsPixmapItem
{
public:
    plant();
    void setData(QString plantName);
    void damageTaken(int damage);

    QString getName(){return name;}

    double getCost(){return cost;}
    double getLife(){return life;}
    double getRange(){return range;}
    double getDamage(){return damage;}
    double getRate(){return rate;}
    double getSeeding(){return seeding;}

    bool getSplash(){return splash;}
    bool getSlow(){return slow;}
    bool getBomb(){return bomb;}
    bool getSun(){return sun;}
    bool getNeed(){return need;}

protected:
    QString name;
    double cost, life, range, damage, rate, seeding;
    bool splash, slow, bomb, sun, need;
};

#endif // PLANT_H
