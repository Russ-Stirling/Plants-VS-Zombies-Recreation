#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QPointF>
#include <QDebug>
#include "QString"
#include "QStringList"
#include "QFile"
#include "QImage"
#include "QGraphicsItem"
#include "QGraphicsPixmapItem"
#include "plant.h"
#include <QMessageBox>
#include <QSpacerItem>
#include <QGridLayout>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    level_file = new QFile("pvz_levels.csv");

    if (level_file->open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate))
        {

         QTextStream out(level_file);

         out<< "1" << ":" << "1,1,1,1,2" << ":" << "1" << ":" << "20" << ":" << "1" << ":" << "0.2" << "\n";
         out<< "2" << ":" << "1,1,1,2,3,1,3,1,3,3" << ":" << "3" << ":" << "15" << ":" << "2" << ":" << "0.2" << "\n";
         out<< "3" << ":" << "1,1,1,2,3,1,3,1,1,1,4,5" << ":" << "5" << ":" << "15" << ":" << "2" << ":" << "0.2" << "\n";



        //“level:sequence:rows:start:interval:decrement
         level_file->close();
        }

    readLevelCSV();
    if (levelSequence[0].isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Error, no level data");
        msgBox.exec();
        this->close();
    }

    save_file = new QFile("pvz_players.csv");

    readPlayerCSV();
        for (int i=0; i<userInfo.size(); i++)
        {
            ui->nameComboBox->addItem(userName[i]+", "+userLevel[i]);
        }
    ui->levelLabel->setText(QString::number(level));

    int max = 0;
    for (int i=0; i<userInfo.size(); i++)
    {
        if (userTimestamp[i].toInt()>max)
            max=i;
    }
    ui->nameComboBox->setCurrentIndex(max);

    QIcon peashooter("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/Peashooter.png");
    QIcon cherryBomb("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/CherryBomb.png");
    QIcon potatoMine("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/PotatoMine.png");
    QIcon sunFlower("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/Sunflower.png");
    QIcon snowPea("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/SnowPea.png");
    QIcon wallNut("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/Wallnut.png");
    QIcon repeater("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/Repeater.png");
    QIcon chomper("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/Chomper.png");

    ui->peaShooterButton->setText("Peashooter\nCost:100");
    ui->peaShooterButton->setIcon(peashooter);

    ui->cherryBombButton->setIcon(cherryBomb);
    ui->cherryBombButton->setText("Cherry Bomb\nCost:150");

    ui->potatoeMineButton->setIcon(potatoMine);
    ui->potatoeMineButton->setText("Potatoe Mine\nCost:25");

    ui->sunFlowerButton->setIcon(sunFlower);
    ui->sunFlowerButton->setText("Sunflower\nCost:50");


    ui->snowPeaButton->setIcon(snowPea);
    ui->snowPeaButton->setText("Snow Pea\nCost:175");

    ui->wallNutButton->setIcon(wallNut);
    ui->wallNutButton->setText("Wallnut\nCost:50");

    ui->repeaterButton->setIcon(repeater);
    ui->repeaterButton->setText("Repeater\nCost:200");

    ui->chomperButton->setIcon(chomper);
    ui->chomperButton->setText("Chomper\nCost:150");

    buttonsDisabled();

    scene = new QGraphicsScene(this);   // scene holds all objects in the scene
    ui->graphicsView->setScene(scene);  // graphicsView is the viewport on to the scene
    QRectF rect(0,0,WIDTH,HEIGHT);
    scene->setSceneRect(rect);          // Set scene boundaries

    loadLevel();


}

void MainWindow::readLevelCSV()
{
    levelSequence.clear();
    levelRows.clear();
    levelStart.clear();
    levelInterval.clear();
    levelDecrement.clear();
    if (level_file->open(QIODevice::ReadOnly))
    {
                 QTextStream text(level_file);


                 //qDebug() << level_file;
                 QStringList infoList;

                 while (!text.atEnd())
                {
                     QString line = text.readLine();
                     //qDebug() << line;
                     infoList = line.split(":");
                     levelSequence << infoList[1];
                     levelRows << infoList[2];
                     levelStart << infoList[3];
                     levelInterval << infoList[4];
                     levelDecrement << infoList[5];
                }
            //for (int i =0; i<userInfo.size(); i++)
                //qDebug() << userInfo[i];
             level_file->close();
      }
}

