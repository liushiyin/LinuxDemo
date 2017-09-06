#-------------------------------------------------
#
# Project created by QtCreator 2017-05-13T16:02:28
#
#-------------------------------------------------

QT       += core gui
QT       +=multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NoteWord
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qabout.cpp \
    qruner.cpp

HEADERS  += mainwindow.h \
    qabout.h \
    qruner.h

FORMS    += mainwindow.ui \
    qabout.ui \
    qruner.ui

RESOURCES += \
    src.qrc

DISTFILES += \
    My.rc

RC_ICONS =icon.ico
