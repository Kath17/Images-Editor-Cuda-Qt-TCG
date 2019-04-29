#-------------------------------------------------
#
# Project created by QtCreator 2019-04-28T16:36:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Editor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        edit.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        edit.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += /home/kat/opencv-3.4.0/build/include

LIBS += -L"/home/kat/opencv-3.4.0/build/lib"
LIBS += -lopencv_calib3d
LIBS += -lopencv_core
LIBS += -lopencv_features2d
LIBS += -lopencv_flann
LIBS += -lopencv_highgui
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_imgproc
LIBS += -lopencv_ml
LIBS += -lopencv_objdetect
LIBS += -lopencv_photo
LIBS += -lopencv_shape
LIBS += -lopencv_stitching
LIBS += -lopencv_superres
LIBS += -lopencv_video
LIBS += -lopencv_videoio
LIBS += -lopencv_videostab

#LIBS += D:\opencv-build\bin\libopencv_core320.dll
#LIBS += D:\opencv-build\bin\libopencv_highgui320.dll
#LIBS += D:\opencv-build\bin\libopencv_imgcodecs320.dll
#LIBS += D:\opencv-build\bin\libopencv_imgproc320.dll
#LIBS += D:\opencv-build\bin\libopencv_features2d320.dll
#LIBS += D:\opencv-build\bin\libopencv_calib3d320.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
