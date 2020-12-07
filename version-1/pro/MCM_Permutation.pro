#TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../src/main.cpp \
    ../src/permutator.cpp \
    ../src/structure.cpp \
    ../src/structures.cpp

HEADERS += \
    ../inc/permutator.h \
    ../inc/structure.h \
    ../inc/structures.h

INCLUDEPATH += ../inc

