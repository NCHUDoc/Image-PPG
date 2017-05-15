#-------------------------------------------------
#
# Project created by QtCreator 2013-01-10T15:19:13
#
#-------------------------------------------------

QT       += core gui

TARGET = zed_264_camera
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    videodevice.cpp \
    cal.cpp \
    fir64.cpp \
    R_peak.cpp \
    resample.cpp \
    PSD.cpp

HEADERS  += widget.h \
    videodevice.h \
    common.h \
    common.h


FORMS    += widget.ui \
    widget.ui

INCLUDEPATH += /usr/local/qwt-6.0.1/include
LIBS += -L "/usr/local/qwt-6.0.1/lib" -lqwt
