TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio

INCLUDEPATH += -L/usr/include/
LIBS += -L/usr/lib/aarch64-linux-gnu -lpthread -lavcodec  -lavformat  -lavutil  -lswscale -lswresample -lavdevice -lavfilter

SOURCES += main.cpp \
    ffmpegdecoder.cpp

HEADERS += \
    ffmpegdecoder.h
