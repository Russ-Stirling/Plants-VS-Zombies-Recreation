#-------------------------------------------------
#
# Project created by QtCreator 2014-11-24T09:38:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = plantsVSzombies
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lawn.cpp \
    plant.cpp \
    sunflower.cpp \
    peashooter.cpp \
    cherrybomb.cpp \
    wallnut.cpp \
    potatoemine.cpp \
    snowpea.cpp \
    chomper.cpp \
    repeater.cpp

HEADERS  += mainwindow.h \
    lawn.h \
    plant.h \
    sunflower.h \
    peashooter.h \
    cherrybomb.h \
    wallnut.h \
    potatoemine.h \
    snowpea.h \
    chomper.h \
    repeater.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    reasources/CherryBomb.png \
    reasources/Chomper.png \
    reasources/Peashooter.png \
    reasources/PotatoMine.png \
    reasources/Repeater.png \
    reasources/SnowPea.png \
    reasources/Sunflower.png \
    reasources/Wallnut.png \
    reasources/Zombie.png
