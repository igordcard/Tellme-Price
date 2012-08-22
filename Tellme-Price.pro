QT       += core network sql

TARGET = TellmePrice
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    retriever.cpp \
    saver.cpp \
    interpreter.cpp \
    runner.cpp \
    sqlsaver.cpp \
    mainwindow.cpp

HEADERS += \
    retriever.h \
    saver.h \
    interpreter.h \
    runner.h \
    sqlsaver.h \
    mainwindow.h

MOC_DIR = debug/moc

FORMS += \
    mainwindow.ui
