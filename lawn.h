#ifndef LAWN_H
#define LAWN_H

#include <QGraphicsView>
#include <QMouseEvent>

class lawn : public QGraphicsView
{
    Q_OBJECT
public:
    explicit lawn(QWidget *parent = 0);

signals:

public slots:
    void mousePressEvent(QMouseEvent *e);

};

#endif // LAWN_H
