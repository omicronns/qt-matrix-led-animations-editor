#-------------------------------------------------
#
# Project created by QtCreator 2014-08-12T22:21:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = matrix-led-simulator
TEMPLATE = app


SOURCES +=  main.cpp\
            simulatorwindow.cpp \
            ledmatrix.cpp \
    frame.cpp \
    simframe.cpp \
    frameviewer.cpp

HEADERS  += simulatorwindow.h \
            ledmatrix.h \
    frame.h \
    simframe.h \
    frameviewer.h

FORMS    += simulatorwindow.ui
