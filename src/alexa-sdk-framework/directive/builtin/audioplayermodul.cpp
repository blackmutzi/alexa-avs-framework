/*
   Copyright (C) 2017-2018 Stefan Masuch

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "directive/builtin/audioplayermodul.hpp"

using namespace directive;


AudioPlayerModul::AudioPlayerModul( AlexaEvent::RequestManager * request_manager )
    : DirectiveModulInterface( request_manager ) ,
      m_play( nullptr ) ,
      m_stop( nullptr ) ,
      m_clearqueue( nullptr )
{
    DirectiveMaker maker;

    m_play = maker.createDirectiveCallbackCommand( maker.createDirectiveType("Audioplayer","Play")  , &AudioPlayerModul::onPlayCallback , this );
    m_stop = maker.createDirectiveCallbackCommand( maker.createDirectiveType("Audioplayer", "Stop") , &AudioPlayerModul::onStopCallback , this );
    m_clearqueue = maker.createDirectiveCallbackCommand( maker.createDirectiveType("Audioplayer", "ClearQueue") , &AudioPlayerModul::onClearQueueCallback , this );

    m_directives.push_back( m_play );
    m_directives.push_back( m_stop );
    m_directives.push_back( m_clearqueue );
}

DirectiveCallbackCommand * AudioPlayerModul::getPlay(void)
{
    return m_play;
}

DirectiveCallbackCommand * AudioPlayerModul::getStop(void)
{
    return m_stop;
}

DirectiveCallbackCommand * AudioPlayerModul::getClearQueue(void)
{
    return m_clearqueue;
}

void AudioPlayerModul::onPlayDirective(const Directive * directive )
{
    Logger::instance().debug("Active-Directive", "AudioPlayer::Play Directive");

    std::string token;
    std::string url;
    std::string dialog_request_id;
    std::string behavior;
    long offset;

    TransportInfo * json_info = directive->getJsonInfo();

    try{

        json json_object = json::parse( json_info->get() );

        dialog_request_id = json_object["directive"]["header"]["dialogRequestId"];
        behavior          = json_object["directive"]["payload"]["playBehavior"];
        token             = json_object["directive"]["payload"]["audioItem"]["stream"]["token"];
        url               = json_object["directive"]["payload"]["audioItem"]["stream"]["url"];
        offset            = json_object["directive"]["payload"]["audioItem"]["stream"]["offsetInMilliseconds"];

        if( behavior == "REPLACE_ALL")
        {
            try
            {
                /* clear playback queue complete */
                /* Get MP3 Url and connect to server and get MP3 Buffer Data ( char* , size_t ) */

                // send PlaybackStarted Event && PlaybackNearlyFinishedEvent ( for buffering )
                m_request_manager->getEventModulManager()->getEventStates()->playbackState->setOffsetInMilliseconds( offset );
                m_request_manager->getEventModulManager()->getEventStates()->playbackState->setPlayerActivity("PLAYING");
                m_request_manager->getEventModulManager()->getEventStates()->playbackState->setToken( token );
                m_request_manager->sendRequest( m_request_manager->getEventModulManager()->getAudioPlayerModul( token , offset )->createPlaybackStartedEvent() );
                m_request_manager->sendRequest( m_request_manager->getEventModulManager()->getAudioPlayerModul( token , offset )->createPlaybackNearlyFinishedEvent() );

                /* build MP3 Package and push to queue ... */
                /* start queue processing ... ( playing queue here now ) */
                /* waiting until playing queue is finished ... */

                // send PlaybackFinished Event
                m_request_manager->getEventModulManager()->getEventStates()->playbackState->setPlayerActivity("FINISHED");
                m_request_manager->sendRequest( m_request_manager->getEventModulManager()->getAudioPlayerModul( token, offset)->createPlaybackFinishedEvent() );


            }catch( std::exception e )
            {
                Logger::instance().debug("onPlayDirective - gstreamer exception " , "gstreamer playing failed - replace_all");

                PayloadPlaybackFailedParam param;
                m_request_manager->getEventModulManager()->getEventStates()->playbackState->setPlayerActivity("STOPPED");
                m_request_manager->sendRequest( m_request_manager->getEventModulManager()->getAudioPlayerModul( token , offset)->createPlaybackFailedEvent( &param ) );
            }
        }

        if( behavior == "ENQUEUE")
        {
            try
            {
                /* Get MP3 Url and connect to server and get MP3 Buffer Data ( char* , size_t ) */
                /* build MP3 Package and push to queue ... */

            }catch( std::exception e )
            {

                Logger::instance().debug("onPlayDirective - gstreamer exception " , "gstreamer playing failed - enqueue");

                PayloadPlaybackFailedParam param;
                m_request_manager->sendRequest( m_request_manager->getEventModulManager()->getAudioPlayerModul( token , offset )->createPlaybackFailedEvent( &param ) );
            }
        }


    }catch( std::exception e )
    {
       Logger::instance().debug("AudioPlayer::Play Directive", "json object is broken ...");
    }

}

