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
#include "sun.h"
#include "zombie.h"

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
    void buttonsDisabled();
    void setPlant(QString plant){plantName=plant;}
    void addPlant(int x, int y);
    int random(double x1, double x2);
    void levelLost();


public slots:
    void mousePressEvent(QMouseEvent *e);

    void addSun();

    void addSunFromSunflower();

    void addZombie();

    void collision();

    void attack();




private slots:
    void on_startButton_clicked();

    void on_newButton_clicked();

    void on_deleteButton_clicked();

    void on_peaShooterButton_clicked();

    void on_sunFlowerButton_clicked();


    void on_cherryBombButton_clicked();

    void on_wallNutButton_clicked();

    void on_potatoeMineButton_clicked();

    void on_snowPeaButton_clicked();

    void on_chomperButton_clicked();

    void on_repeaterButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *timer, *plantTimer, *sunTimer, *zombieTimer, *seeding, *attacking, *sunflower;
    QFile *save_file, *level_file;
    int level=0, timestamp=0, points=1500;
    QString currentUserName;
    QStringList userInfo, userTimestamp, userName, userLevel;
    QStringList levelSequence, levelRows, levelStart, levelInterval, levelDecrement, chosenLevelSequence;

    QString plantName;
    QGraphicsPixmapItem *plantPix;
    QGraphicsItem *plantPixTest;
    std::vector<plant *> plants;
    plant *p;
    std::vector<sun *> suns;
    sun *s;
    std::vector<zombie *> zombies;
    zombie *z;
    int zombieIndex=0;
    bool coll=true;




};

#endif // MAINWINDOW_H
