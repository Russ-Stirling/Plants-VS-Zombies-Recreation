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


        //“level:sequence:rows:start:interval:decrement
         level_file->close();
        }
    readLevelCSV();

    save_file = new QFile("pvz_players.csv");
    readPlayerCSV();
        for (int i=0; i<userInfo.size(); i++)
        {
            ui->nameComboBox->addItem(userName[i]+", "+userLevel[i]);
        }
    int max = 0;
    for (int i=0; i<userInfo.size(); i++)
    {
        if (userTimestamp[i].toInt()>max)
            max=i;
    }
    ui->nameComboBox->setCurrentIndex(max);
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));

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
                 qDebug() << level_file;
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
                 qDebug() << save_file;
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

    QPen my_pen = QPen(Qt::black);
    QBrush my_brush1 = QBrush(Qt::darkGreen);
    QBrush my_brush2 = QBrush(Qt::green);
    QBrush my_brush3 = QBrush(Qt::darkYellow);

    if (level==0)
    {
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
    timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    timer->start(10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    QString levelinfo = ui->nameComboBox->currentText();
    level = levelinfo.split(" ")[1].toInt();
    qDebug() << level;
    loadLevel();
}

void MainWindow::on_newButton_clicked()
{
    scene->clear();
    level=1;
    ui->levelLabel->setText(QString::number(level));
    currentUserName = ui->nameLineEdit->text();
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
    ui->peaShooterButton->setEnabled(true);
    ui->sunFlowerButton->setEnabled(true);
    ui->snowPeaButton->setEnabled(true);
    ui->cherryBombButton->setEnabled(true);
    ui->chomperButton->setEnabled(true);
    ui->potatoeMineButton->setEnabled(true);
    ui->repeaterButton->setEnabled(true);
    ui->wallNutButton->setEnabled(true);


}

void MainWindow::on_peaShooterButton_clicked()
{
    buttonsEnabled();
    ui->peaShooterButton->setDisabled(true);
    //QPixmap test("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/Peashooter.png");


    ui->graphicsView->setPlant("Peashooter");
}

void MainWindow::on_sunFlowerButton_clicked()
{
    buttonsEnabled();
    ui->sunFlowerButton->setDisabled(true);
    //QPixmap test("C:/Qt/Qt5.3.1/Tools/QtCreator/bin/plantsVSzombies/reasources/Sunflower.png");


    ui->graphicsView->setPlant("Sunflower");

}


void MainWindow::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<e->globalPos();
}
