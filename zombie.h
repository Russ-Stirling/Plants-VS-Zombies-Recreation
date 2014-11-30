#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsPixmapItem>

class zombie : public QGraphicsPixmapItem
{
public:
    zombie();
    zombie(QString filename);
    void advance(int phase);
private:
    int velocity =1;
};

#endif // ZOMBIE_H
