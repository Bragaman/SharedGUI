#-------------------------------------------------
#
# Project created by QtCreator 2016-09-21T19:42:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SharedGUI
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        widget.cpp \
    basedto.cpp \
    tablecontainerview.cpp \
    testtable.cpp

HEADERS  += widget.h \
    basedto.h \
    tablecontainerview.h \
    testtable.h

FORMS    += widget.ui
