#-------------------------------------------------
#
# Project created by QtCreator 2017-05-19T17:15:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaintPanel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mylabel.cpp \
    shapedialog.cpp

HEADERS  += mainwindow.h \
    mylabel.h \
    shapedialog.h

FORMS    += mainwindow.ui

RESOURCES += \
    src.qrc \
    shape.qrc