void MainWindow::readPlayerCSV()
{
    userInfo.clear();
    userTimestamp.clear();
    userName.clear();
    userLevel.clear();
    if (save_file->open(QIODevice::ReadOnly))
    {
                 QTextStream text(save_file);
                // qDebug() << save_file;
                 QStringList infoList;

                 while (!text.atEnd())
                {
                     QString line = text.readLine();
                     //qDebug() << line;
                     userInfo << line;

                     infoList = line.split(":");

                     userTimestamp << infoList[0];
                     userName << infoList[1];
                     userLevel << infoList[2];
                }
            //for (int i =0; i<userInfo.size(); i++)
                //qDebug() << userInfo[i];
             save_file->close();

      }
}

void MainWindow::loadLevel()
{
    scene->clear();
    plants.clear();
    suns.clear();
    zombies.clear();
    bullets.clear();
    lawnmowers.clear();
    qDebug()<<zombies.size();

    QPen my_pen = QPen(Qt::black);
    QBrush my_brush1 = QBrush(Qt::darkGreen);
    QBrush my_brush2 = QBrush(Qt::green);
    QBrush my_brush3 = QBrush(Qt::darkYellow);

    if (level==0)
    {
        buttonsDisabled();

        ui->quitButton->setDisabled(true);
        ui->restartButton->setDisabled(true);
        ui->newButton->setEnabled(true);
        ui->startButton->setEnabled(true);
        ui->deleteButton->setEnabled(true);
        ui->nameLineEdit->setEnabled(true);
        ui->nameComboBox->setEnabled(true);
        if(ui->nameComboBox->currentText().isEmpty())
        {
            ui->deleteButton->setEnabled(false);
            ui->startButton->setEnabled(false);
        }

        for(int i=0; i<HEIGHT; i=i+100)
        {
            for (int j=0; j<WIDTH; j=j+100)
            {
                scene->addRect(QRect(j,i,100,100),my_pen, my_brush3);
            }
        }
    }

    else if (level==1)
    {
        for(int i=0; i<HEIGHT; i=i+100)
        {
            scene->addRect(QRect(0,i,100,100),my_pen, my_brush3);
        }

        for (int i=100; i<WIDTH; i=i+100)
        {
            scene->addRect(QRect(i,0,100,100),my_pen, my_brush3);
            scene->addRect(QRect(i,100,100,100),my_pen, my_brush3);
            scene->addRect(QRect(i,300,100,100),my_pen, my_brush3);
            scene->addRect(QRect(i,400,100,100),my_pen, my_brush3);
        }

        for (int i=100; i<WIDTH; i=i+200)
        {
            scene->addRect(QRect(i,200,100,100),my_pen, my_brush1);
            scene->addRect(QRect(i+100,200,100,100),my_pen, my_brush2);
        }
    }

    else if (level==2)
    {
        for(int i=0; i<HEIGHT; i=i+100)
        {
            scene->addRect(QRect(0,i,100,100),my_pen, my_brush3);
        }
        for (int i=100; i<WIDTH; i=i+100)
        {
            scene->addRect(QRect(i,0,100,100),my_pen, my_brush3);
            scene->addRect(QRect(i,400,100,100),my_pen, my_brush3);
        }

        for (int i=100; i<WIDTH; i=i+200)
        {
            scene->addRect(QRect(i,100,100,100),my_pen, my_brush2);
            scene->addRect(QRect(i,300,100,100),my_pen, my_brush2);
            scene->addRect(QRect(i+100,100,100,100),my_pen, my_brush1);
            scene->addRect(QRect(i+100,300,100,100),my_pen, my_brush1);
            scene->addRect(QRect(i,200,100,100),my_pen, my_brush1);
            scene->addRect(QRect(i+100,200,100,100),my_pen, my_brush2);
        }
    }

    else if (level>2)
    {

        for(int i=0; i<HEIGHT; i=i+100)
        {
            scene->addRect(QRect(0,i,100,100),my_pen, my_brush3);
        }

        for(int i=0; i<HEIGHT; i=i+200)
       {
            for (int j=100; j<WIDTH; j=j+200)
            {

                scene->addRect(QRect(j,i,100,100),my_pen, my_brush1);

                scene->addRect(QRect(j+100,i,100,100),my_pen, my_brush2);

         }
     }
        for(int i=100; i<HEIGHT; i=i+200)
        {
            for (int j=100; j<WIDTH; j=j+200)
            {

             scene->addRect(QRect(j,i,100,100),my_pen, my_brush2);

               scene->addRect(QRect(j+100,i,100,100),my_pen, my_brush1);

            }
         }
    }

    if (level>0)
    {
        startLevel();
    }
}

