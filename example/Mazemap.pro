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
    Field.cpp \
    StartMenu.cpp \
    Window.cpp \
    character.cpp \
    collect.cpp \
    dialogue.cpp \
        mainwindow.cpp \
    map.cpp \
    maze.cpp \
    interface.cpp \
    Dungeon.cpp \
    namemenu.cpp \
    storewidget.cpp

HEADERS  += mainwindow.h \
    Farm.h \
    Field.h \
    StartMenu.h \
    Window.h \
    character.h \
    collect.h \
    dialogue.h \
    map.h \
    maze.h \
    interface.h \
    Dungeon.h \
    namemenu.h \
    storewidget.h

FORMS    +=

QT += multimedia
CONFIG += resources_big
RC_ICONS = icon.ico

RESOURCES += \
    now.qrc
