#include "lawn.h"
#include <QDebug>
#include <mainwindow.h>
#include<plant.h>
#include "QObject"
#include "QList"

lawn::lawn(QWidget *parent) :
    QGraphicsView(parent)
{
}

void lawn::mousePressEvent(QMouseEvent *e)
{
    qDebug() << e->localPos();
    if (!plantName.isEmpty())
    {
        QPixmap test("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/"+plantName+".png");

        p=new plant;
        p->setPixmap(test.scaled(100,100));
        plants.insert(plants.end(),p);

        int x = e->x();
        int y = e->y();

        x = x - x%100;
        y = y - y%100;
        p->setPos(x,y);
        bool empty=true;

        if (!plants.empty())
        {
        for (int i=0; i<plants.size()-1; i++)
            if(plants[i]->pos()==p->pos())
            {
                empty=false;
            }
        }
        qDebug() << empty;
        plantPixTest = scene()->itemAt(e->localPos(),QGraphicsView::transform());

        if (empty&&e->x()>100)
        {
            scene()->addItem(p);
            plantName.clear();

        }


        p=NULL;
    }

}