void MainWindow::startLevel()
{
    buttonsEnabled();
    zombieIndex=0;
    chosenLevelSequence.clear();
    QString sequence=levelSequence[level-1];
    //qDebug()<<sequence;
    chosenLevelSequence= sequence.split(",");
    //qDebug()<<levelSequence;
    //for (int i=0; i<chosenLevelSequence.size(); i++)
      //  qDebug()<<chosenLevelSequence[i];
    ui->levelLabel->setText(QString::number(level));

    ui->pointsLabel->setText(QString::number(points));
    ui->startButton->setDisabled(true);
    ui->newButton->setDisabled(true);
    ui->deleteButton->setDisabled(true);
    ui->restartButton->setEnabled(true);
    ui->quitButton->setEnabled(true);
    ui->nameLineEdit->setDisabled(true);
    ui->nameComboBox->setDisabled(true);


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    connect(timer, SIGNAL(timeout()), this, SLOT(collision()));

    timer->start(40);

    test1=new QTimer(this);
    connect(test1, SIGNAL(timeout()), this, SLOT(buttonsEnabled()));
    test1->start(10);



    plantTimer= new QTimer(this);
    connect(plantTimer, SIGNAL(timeout()), this, SLOT(plantsFire()));
    plantTimer->start(1500);

    sunTimer = new QTimer(this);
    connect(sunTimer, SIGNAL(timeout()), this, SLOT(addSun()));
    sunTimer->start(10000);

    zombieTimer = new QTimer(this);
    connect(zombieTimer, SIGNAL(timeout()), this, SLOT(addZombie()));
    zombieTimer->start(5000);

    seeding= new QTimer(this);

    attacking = new QTimer(this);
    connect(attacking, SIGNAL(timeout()), this, SLOT(attack()));
    attacking->start(500);

    sunflower = new QTimer(this);
    connect(sunflower, SIGNAL(timeout()), this, SLOT(addSunFromSunflower()));

    if (levelRows[level-1]=="1")
    {
        l=new lawnMower;
        l->setPos(0,200);
        lawnmowers.insert(lawnmowers.end(), l);
        scene->addItem(l);
        l=NULL;
    }
    else if (levelRows[level-1]=="3")
    {
        for (int i=1; i<4; i++)
        {
            l=new lawnMower;
            l->setPos(0,i*100);
            lawnmowers.insert(lawnmowers.end(), l);
            scene->addItem(l);
            l=NULL;
        }
    }

    else
    {
        for (int i=0; i<5; i++)
        {
            l=new lawnMower;
            l->setPos(0,i*100);
            lawnmowers.insert(lawnmowers.end(), l);
            scene->addItem(l);
            l=NULL;
        }
    }


}

MainWindow::~MainWindow()
{
    delete ui;
    if (timer!=NULL)
    {
        delete timer;
    }
    if (plantTimer!=NULL)
    {
        delete plantTimer;
    }
    if (test1!=NULL)
    {
        delete test1;
    }
    if (seeding!=NULL)
    {
        delete seeding;
    }
    if (attacking!=NULL)
    {
        delete attacking;
    }
    if (zombieTimer!=NULL)
    {
        delete zombieTimer;
    }
    if (sunTimer!=NULL)
    {
        delete sunTimer;
    }
    if (sunflower!=NULL)
    {
        delete sunflower;
    }
    delete scene;
    userInfo.clear(); userTimestamp.clear(); userName.clear(); userLevel.clear();
    levelSequence.clear(); levelRows.clear(); levelStart.clear(); levelInterval.clear(); levelDecrement.clear();
    chosenLevelSequence.clear();
    suns.clear(); lawnmowers.clear();zombies.clear(); bullets.clear(); plants.clear();
    if (p!=NULL)
        delete p;
    if (z!=NULL)
        delete z;
    if (b!=NULL)
        delete b;
    if (s!=NULL)
        delete s;
    if (l!=NULL)
        delete l;
    if (plantPix!=NULL)
        delete plantPix;
    if (plantPixTest!=NULL)
        delete plantPixTest;
    if (save_file!=NULL)
        delete save_file;
    if (level_file!=NULL)
        delete level_file;


}

