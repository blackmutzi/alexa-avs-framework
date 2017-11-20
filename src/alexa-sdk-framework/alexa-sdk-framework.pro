#-------------------------------------------------
#
# Project created by QtCreator 2017-11-20T19:24:07
#
#-------------------------------------------------

QT       -= core gui

TARGET = alexa-sdk-framework
TEMPLATE = lib


QMAKE_CXXFLAGS += -std=c++11 -Wdeprecated-declarations
DEFINES += ALEXASDKFRAMEWORK_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lgstapp-1.0 -lgobject-2.0 -lglib-2.0 -lgstreamer-1.0 -lmp3lame -lboost_system -lboost_thread -lboost_date_time -lasound -lcurl -lnghttp2 -lssl -lcrypto -levent -levent_openssl -levent_core
INCLUDEPATH += $$PWD/include/
INCLUDEPATH += /usr/include/glib-2.0/
INCLUDEPATH += /usr/lib/glib-2.0/include/
INCLUDEPATH += /usr/include/gstreamer-1.0/


SOURCES += event/transportinfo.cpp \
    event/transportmaker.cpp \
    event/transportdatainferface.cpp \
    event/recorder.cpp \
    event/jsonfileloader.cpp \
    event/fileloader.cpp \
    http2/http2data.cpp \
    http2/http2transportdata.cpp \
    http2/http2response.cpp \
    http2/http2connection.cpp \
    http2/http2transportqueue.cpp \
    http2/http2pipeline.cpp \
    event/transportheaderinfo.cpp \
    amazon-client/pipeline.cpp \
    event/http2headerbuilder.cpp \
    event/jsonheaderbuilder.cpp \
    event/jsonbodybuilder.cpp \
    event/jsonobject.cpp \
    event/http2headerpost.cpp \
    event/http2headerget.cpp \
    event/eventstreamrequest.cpp \
    event/recognizestreamrequest.cpp \
    directive/directive.cpp \
    directive/directiveiterator.cpp \
    directive/directiveobserver.cpp \
    directive/directivecommandproxy.cpp \
    directive/directivecommand.cpp \
    directive/directivecommandinvoker.cpp \
    directive/builtin/speechrecognizemodul.cpp \
    directive/builtin/speechsynthesizermodul.cpp \
    directive/builtin/audioplayermodul.cpp \
    directive/builtin/alertmodul.cpp \
    directive/builtin/notificationmodul.cpp \
    directive/builtin/speakermodul.cpp \
    directive/builtin/systemmodul.cpp \
    event/builtin/eventspeechrecognizemodul.cpp \
    event/builtin/eventcontextmodul.cpp \
    event/builtin/eventspeechsynthesizermodul.cpp \
    event/builtin/eventalertmodul.cpp \
    event/builtin/eventaudioplayermodul.cpp \
    event/builtin/eventplaybackcontrollermodul.cpp \
    event/builtin/eventsettingsmodul.cpp \
    event/builtin/eventspeakermodul.cpp \
    event/builtin/eventsystemmodul.cpp \
    amazon-client/controller.cpp \
    http2/http2responseanalyse.cpp \
    utils/logger.cpp \
    audio/playback.cpp \
    http2/http2pipelineinterface.cpp \
    event/eventmodulmanager.cpp \
    auth/authenticator.cpp \
    auth/authinfo.cpp \
    auth/httppipeline.cpp \
    auth/httpinterface.cpp \
    auth/httpresponse.cpp \
    audio/gplayback.cpp \
    server/directiveproxy.cpp \
    server/serverinterface.cpp \
    server/client.cpp \
    server/alexaserver.cpp \
    server/transferstate.cpp \
    server/transportdatamanager.cpp \
    server/transportdataobserver.cpp \
    server/transportdatalistener.cpp \
    utils/console.cpp \
    http2/pipelineconnectinfo.cpp \
    http2/http2headerinfo.cpp \
    directive/directivemanager.cpp \
    event/requestmanager.cpp \
    directive/directivemodulinterface.cpp \
    directive/directivemaker.cpp \
    amazon-client/alexaamazonclient.cpp

