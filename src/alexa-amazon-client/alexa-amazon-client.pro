TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -Wdeprecated-declarations

LIBS += -L $$PWD/../../libs/x86_64/ -lalexa-sdk-framework
LIBS += -lgstapp-1.0 -lgobject-2.0 -lglib-2.0 -lgstreamer-1.0 -lmp3lame -lboost_system -lboost_thread -lboost_date_time -lasound -lcurl -lnghttp2 -lssl -lcrypto -levent -levent_openssl -levent_core

INCLUDEPATH += $$PWD/../alexa-sdk-framework/
INCLUDEPATH += /usr/include/glib-2.0/
INCLUDEPATH += /usr/lib/glib-2.0/include/
INCLUDEPATH += /usr/include/gstreamer-1.0/

SOURCES += main.cpp \
           application.cpp \

HEADERS += \
    include/stdafx.hpp \