void MainWindow::on_startButton_clicked()
{
    QString levelinfo = ui->nameComboBox->currentText();
    currentUserName = levelinfo.split(",")[0];
    level = levelinfo.split(" ")[1].toInt();
    qDebug() << level;
    loadLevel();
}

void MainWindow::on_newButton_clicked()
{   QMessageBox msgBox;
    msgBox.setText("Create new profile?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int selection = msgBox.exec();
    switch (selection)
    {
    case QMessageBox::Ok:
    {
        currentUserName = ui->nameLineEdit->text();
        if(currentUserName.size()<=10)
        {
        level=1;
        ui->levelLabel->setText(QString::number(level));
        readPlayerCSV();
        timestamp= QDateTime::currentDateTime().toTime_t();
        //qDebug() << userName;

        if (save_file->open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate))
        {

         QTextStream out(save_file);
         for (int i=0; i<userInfo.size(); i++ )
         {
           out<<userInfo[i]<<"\n";
         }
         out<< timestamp << ":" << currentUserName << ":" << level << "\n";


         save_file->close();
        }
        ui->nameComboBox->addItem(currentUserName+", "+QString::number(level));
        loadLevel();
        break;
        }
        QMessageBox mssg;
        mssg.setText("invalid user name");
        mssg.exec();
        break;
    }
    case QMessageBox::Cancel:
    {
        break;
    }
    default:
    {
        break;
    }
    }
}

void MainWindow::on_deleteButton_clicked()
{
    int index =ui->nameComboBox->currentIndex();
    qDebug() << index;
    readPlayerCSV();
    if (save_file->open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate))
        {

         QTextStream out(save_file);
         for (int i=0; i<index; i++ )
         {
           out<<userInfo[i]<<"\n";
         }
         for (int i=index+1; i<userInfo.size(); i++ )
         {
           out<<userInfo[i]<<"\n";
         }


         save_file->close();
        }

    readPlayerCSV();
    ui->nameComboBox->clear();
        for (int i=0; i<userInfo.size(); i++)
        {
            ui->nameComboBox->addItem(userName[i]+", "+userLevel[i]);
        }
}

void MainWindow::buttonsEnabled()
{
    if (points>=200)
    {
        ui->peaShooterButton->setEnabled(true);
        ui->sunFlowerButton->setEnabled(true);
        ui->snowPeaButton->setEnabled(true);
        ui->cherryBombButton->setEnabled(true);
        ui->chomperButton->setEnabled(true);
        ui->potatoeMineButton->setEnabled(true);
        ui->repeaterButton->setEnabled(true);
        ui->wallNutButton->setEnabled(true);
    }
    else if (points>=175)
    {
        ui->snowPeaButton->setEnabled(true);
        ui->peaShooterButton->setEnabled(true);
        ui->sunFlowerButton->setEnabled(true);
        ui->cherryBombButton->setEnabled(true);
        ui->chomperButton->setEnabled(true);
        ui->potatoeMineButton->setEnabled(true);
        ui->wallNutButton->setEnabled(true);
        ui->repeaterButton->setEnabled(false);

    }

    else if (points>=150)
    {
        ui->chomperButton->setEnabled(true);
        ui->peaShooterButton->setEnabled(true);
        ui->sunFlowerButton->setEnabled(true);
        ui->cherryBombButton->setEnabled(true);
        ui->potatoeMineButton->setEnabled(true);
        ui->wallNutButton->setEnabled(true);
        ui->repeaterButton->setEnabled(false);
        ui->snowPeaButton->setEnabled(false);


    }

    else if (points>=100)
    {
        ui->peaShooterButton->setEnabled(true);
        ui->sunFlowerButton->setEnabled(true);
        ui->potatoeMineButton->setEnabled(true);
        ui->wallNutButton->setEnabled(true);
        ui->repeaterButton->setEnabled(false);
        ui->snowPeaButton->setEnabled(false);
        ui->chomperButton->setEnabled(false);
        ui->cherryBombButton->setEnabled(false);


    }

    else if (points>=50)
    {
        ui->sunFlowerButton->setEnabled(true);
        ui->potatoeMineButton->setEnabled(true);
        ui->wallNutButton->setEnabled(true);
        ui->repeaterButton->setEnabled(false);
        ui->snowPeaButton->setEnabled(false);
        ui->chomperButton->setEnabled(false);
        ui->cherryBombButton->setEnabled(false);
        ui->peaShooterButton->setEnabled(false);

    }
    else if (points>=25)
    {
        ui->potatoeMineButton->setEnabled(true);
        ui->repeaterButton->setEnabled(false);
        ui->snowPeaButton->setEnabled(false);
        ui->chomperButton->setEnabled(false);
        ui->cherryBombButton->setEnabled(false);
        ui->peaShooterButton->setEnabled(false);
        ui->sunFlowerButton->setEnabled(false);
        ui->wallNutButton->setEnabled(false);


    }




}

