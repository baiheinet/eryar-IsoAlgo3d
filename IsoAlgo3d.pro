#-------------------------------------------------
#
# Project created by QtCreator 2016-06-16T15:52:09
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IsoAlgo3d
TEMPLATE = app

SOURCES += main.cpp \
    occQt.cpp       \
    occView.cpp     \
    IsoComponent.cpp\
    IsoEndPoint.cpp \
    IsoItemCode.cpp \
    IsoPcfReader.cpp\
    IsoPipeline.cpp \

CONFIG += c++11

HEADERS  +=        \
    occQt.h        \
    occView.h      \
    IsoAlgoAbs.h   \
    IsoComponent.h \
    IsoEndPoint.h  \
    IsoItemCode.h  \
    IsoPcfReader.h \
    IsoPipeline.h  \

FORMS    += \
    occQt.ui

RESOURCES += \
    IsoAlgo3d.qrc

win32 {
    DEFINES +=  \
        WNT
    INCLUDEPATH +=  \
        $$(CASROOT)/inc

    win32-msvc2010 {
        compiler=vc10
    }

    win32-msvc2012 {
        compiler=vc11
    }

    win32-msvc2013 {
        compiler=vc12
    }

    win32-msvc2015 {
        compiler=vc14
    }

    # Determine 32 / 64 bit and debug / release build
    !contains(QMAKE_TARGET.arch, x86_64) {
        CONFIG(debug, debug|release) {
            message("Debug 32 build")
            LIBS += -L$$(CASROOT)/win32/$$compiler/libd
        }
        else {
            message("Release 32 build")
            LIBS += -L$$(CASROOT)/win32/$$compiler/lib
        }
    }
    else {
        CONFIG(debug, debug|release) {
            message("Debug 64 build")
            LIBS += -L$$(CASROOT)/win64/$$compiler/libd
        }
        else {
            message("Release 64 build")
            LIBS += -L$$(CASROOT)/win64/$$compiler/lib
        }
    }
}

linux-g++ {
    INCLUDEPATH +=  \
        $$(CASROOT)/include/opencascade

    LIBS +=         \
        -L$$(CASROOT)/lib
}

LIBS +=         \
    -lTKernel   \
    -lTKMath    \
    -lTKG3d     \
    -lTKBRep    \
    -lTKGeomBase\
    -lTKGeomAlgo\
    -lTKTopAlgo \
    -lTKPrim    \
    -lTKBO      \
    -lTKBool    \
    -lTKOffset  \
    -lTKService \
    -lTKV3d     \
    -lTKOpenGl  \
    -lTKFillet
