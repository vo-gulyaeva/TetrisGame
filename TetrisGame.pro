QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game/activshape.cpp \
    game/fixedshape.cpp \
    game/gamescene.cpp \
    help/help.cpp \
    main.cpp \
    mainmenu.cpp \
    game/playingfield.cpp \
    game/widgetnextelem.cpp \
    settings/settings.cpp

HEADERS += \
    game/activshape.h \
    game/fixedshape.h \
    game/gamescene.h \
    help/help.h \
    mainmenu.h \
    game/playingfield.h \
    game/widgetnextelem.h \
    settings/settings.h

FORMS += \
    help/help.ui \
    mainmenu.ui \
    game/playingfield.ui \
    game/widgetnextelem.ui \
    settings/settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
