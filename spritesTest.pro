QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    bulletpool.cpp \
    enemy.cpp \
    game.cpp \
    player.cpp \
    room.cpp \
    sprite.cpp \
    main.cpp \
    statusbar.cpp \
    tilemap.cpp

HEADERS += \
    bullet.h \
    bulletpool.h \
    enemy.h \
    game.h \
    player.h \
    room.h \
    sprite.h \
    statusbar.h \
    tilemap.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sprites.qrc

DISTFILES +=
