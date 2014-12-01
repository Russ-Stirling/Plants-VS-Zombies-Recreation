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
    void damageTaken(int d){life = life-d;}
    int getAttack(){return attack;}
    int getDefaultVelocity(){return defaultVelocity;}
    int getLife(){return life;}
private:
    QString name;
    double life, attack, rate, velocity, defaultVelocity;
};

#endif // ZOMBIE_H
