#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFile>
#include <QDateTime>
#include <QTimer>
#include "plant.h"
#include <vector>
#include "QPixmap"
#include <QImage>
#include "QFile"
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum {WIDTH=1000};
    enum {HEIGHT=500};
    void loadLevel();
    void readPlayerCSV();
    void readLevelCSV();
    void startLevel();
    QString getName(){return plantName;}
    void buttonsEnabled();
    void setPlant(QString plant){plantName=plant;}
    void addPlant(int x, int y);


public slots:
    void mousePressEvent(QMouseEvent *e);



private slots:
    void on_startButton_clicked();

    void on_newButton_clicked();

    void on_deleteButton_clicked();

    void on_peaShooterButton_clicked();

    void on_sunFlowerButton_clicked();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *plantTimer;
    QFile *save_file, *level_file;
    int level=0, timestamp=0, points=0;
    QString currentUserName;
    QStringList userInfo, userTimestamp, userName, userLevel;
    QStringList levelSequence, levelRows, levelStart, levelInterval, levelDecrement;

    QString plantName;
    QGraphicsPixmapItem *plantPix;
    QGraphicsItem *plantPixTest;
    std::vector<QGraphicsPixmapItem *> plants;
    plant *p;




};

#endif // MAINWINDOW_H
