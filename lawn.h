#ifndef LAWN_H
#define LAWN_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "plant.h"

class lawn : public QGraphicsView
{
    Q_OBJECT
private:

public:
    explicit lawn(QWidget *parent = 0);

signals:

public slots:

};

#endif // LAWN_H
