#-------------------------------------------------
#
# Project created by QtCreator 2017-08-21T00:39:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Recoder
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG      -=app_bundle
CONFIG      -= x86_64

SOURCES += main.cpp\
        mainrecoder.cpp \
    recoders.cpp

HEADERS  += mainrecoder.h \
    recoders.h

FORMS    += mainrecoder.ui


# The following lines tells Qmake to use pkg-config for opencv
QT_CONFIG -= no-pkg-confi
CONFIG  += link_pkgconfig
PKGCONFIG += opencv

LIBS += -L/usr/local/Cellar/opencv3/3.3.0_1/share/OpenCV/3rdparty/lib/
LIBS += -L/usr/local/lib/

DISTFILES += \
    haarcascade_frontalface_alt.xml \
    haarcascade_eye_tree_eyeglasses.xml