HEADERS += \
    include/stdafx.hpp \
    include/avs.hpp \
    include/transportlayer.hpp \
    include/requestlayer.hpp \
    include/directivelayer.hpp \
    include/event/transport_builder_interface.hpp \
    include/event/transportinfo.hpp \
    include/event/transportmaker.hpp \
    include/event/recorder.hpp \
    include/http2/http2data.hpp \
    include/http2/http2response.hpp \
    include/http2/http2connection.hpp \
    include/http2/http2responseeventinterface.hpp \
    include/http2/http2transportdata.hpp \
    include/http2/http2transportqueue.hpp \
    include/http2/http2pipeline.hpp \
    include/event/transportheaderinfo.hpp \
    include/event/http2headerbuilder.hpp \
    include/event/jsonheaderbuilder.hpp \
    include/event/jsonbodybuilder.hpp \
    include/event/jsonobject.hpp \
    include/event/http2headerpost.hpp \
    include/event/http2headerget.hpp \
    include/event/eventstreamrequest.hpp \
    include/event/recognizestreamrequest.hpp \
    include/event/jsonfileloader.hpp \
    include/event/fileloader.hpp \
    include/directive/directive.hpp \
    include/directive/directiveiterator.hpp \
    include/directive/directiveobserver.hpp \
    include/directive/directivelistenerinterface.hpp \
    include/directive/directivecommandproxy.hpp \
    include/directive/directivecommand.hpp \
    include/directive/directivecommandinvoker.hpp \
    include/directive/builtin/speechrecognizemodul.hpp \
    include/directive/builtin/speechsynthesizermodul.hpp \
    include/directive/builtin/audioplayermodul.hpp \
    include/directive/builtin/alertmodul.hpp \
    include/directive/builtin/notificationmodul.hpp \
    include/directive/builtin/speakermodul.hpp \
    include/directive/builtin/systemmodul.hpp \
    include/event/builtin/eventspeechrecognizemodul.hpp \
    include/event/builtin/eventcontextmodul.hpp \
    include/event/builtin/eventspeechsynthesizermodul.hpp \
    include/event/builtin/eventalertmodul.hpp \
    include/event/builtin/eventaudioplayermodul.hpp \
    include/event/builtin/eventplaybackcontrollermodul.hpp \
    include/event/builtin/eventsettingsmodul.hpp \
    include/event/builtin/eventspeakermodul.hpp \
    include/event/builtin/eventsystemmodul.hpp \
    include/amazon-client/controller.hpp \
    include/amazon-client/pipeline.hpp \
    include/http2/http2responseanalyse.hpp \
    include/utils/logger.hpp \
    include/nlohmann_json.hpp \
    include/audio/playback.hpp \
    include/event/transportdatainterface.hpp \
    include/http2/http2pipelineinterface.hpp \
    include/event/eventmodulmanger.hpp \
    include/auth/authenticator.hpp \
    include/auth/authinfo.hpp \
    include/auth/httppipeline.hpp \
    include/auth/httpinterface.hpp \
    include/auth/httpresponse.hpp \
    include/audio/gplayback.hpp \
    include/server/directiveproxy.hpp \
    include/server/serverinterface.hpp \
    include/server/client.hpp \
    include/server/alexaserver.hpp \
    include/server/transferstate.hpp \
    include/server/transportdatamanager.hpp \
    include/server/transportdataobserver.hpp \
    include/server/transportdatalistener.hpp \
    include/utils/console.hpp \
    include/http2/pipelineconnectinfo.hpp \
    include/http2/http2headerinfo.hpp \
    include/directive/directivemanager.hpp \
    include/event/requestmanager.hpp \
    include/directive/directivemodulinterface.hpp \
    include/directive/directivemaker.hpp \
    include/amazon-client/alexaamazonclient.hpp


unix {
    target.path = /usr/lib
    INSTALLS += target
}
