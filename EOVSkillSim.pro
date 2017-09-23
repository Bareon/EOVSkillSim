#-------------------------------------------------
#
# Project created by QtCreator 2017-07-23T20:41:16
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
win32: RC_ICONS = EOVicon.ico
TARGET = EOVSkillSimulator
TEMPLATE = app
VERSION = 0.1
#DEFINES += VERSION_STRING=\\\"0.1\\\"
#DEFINES += APPLICATION_NAME=\\\"Etrian Odyssey V Skill Simulator\\\"
QMAKE_TARGET_PRODUCT ="Etrian Odyssey V Skill Simulator"
QMAKE_TARGET_COPYRIGHT ="Brent Scheppmann"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mainlayout.cpp \

HEADERS += \
        mainwindow.h \
    mainlayout.h \
    mainlayout.h


