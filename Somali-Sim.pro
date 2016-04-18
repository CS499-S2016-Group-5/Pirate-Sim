#-------------------------------------------------
#
# Project created by QtCreator 2016-02-21T10:29:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Somali-Sim
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        simwindow.cpp \
    simsettingsdialog.cpp \
    Ship.cpp \
    Ships.cpp \
    Simulation.cpp

HEADERS  += simwindow.h \
    simsettingsdialog.h \
    Ship.hpp \
    Ships.hpp \
    RandomEvent.hpp \
    Simulation.hpp \
    Ship_Type_Enum.hpp \
    Counts.hpp

FORMS    += simwindow.ui \
    simsettingsdialog.ui

RESOURCES += \
    images.qrc
