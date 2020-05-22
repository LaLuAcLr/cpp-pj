#-------------------------------------------------
#
# Project created by QtCreator 2019-07-07T14:36:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mazemap
TEMPLATE = app


SOURCES += main.cpp\
    Farm.cpp \
    StartMenu.cpp \
    Window.cpp \
    exp.cpp \
        mainwindow.cpp \
    maze.cpp \
    interface.cpp \
    Dungeon.cpp \
    storewidget.cpp

HEADERS  += mainwindow.h \
    Farm.h \
    StartMenu.h \
    Window.h \
    maze.h \
    interface.h \
    Dungeon.h \
    storewidget.h

FORMS    +=

QT += multimedia
CONFIG += resources_big
RC_ICONS = Maze&Dungeon.ico

RESOURCES += \
    resources.qrc
