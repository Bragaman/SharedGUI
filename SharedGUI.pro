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
    basedto.h


SOURCES += \
    basedto.cpp

include (table_container_view.pri)
include (examples/examples.pri)
