#-------------------------------------------------
#
# Project created by QtCreator 2017-10-28T15:43:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCVtest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += -L/usr/local/include
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mattoqimage.cpp \
    ../m3-TheIndexZero-master/leddarmain.cpp

HEADERS += \
        mainwindow.h \
    mattoqimage.h \
    ../m3-TheIndexZero-master/LeddarC.h \
    ../m3-TheIndexZero-master/leddarmain.h \
    ../m3-TheIndexZero-master/LeddarProperties.h

FORMS += \
        mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../Release/ -lLeddar -lLeddarC -lLeddarTech

INCLUDEPATH += $$PWD/../Release
DEPENDPATH += $$PWD/../Release

DISTFILES += \
    ../m3-TheIndexZero-master/Definitions.mif
