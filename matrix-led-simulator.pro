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
            ledmatrix.cpp

HEADERS  += simulatorwindow.h \
            ledmatrix.h

FORMS    += simulatorwindow.ui
