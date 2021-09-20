QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    avr-asm-compiler.cpp \
    delay.cpp \
    fat_fs/src/diskio.cpp \
    fat_fs/src/fattime.cpp \
    fat_fs/src/ff.cpp \
    fat_fs/src/ff_util.cpp \
    fat_fs/src/option/cc932.cpp \
    fat_fs/src/option/cc936.cpp \
    fat_fs/src/option/cc949.cpp \
    fat_fs/src/option/cc950.cpp \
    fat_fs/src/option/ccsbcs.cpp \
    fat_fs/src/option/syncobj.cpp \
    gfx/draw.cpp \
    main.cpp \
    mainwindow.cpp \
    driver/spi.c \
    device/ssd1306.cpp \
    textEditor.cpp \
    util.cpp

HEADERS += \
    avr-asm-compiler.h \
    def.h \
    delay.h \
    fat_fs/inc/diskio.h \
    fat_fs/inc/fattime.h \
    fat_fs/inc/ff.h \
    fat_fs/inc/ff_util.h \
    fat_fs/inc/integer.h \
    ffconf.h \
    gfx/draw.h \
    mainwindow.h \
    driver/spi.h \
    device/ssd1306.h \
    textEditor.h \
    util.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
