#ifndef SUN_H
#define SUN_H

#include <QGraphicsPixmapItem>

class sun : public QGraphicsPixmapItem
{
public:
    sun();
    int getPoints(){return points;}
    void advance(int phase);
    void setVelocity(int v){velocity=v;}
    void setStop(int s){stop=s;}

private:
    int points=50;
    int velocity=1;
    int life = 750;
    int stop = 400;
};

#endif // SUN_H
