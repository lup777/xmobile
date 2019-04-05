#-------------------------------------------------
#
# Project created by QtCreator 2019-03-27T07:41:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = render_test
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    shaderobject.cpp \
    shadercircle.cpp \
    renderer.cpp \
    zone.cpp \
    display.cpp

HEADERS  += mainwindow.h \
    shaderobject.h \
    shadercircle.h \
    renderer.h \
    zone.h \
    display.h \
    druid_types.h

FORMS    += mainwindow.ui
