#include "event/requestmanager.hpp"

RequestManager::RequestManager( const char * access_token , const char * boundary )
    : m_event_manager( nullptr ) ,
      m_pipeline( nullptr ) ,
      m_access_token( access_token ) ,
      m_boundary( boundary )
{}

RequestManager::~RequestManager(){}

void RequestManager::setEventModulManager(EventModulManager *manager)
{
    m_event_manager = manager;
}

void RequestManager::setAlexaPipeline(AVS::Pipeline *pipeline)
{
    m_pipeline = pipeline;
}

EventModulManager * RequestManager::getEventModulManager(void)
{
    return m_event_manager;
}

AVS::Pipeline * RequestManager::getPipeline(void)
{
    return m_pipeline;
}

void RequestManager::sendRequest(TransportInfo *info)
{
    EventStreamRequest request;
    request.setAccessToken( m_access_token );
    request.setBoundary( m_boundary );
    request.setCustomJsonTransportInfo( info );

    m_pipeline->push_transport( request.buildTransportData() );
}

void RequestManager::sendRecognizeRequest(string dialog_request_id)
{
    Recorder recorder;
    sendRecognizeRequest( dialog_request_id , recorder.recordNow() );
}

void RequestManager::sendRecognizeRequest(string dialog_request_id, TransportInfo *audio_info)
{

    RecognizeStreamRequest request;
    request.setAccessToken( m_access_token );
    request.setBoundary( m_boundary );
    request.setRecognizeJson( m_event_manager->getSpeechRecognizeModul( dialog_request_id )->createSpeechRecognizeEvent() );
    request.setAudioInfo( audio_info );

    m_pipeline->push_transport( request.buildTransportData() );
    sendRequest( m_event_manager->getAudioPlayerModul("",0)->createPlaybackPausedEvent() );
}
