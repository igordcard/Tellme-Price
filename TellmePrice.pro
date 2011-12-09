#-------------------------------------------------
#
# Project created by QtCreator 2011-11-28T00:05:07
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = TellmePrice
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    retriever.cpp \
    saver.cpp \
    interpreter.cpp \
    runner.cpp

HEADERS += \
    retriever.h \
    saver.h \
    interpreter.h \
    runner.h

MOC_DIR = debug/moc






