#ifndef LAWN_H
#define LAWN_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "plant.h"

class lawn : public QGraphicsView
{
    Q_OBJECT
private:
    QString plantName;
    QGraphicsPixmapItem *plantPix;
    QGraphicsItem *plantPixTest;
    std::vector<QGraphicsPixmapItem *> plants;
    plant *p;
public:
    explicit lawn(QWidget *parent = 0);

signals:

public slots:
    void setPlant(QString plant){plantName=plant;}
    void mousePressEvent(QMouseEvent *e);

};

#endif // LAWN_H
