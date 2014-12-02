#ifndef LAWNMOWER_H
#define LAWNMOWER_H

#include <QGraphicsPixmapItem>

class lawnMower : public QGraphicsPixmapItem
{
private:
    int velocity=0;
public:
    lawnMower();
    void advance(int phase);
    void setVelocity(){velocity=8;}
};

#endif // LAWNMOWER_H
