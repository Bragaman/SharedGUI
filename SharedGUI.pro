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

HEADERS += \
    widget.h \
    basedto.h \
    testtable.h

SOURCES += main.cpp \
        widget.cpp \
    basedto.cpp \
    testtable.cpp

include (table_container_view.pri)

FORMS += \
    widget.ui