void MainWindow::buttonsDisabled()
{
    ui->peaShooterButton->setEnabled(false);
    ui->sunFlowerButton->setEnabled(false);
    ui->snowPeaButton->setEnabled(false);
    ui->cherryBombButton->setEnabled(false);
    ui->chomperButton->setEnabled(false);
    ui->potatoeMineButton->setEnabled(false);
    ui->repeaterButton->setEnabled(false);
    ui->wallNutButton->setEnabled(false);
}

void MainWindow::on_peaShooterButton_clicked()
{
        test1->stop();
        buttonsEnabled();
        ui->peaShooterButton->setDisabled(true);


        setPlant("Peashooter");

}

void MainWindow::on_sunFlowerButton_clicked()
{

        test1->stop();

        buttonsEnabled();
        ui->sunFlowerButton->setDisabled(true);
        setPlant("Sunflower");


}

void MainWindow::mousePressEvent(QMouseEvent *e)
{

    //qDebug()<<test;
    //qDebug()<<e->x()-170;
    //qDebug()<<e->y()-150;
   // addZombie(400);
    int x = e->x()-170;
    int y = e->y()-190;

    if (!plantName.isEmpty())
    {
        addPlant(x,y);
    }

    for (int i=0; i<suns.size(); i++)
    {
        if (x>=suns[i]->x()&&x<=(suns[i]->x()+50))
        {
            if (y>=suns[i]->y()&&y<=(suns[i]->y()+50))
            {
                points= points+suns[i]->getPoints();
                ui->pointsLabel->setText(QString::number(points));
                buttonsEnabled();
                scene->removeItem(suns[i]);
                suns.erase(suns.begin()+i);
            }
        }

    }
}

void MainWindow::addPlant(int x, int y)
{
    QPixmap test("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/"+plantName+".png");

    x = x - x%100;
    y = y - y%100;
    bool empty=true;

    if (!plants.empty())
    {
    for (int i=0; i<plants.size(); i++)
        if(plants[i]->x()==x&&plants[i]->y()==y)
        {
            empty=false;
        }
    }

    qDebug()<<levelRows[level-1];
    qDebug()<<levelRows[level-1].toInt()*100;
    if (levelRows[level-1]=="1")
    {
        if(y!= 200)
        {
            empty=false;
        }
    }
    if (levelRows[level-1]=="3")
    {
        if(!(y >= 100&&y<=300))
        {

            empty=false;
        }
    }



    //qDebug()<<empty;
    //qDebug()<<x;
    if (empty&&x>=100)
    {
        test1->start();
        p=new plant;
        p->setData(plantName);
        p->setPixmap(test.scaled(100,100));
        p->setPos(x,y);

        plants.insert(plants.end(),p);
        scene->addItem(p);
        points= points - p->getCost();
        ui->pointsLabel->setText(QString::number(points));

        if (p->getName()=="Sunflower")
        {
            sunflower->start(5000);
        }

        plantName.clear();


    }


    p=NULL;
}

void MainWindow::addSun()
{
    s = new sun;
    suns.insert(suns.end(),s);
    s->setPos(random(1,9)*100,0);
    if (levelRows[level-1]=="1")
    {
        s->setStop(250);
    }
    else if (levelRows[level-1]=="3")
    {
        s->setStop(random(1,3)*100+50);
    }
    else
    {
        s->setStop(random(0,4)*100+50);
    }
    scene->addItem(s);
    s=NULL;
}

void MainWindow::addSunFromSunflower()
{
    for (int i=0; i<plants.size(); i++)
    {

        if(plants[i]->getName()=="Sunflower")
        {
            s = new sun;
            suns.insert(suns.end(),s);
            s->setPos(plants[i]->x(),plants[i]->y()+50);
            s->setStop(plants[i]->y()+50);
            scene->addItem(s);
            s=NULL;
        }
    }
}

