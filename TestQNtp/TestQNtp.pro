#-------------------------------------------------
#
# Project created by QtCreator 2015-04-25T13:20:17
#
#-------------------------------------------------

QT       += core

QT       -= gui
QT       += network

TARGET = TestQNtp
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../include/qntp

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../debug \
            -lqntpd
}
CONFIG(release, debug|release) {
    LIBS += -L$$PWD/../release \
            -lqntp
}



SOURCES += main.cpp \
    NtpApp.cpp

HEADERS += \
    NtpApp.h
