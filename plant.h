#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsPixmapItem>
#include <QString>

class plant : public QGraphicsPixmapItem
{
public:
    plant();
protected:
    QString name;
    double cost, life, range, damage, rate, seeding;
    bool splash, slow, bomb, sun, need;
};

#endif // PLANT_H
