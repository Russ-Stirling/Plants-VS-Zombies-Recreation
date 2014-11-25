#include "lawn.h"
#include <QDebug>

lawn::lawn(QWidget *parent) :
    QGraphicsView(parent)
{
}

void lawn::mousePressEvent(QMouseEvent *e)
{
    qDebug() << e->localPos();
}
