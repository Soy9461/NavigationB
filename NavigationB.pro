#-------------------------------------------------
#
# Project created by QtCreator 2015-05-16T20:37:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NavigationB
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Navigation/Auxiliaries/Auxiliary.cpp \
    Navigation/DataStructures/BaseStructure.cpp \
    Navigation/DataStructures/NavigationMap.cpp \
    Navigation/DataStructures/NavigationPath.cpp \

HEADERS  += mainwindow.h \
    Navigation/Auxiliaries/Auxiliary.h \
    Navigation/DataStructures/BaseStructure.h \
    Navigation/DataStructures/NavigationMap.h \
    Navigation/DataStructures/NavigationPath.h \
    Navigation/DataStructures/Stdafx.h \
    Navigation/DataStructures/Vector3.h

FORMS    += mainwindow.ui
