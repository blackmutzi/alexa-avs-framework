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
#include "include/directive/builtin/speechsynthesizermodul.hpp"

using namespace directive;

SpeechSynthesizerModul::SpeechSynthesizerModul(  AlexaEvent::RequestManager * request_manager )
    : DirectiveModulInterface( request_manager )  ,
      m_speak( nullptr )         ,
	  m_gplayback( nullptr )
{
	/* create new playback instance */	
	m_gplayback = new AVS::GPlayback();
	boost::thread playback_thread( &SpeechSynthesizerModul::PlaybackThread , m_gplayback );

    DirectiveMaker maker;
    m_speak = maker.createDirectiveCallbackCommand( maker.createDirectiveType("SpeechSynthesizer" , "Speak") , &SpeechSynthesizerModul::onSpeakDirectiveCallback , this );
    m_directives.push_back( m_speak );
}

void SpeechSynthesizerModul::PlaybackThread( AVS::GPlayback * instance )
{
	instance->initialize( 0 , nullptr );
}

DirectiveCallbackCommand * SpeechSynthesizerModul::getSpeak(void)
{
    return m_speak;
}

void SpeechSynthesizerModul::onSpeakDirective( const Directive * directive )
{
    Logger::instance().debug("Active-Directive", "Speak");

    std::string token;
    TransportInfo * json_info = directive->getJsonInfo();

    try
    {
        json json_object = json::parse( json_info->get() );
        token = json_object["directive"]["payload"]["token"];

        if( directive->hasAudioInfo() )
                onPlayAlexa( directive->getAudioInfo() , token );

    } catch ( std::exception )
    {
        Logger::instance().debug("onSpeakDirective", "json-object has no token");
    }
}

void SpeechSynthesizerModul::onSpeakDirectiveCallback( void * instance )
{
    SpeechSynthesizerModul * modul = ( SpeechSynthesizerModul * ) instance;
    modul->onSpeakDirective( (const Directive * ) modul->getSpeak() );
}

void SpeechSynthesizerModul::onPlayAlexa( TransportInfo * audio_info , std::string token )
{
    EventSpeechSynthesizerModul * modul = getRequestManager()->getEventModulManager()->getSpeechSynthesizerModul( token );

    getRequestManager()->sendRequest( modul->createSpeechStartedEvent() );
	m_gplayback->push_buffer( audio_info );
	m_gplayback->play();

    //start loop
    while( m_gplayback->isPlaying() ){}
    getRequestManager()->sendRequest( modul->createSpeechFinishedEvent() );
    getRequestManager()->sendRequest( getRequestManager()->getEventModulManager()->getAudioPlayerModul("",0)->createPlaybackResumedEvent() );
}