void MainWindow::addZombie()
{
    if(zombieIndex<chosenLevelSequence.size())
    {
        z = new zombie("Zombie"+chosenLevelSequence[zombieIndex]);
        zombies.insert(zombies.end(),z);
        if (levelRows[level-1]=="1")
        {
            z->setPos(999,200);
        }
        if (levelRows[level-1]=="3")
        {
            qDebug()<<level;

            z->setPos(999,random(1,3)*100);
            qDebug()<<z->y();
        }

        if (levelRows[level-1]=="5")
        {
            z->setPos(999,random(0,4)*100);
        }

        scene->addItem(z);
        z=NULL;
        zombieIndex++;
    }


    else if((!(zombieIndex<chosenLevelSequence.size()))&&zombies.size()==0)
    {
        nextLevel();
    }
}

int MainWindow::random(double x1, double x2)
{
    int returned;
    x2=x2+1;
    returned = x1 + ((qrand()/(double(RAND_MAX)))*(x2-x1));
    int value = static_cast<int>(returned);
    return value;
}

void MainWindow::on_cherryBombButton_clicked()
{
    test1->stop();

        buttonsEnabled();
        ui->cherryBombButton->setDisabled(true);
        setPlant("CherryBomb");

}

void MainWindow::on_wallNutButton_clicked()
{
    test1->stop();

    buttonsEnabled();
    ui->wallNutButton->setDisabled(true);
    setPlant("Wallnut");
}

void MainWindow::on_potatoeMineButton_clicked()
{
    test1->stop();

    buttonsEnabled();
    ui->potatoeMineButton->setDisabled(true);
    setPlant("PotatoMine");
}

void MainWindow::on_snowPeaButton_clicked()
{
    test1->stop();

    buttonsEnabled();
    ui->snowPeaButton->setDisabled(true);
    setPlant("SnowPea");
}

void MainWindow::on_chomperButton_clicked()
{
    test1->stop();

    buttonsEnabled();
    ui->chomperButton->setDisabled(true);
    setPlant("Chomper");
}

void MainWindow::on_repeaterButton_clicked()
{
    test1->stop();

    buttonsEnabled();
    ui->repeaterButton->setDisabled(true);
    setPlant("Repeater");
}

void MainWindow::collision()
{
    for (int i=0; i<zombies.size(); i++)
    {


        for (int j=0; j<plants.size(); j++)
        {




            if(zombies[i]->x()>=plants[j]->x()+90&&zombies[i]->x()<=plants[j]->x()+100)
            {
                if(zombies[i]->y()==plants[j]->y())
                {
                    zombies[i]->setVelocity(0);
                    coll=false;
                }

            }
            if (coll)
            {
                zombies[i]->setVelocity(zombies[i]->getDefaultVelocity());
            }

        }
        if (zombies[i]->x()<=0)
        {
            levelLost();
            break;
        }
        coll=true;

        for (int j=0; j<bullets.size(); j++)
        {
            if(bullets[j]->x()>=1000)
            {
                b=bullets[j];

                scene->removeItem(bullets[j]);
                bullets.erase(bullets.begin()+j);
                delete b;
                b=NULL;
                j--;
                break;
            }
            if (zombies[i]->x()>=bullets[j]->x()+40&&zombies[i]->x()<=bullets[j]->x()+70)
            {
                if(zombies[i]->y()==bullets[j]->y())
                {
                    zombies[i]->damageTaken(bullets[j]->getDamage());
                    if (bullets[j]->getSlow())
                    {
                        zombies[i]->setDefaultVelocity(zombies[i]->getDefaultVelocity()-1);
                    }
                    b=bullets[j];
                    scene->removeItem(bullets[j]);
                    bullets.erase(bullets.begin()+j);
                    delete b;
                    b=NULL;
                    j--;
                    break;
                }
            }

            if (zombies[i]->getLife()<=0)
            {
                z=zombies[i];
                scene->removeItem(zombies[i]);
                zombies[i]->setPos(1000,500);
                zombies.erase(zombies.begin()+i);
                delete z;
                z=NULL;
                //i--;
                break;
            }
        }
        for (int j=0; j<lawnmowers.size(); j++)
        {


            if (zombies[i]->x()>=lawnmowers[j]->x()+40&&zombies[i]->x()<=lawnmowers[j]->x()+70)
            {
                if(zombies[i]->y()==lawnmowers[j]->y())
                {
                    lawnmowers[j]->setVelocity();
                    z=zombies[i];
                    scene->removeItem(zombies[i]);
                    zombies.erase(zombies.begin()+i);
                    delete z;
                    z=NULL;
                    break;
                }
        }

    }
    }

    for (int j=0; j<lawnmowers.size(); j++)
        {
            if (lawnmowers[j]->x()>=1000)
            {
                l=lawnmowers[j];

                scene->removeItem(lawnmowers[j]);
                lawnmowers.erase(lawnmowers.begin()+j);
                delete l;
                l=NULL;
                j--;
                break;
            }
        }


}

