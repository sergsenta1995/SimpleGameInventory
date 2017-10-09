#-------------------------------------------------
#
# Project created by QtCreator 2017-10-02T15:18:28
#
#-------------------------------------------------

QT       += core gui multimedia network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleGameInventory
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PROJECT_PATH="\"$$PWD\""

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        main-window.cpp \
        inventory.cpp \
        game-object.cpp \
    client.cpp \
    server-inventory.cpp \
    client-inventory.cpp \
    server-game-object.cpp \
    client-game-object.cpp \
    server.cpp \
    inventory-facade.cpp \
    game-object-facade.cpp

HEADERS += \
        main-window.hpp \
        inventory.hpp \
        game-object.hpp \
    client.hpp \
    server-inventory.hpp \
    client-inventory.hpp \
    server-game-object.hpp \
    client-game-object.hpp \
    server.hpp \
    inventory-facade.hpp \
    game-object-facade.hpp

FORMS += \
        main-window.ui

RESOURCES += \
        images.qrc \
        sounds.qrc \
    database.qrc
