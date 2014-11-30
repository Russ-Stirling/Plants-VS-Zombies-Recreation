#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsPixmapItem>

class zombie : public QGraphicsPixmapItem
{
public:
    zombie();
    zombie(QString filename);
    void advance(int phase);
    void setVelocity(int v){velocity=v;}
private:
    int velocity =1;
};

#endif // ZOMBIE_H
