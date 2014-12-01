#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>

class bullet : public QGraphicsPixmapItem
{
public:
    bullet();
    bullet(bool isSlow);
    void setSlow(bool isIt){slow=isIt;}
    bool getSlow(){return slow;}
    void advance(int phase);
    int getDamage(){return damage;}
private:
    int damage = 1;
    bool slow = false;
    int velocity = 2;
};

#endif // BULLET_H
