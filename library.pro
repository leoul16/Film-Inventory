QT += core
QT -= gui

TARGET = library
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    library.cpp \
    libraryClient-v2.cpp \
    LibraryUI.cpp

HEADERS += \
    library.h \
    LibraryUI.h

