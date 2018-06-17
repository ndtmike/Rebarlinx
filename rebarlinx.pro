################################################################
# rebarlinx
# Copyright (C) 2018   Michael W Hoag
################################################################

include( rebarlinxconfig.pri )

#DEFINES += VERSION_MAJOR

#DEFINES += PI="\"3.1415926\""

QT += widgets serialport

TARGET = Rebarlinx
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    console.cpp

HEADERS += \
    mainwindow.h \
    console.h

CONFIG += \
    C++11 \
    C++14

win32{

    RC_ICONS += ../icon/ndt_rebarlinx.ico
    VERSION = $$(REE_VERSION)
    QMAKE_TARGET_COMPANY = James Instruments Inc.
    QMAKE_TARGET_PRODUCT = Rebarlinx
    QMAKE_TARGET_DESCRIPTION = Upload Software for James Instruments Rebarscope
    QMAKE_TARGET_COPYRIGHT = @2018 James Instruments Inc.

#test for what compiler is to link proper libraries
    contains(QT_ARCH, i386) {
        message("Win 32-bit")
        win32:CONFIG(release, debug|release):    LIBS += -LC:/qwt-6.1.3-MSVC32/lib -lqwt
        else:win32:CONFIG(debug, debug|release): LIBS += -LC:/qwt-6.1.3-MSVC32/lib -lqwtd

        INCLUDEPATH += C:/qwt-6.1.3-MSVC32/include
        DEPENDPATH +=  C:/qwt-6.1.3-MSVC32/include
        message( $$LIBS )
        message( $$INCLUDEPATH )
    }else {
        message("Win 64-bit")
        win32:CONFIG(release, debug|release):    LIBS += -LC:/qwt-6.1.3-MSVC64/lib -lqwt
        else:win32:CONFIG(debug, debug|release): LIBS += -LC:/qwt-6.1.3-MSVC64/lib -lqwtd

        INCLUDEPATH += C:/qwt-6.1.3-MSVC64/include
        DEPENDPATH +=  C:/qwt-6.1.3-MSVC64/include

        message( $$LIBS )
        message( $$INCLUDEPATH )
    }
}
message ("")
#DISTFILES += \
#    rebarlinxconfig.pri