void MainWindow::attack()
{
    for (int i=0; i<zombies.size(); i++)
    {
        for (int j=0; j<plants.size(); j++)
        {
            if(zombies[i]->x()>=plants[j]->x()+90&&zombies[i]->x()<=plants[j]->x()+100)
            {
                if(zombies[i]->y()==plants[j]->y())
                {

                    plants[j]->damageTaken(zombies[i]->getAttack());
                    if (plants[j]->getLife()<=0)
                    {
                        p=plants[j];
                        scene->removeItem(plants[j]);
                        plants.erase(plants.begin()+j);
                        zombies[i]->setVelocity(zombies[i]->getDefaultVelocity());
                        delete p;
                        p=NULL;
                        j--;
                    }
                }
            }
        }
    }
    for (int j=0; j<plants.size(); j++)
    {
        for (int i=0; i<zombies.size(); i++)
        {
            if (plants[j]->getName()=="CherryBomb")
            {
                for (int k=0; k<zombies.size(); k++)
                {
                    if (zombies[k]->x()<=110+plants[j]->x()&&zombies[k]->x()>=plants[j]->x()-110)
                    {
                        if (zombies[k]->y()<=100+plants[j]->y()&&zombies[k]->y()>=plants[j]->y()-100)
                        {
                            z=zombies[k];
                            scene->removeItem(zombies[k]);
                            zombies.erase(zombies.begin()+k);
                            delete z;
                            z=NULL;
                            k--;
                        }

                    }
                }
                p=plants[j];
                scene->removeItem(plants[j]);
                plants.erase(plants.begin()+j);
                delete p;
                p=NULL;
                j--;
                break;
            }
            if(zombies[i]->x()>=plants[j]->x()+90&&zombies[i]->x()<=plants[j]->x()+100)
            {
                if(zombies[i]->y()==plants[j]->y())
                {
                    /* if (plants[j]->getName()=="CherryBomb")
                    {
                        for (int k=0; k<zombies.size(); k++)
                        {
                            if (zombies[k]->x()<=110+plants[j]->x()&&zombies[k]->x()>=plants[j]->x()-110)
                            {
                                if (zombies[k]->y()<=100+plants[j]->y()&&zombies[k]->y()>=plants[j]->y()-100)
                                {
                                    z=zombies[k];
                                    scene->removeItem(zombies[k]);
                                    zombies.erase(zombies.begin()+k);
                                    delete z;
                                    z=NULL;
                                    k--;
                                }

                            }
                        }
                        p=plants[j];
                        scene->removeItem(plants[j]);
                        plants.erase(plants.begin()+j);
                        delete p;
                        p=NULL;
                        j--;
                        break;
                    } */

                    if (plants[j]->getName()=="PotatoMine")
                    {
                        z=zombies[i];
                        scene->removeItem(zombies[i]);
                        zombies.erase(zombies.begin()+i);
                        delete z;
                        z=NULL;
                        i--;

                        p=plants[j];
                        scene->removeItem(plants[j]);
                        plants.erase(plants.begin()+j);
                        delete p;
                        p=NULL;
                        j--;
                        break;
                    }

                }
            }
    }
}
}

void MainWindow::levelLost()
{
    QMessageBox msgBox;
    points=150;
    msgBox.setText("zombies ate your brains");
    msgBox.exec();
    delete timer;
    delete sunTimer;
    delete zombieTimer;
    delete seeding;
    delete attacking;
    delete sunflower;
    delete plantTimer;
    loadLevel();

}

