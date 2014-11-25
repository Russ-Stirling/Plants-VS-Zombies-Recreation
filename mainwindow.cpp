#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QPointF>
#include <QDebug>
#include "QString"
#include "QStringList"
#include "QFile"
#include "QImage"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    save_file = new QFile("pvz_players.csv");
    readCSV();
        for (int i=0; i<userInfo.size(); i++)
        {
            ui->nameComboBox->addItem(userInfo[i]);
        }












    /* if (save_file->open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate))
    {

     QTextStream out(save_file);
     out<<"test";


     save_file->close();
    }

*/
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));

    loadLevel();


}

void MainWindow::readCSV()
{
    userInfo.clear();
    if (save_file->open(QIODevice::ReadOnly))
    {
                 QTextStream text(save_file);
                 qDebug() << save_file;

                 while (!text.atEnd())
                {
                     QString line = text.readLine();
                     //qDebug() << line;
                     userInfo << line;



                }


            //for (int i =0; i<userInfo.size(); i++)
                //qDebug() << userInfo[i];



             save_file->close();

      }
}

void MainWindow::loadLevel()
{
    scene = new QGraphicsScene(this);   // scene holds all objects in the scene
    ui->graphicsView->setScene(scene);  // graphicsView is the viewport on to the scene
    QRectF rect(0,0,WIDTH,HEIGHT);
    scene->setSceneRect(rect);          // Set scene boundaries

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


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{

}

void MainWindow::on_newButton_clicked()
{
    scene->clear();
    level=1;
    userName = ui->nameLineEdit->text();
    readCSV();
    //qDebug() << userName;
    if (save_file->open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate))
        {

         QTextStream out(save_file);
         for (int i=0; i<userInfo.size(); i++ )
         {
            out<<userInfo[i]<<"\n";
         }
         out<< 72 << ":" << userName << ":" << level << "\n";


         save_file->close();
        }

    ui->nameComboBox->addItem(userName, QString(level));

    loadLevel();
}
