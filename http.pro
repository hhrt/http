######################################################################
# Automatically generated by qmake (2.01a) ?? ???. 12 15:52:35 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += errorcodes.h httpapp.h httpposter.h ./include/json/*.h torrent.h
SOURCES += httpapp.cpp httpposter.cpp main.cpp ./lib/*.cpp torrent.cpp

QT += network

mac {
    CONFIG -= app_bundle
}

MOC_DIR = ../tmp
DESTDIR = ../out
OBJECTS_DIR = ../tmp

CONFIG += debug

#LIBS += ./lib/
INCLUDEPATH += ./include/