void AudioPlayerModul::onStopDirective(const Directive * directive)
{
    Logger::instance().debug("Active-Directive", "AudioPlayer::Stop Directive");

    std::string dialog_request_id;
    TransportInfo * json_info = directive->getJsonInfo();

    try{

        json json_object = json::parse( json_info->get() );
        dialog_request_id = json_object["directive"]["header"]["dialogRequestId"];

        /* cancel active mp3 stream gstreamer::stop() */
        /* stop queue processing ... */

        m_request_manager->getEventModulManager()->getEventStates()->playbackState->setPlayerActivity("STOPPED");
        m_request_manager->sendRequest( m_request_manager->getEventModulManager()->getAudioPlayerModul("",0)->createPlaybackStoppedEvent() );

    }catch( std::exception e )
    {
        Logger::instance().debug("AudioPlayer::Stop Directive", "json object is broken ...");
    }

}

void AudioPlayerModul::onClearQueueDirective(const Directive * directive )
{
    Logger::instance().debug("Active-Directive", "AudioPlayer::ClearQueue Directive");

    std::string behavior;
    TransportInfo * json_info = directive->getJsonInfo();

    try{

        json json_object = json::parse( json_info->get() );
        behavior = json_object["directive"]["payload"]["clearBehavior"];

        if( behavior == "CLEAR_ENQUEUED")
        {
            /* stop queue processing */
            /* clear playback queue complete  */

            m_request_manager->sendRequest( m_request_manager->getEventModulManager()->getAudioPlayerModul("",0)->createPlaybackQueueClearedEvent());
        }

        if( behavior == "CLEAR_ALL")
        {
            m_request_manager->getEventModulManager()->getEventStates()->playbackState->setPlayerActivity("STOPPED");
            m_request_manager->sendRequest( m_request_manager->getEventModulManager()->getAudioPlayerModul("",0)->createPlaybackQueueClearedEvent());

            /* stop active streaming gstreamer::stop() */
            /* stop queue processing */
            /* clear playback queue complete */
        }


    }catch( std::exception e )
    {
        Logger::instance().debug("AudioPlayer::ClearQueue Directive", "json object is broken ...");
    }

}

void AudioPlayerModul::onPlayCallback( void * instance )
{
    AudioPlayerModul * modul = (AudioPlayerModul *) instance;
    modul->onPlayDirective( (const Directive * ) modul->getPlay() );
}

void AudioPlayerModul::onStopCallback( void * instance )
{
    AudioPlayerModul * modul = (AudioPlayerModul *) instance;
    modul->onStopDirective( (const Directive *) modul->getStop() );
}

void AudioPlayerModul::onClearQueueCallback( void * instance )
{
     AudioPlayerModul * modul = (AudioPlayerModul *) instance;
     modul->onClearQueueDirective( (const Directive *) modul->getClearQueue() );
}
