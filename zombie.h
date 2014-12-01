#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsPixmapItem>

class zombie : public QGraphicsPixmapItem
{
public:
    zombie();
    zombie(QString filename);
    void advance(int phase);
    void setVelocity(double v){velocity=v;}
    int getAttack(){return attack;}
private:
    QString name;
    double life, attack, rate, velocity;
};

#endif // ZOMBIE_H
