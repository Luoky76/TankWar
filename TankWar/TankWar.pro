QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    blockKinds/base.cpp \
    blockKinds/floor.cpp \
    blockKinds/gameblock.cpp \
    blockKinds/grass.cpp \
    blockKinds/redwall.cpp \
    blockKinds/steel.cpp \
    blockKinds/wall.cpp \
    blockKinds/water.cpp \
    bulletKind/bullet.cpp \
    gameparameter.cpp \
    main.cpp \
    mapStructAndData/mapstruct.cpp \
    mapStructAndData/mapdatabase.cpp \
    mybutton.cpp \
    playwidget.cpp \
    spinslider.cpp \
    tankKinds/enemytank.cpp \
    tankKinds/friendtank.cpp \
    tankKinds/heavytank.cpp \
    tankKinds/midtank.cpp \
    tankKinds/minitank.cpp \
    tankKinds/playertank.cpp \
    tankKinds/tank.cpp \
    visibleobject.cpp \
    widget.cpp

HEADERS += \
    blockKinds/base.h \
    blockKinds/floor.h \
    blockKinds/gameblock.h \
    blockKinds/grass.h \
    blockKinds/redwall.h \
    blockKinds/steel.h \
    blockKinds/wall.h \
    blockKinds/water.h \
    bulletKind/bullet.h \
    gameparameter.h \
    mapStructAndData/mapstruct.h \
    mapStructAndData/mapdatabase.h \
    mybutton.h \
    playwidget.h \
    spinslider.h \
    tankKinds/enemytank.h \
    tankKinds/friendtank.h \
    tankKinds/heavytank.h \
    tankKinds/midtank.h \
    tankKinds/minitank.h \
    tankKinds/playertank.h \
    tankKinds/tank.h \
    visibleobject.h \
    widget.h

FORMS += \
    spinslider.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../res.qrc
