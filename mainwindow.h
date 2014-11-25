#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFile>

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
    void readCSV();

private slots:
    void on_startButton_clicked();

    void on_newButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QFile *save_file;
    int level=0;
    QString userName;
    QStringList userInfo;


};

#endif // MAINWINDOW_H