void MainWindow::nextLevel()
{
    level++;
    points=150;
    delete timer;
    delete sunTimer;
    delete zombieTimer;
    delete seeding;
    delete attacking;
    delete sunflower;
    delete plantTimer;
    readPlayerCSV();
    timestamp= QDateTime::currentDateTime().toTime_t();
    int index =ui->nameComboBox->currentIndex();


    if (save_file->open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate))
        {

         QTextStream out(save_file);
         for (int i=0; i<index; i++ )
         {
           out<<userInfo[i]<<"\n";
         }
         out<< timestamp << ":" << currentUserName << ":" << level << "\n";
         for (int i=index+1; i<userInfo.size(); i++ )
         {
           out<<userInfo[i]<<"\n";
         }


         save_file->close();
        }

    readPlayerCSV();
    ui->nameComboBox->clear();
        for (int i=0; i<userInfo.size(); i++)
        {
            ui->nameComboBox->addItem(userName[i]+", "+userLevel[i]);
        }

    if (level>3)
    {
        level=0;
        QMessageBox msgBox;
        msgBox.setText("You Won");
        msgBox.exec();
    }
    loadLevel();
}

void MainWindow::on_restartButton_clicked()
{
    timer->stop();
    sunTimer->stop();
    zombieTimer->stop();
    seeding->stop();
    attacking->stop();
    sunflower->stop();
    plantTimer->stop();

    QMessageBox msgBox;
    //QSpacerItem* horizontalSpacer = new QSpacerItem(444, 202, QSizePolicy::Fixed, QSizePolicy::Fixed);
    //dynamic_cast<QGridLayout*>(msgBox.layout()->addItem(horizontalSpacer, 0, 0, 0, 0));
    //(msgBox.layout()->addItem(horizontalSpacer));
    //tried to use spacers not working out though

    msgBox.setText("Are you sure you want to restart?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);




    int selection = msgBox.exec();
    qDebug()<<msgBox.width();

    qDebug()<<msgBox.height();

    switch (selection)
    {
    case QMessageBox::Ok:
    {

        delete timer;
        delete sunTimer;
        delete zombieTimer;
        delete seeding;
        delete attacking;
        delete sunflower;
        delete plantTimer;
        loadLevel();
        break;
    }
    case QMessageBox::Cancel:
    {

        timer->start();
        sunTimer->start();
        zombieTimer->start();
        seeding->start();
        attacking->start();
        sunflower->start();
        plantTimer->start();
        break;
    }
    default:
    {
        break;
    }

    }
}

void MainWindow::on_quitButton_clicked()
{
    timer->stop();
    sunTimer->stop();
    zombieTimer->stop();
    seeding->stop();
    attacking->stop();
    sunflower->stop();

    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to quit?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int selection = msgBox.exec();
    switch (selection)
    {
    case QMessageBox::Ok:
    {
        delete timer;
        delete sunTimer;
        delete zombieTimer;
        delete seeding;
        delete attacking;
        delete sunflower;
        level=0;
        buttonsDisabled();
        loadLevel();
        break;
    }
    case QMessageBox::Cancel:
    {
        timer->start();
        sunTimer->start();
        zombieTimer->start();
        seeding->start();
        attacking->start();
        sunflower->start();
        break;
    }
    default:
    {
        break;
    }

    }
}

void MainWindow::plantsFire()
{
    for (int i=0; i<plants.size(); i++)
    {
        for (int j=0; j<zombies.size(); j++)
        {
            if (plants[i]->y()==zombies[j]->y()&&plants[i]->x()<zombies[j]->x())
            {
                if(plants[i]->getName()=="Peashooter")
                {
                    addBullet(plants[i]->x(),plants[i]->y(),"1");
                    break;
                }
                else if (plants[i]->getName()=="SnowPea")
                {
                    addBullet(plants[i]->x(),plants[i]->y(),"2");
                    break;

                }
                else if (plants[i]->getName()=="Repeater")
                {
                    addBullet(plants[i]->x(),plants[i]->y(),"3");
                    break;
                }
            }
        }
    }
}

void MainWindow::addBullet(int x, int y, QString type)
{
    if (type=="1")
    {
        b=new bullet();
        b->setPos(x,y);
        bullets.insert(bullets.end(),b);
        scene->addItem(b);
        b=NULL;
    }
    else if (type=="2")
    {
        b=new bullet(true);
        b->setPos(x,y);
        bullets.insert(bullets.end(),b);
        scene->addItem(b);
        b=NULL;
    }

    else if(type=="3")
    {
        b=new bullet();
        b->setPos(x,y);
        bullets.insert(bullets.end(),b);
        scene->addItem(b);
        b=NULL;

        b=new bullet();
        b->setPos(x+100,y);
        bullets.insert(bullets.end(),b);
        scene->addItem(b);
        b=NULL;
    }




}

