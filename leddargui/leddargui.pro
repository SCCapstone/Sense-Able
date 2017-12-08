#-------------------------------------------------
#
# Project created by QtCreator 2017-11-10T21:06:40
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = leddargui
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
LIBS += -ggdb
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lstdc++ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_objdetect
INCLUDEPATH += ../Release/
LIBS += -L../Release/ -lLeddar -lLeddarC -lLeddarTech
DEPENDPATH += ../Release
LIBS += -Wl,-rpath=../Release/
#LIBS += -Wl,-rpath='${ORIGIN}/../'

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    leddarmain.cpp \
    usernotifier.cpp \
    capturethread.cpp \
    objdetect.cpp

HEADERS += \
    mainwindow.h \
    LeddarProperties.h \
    leddarmain.h \
    LeddarC.h \
    usernotifier.h \
    capturethread.h \
    objdetect.h

FORMS += \
    mainwindow.ui
