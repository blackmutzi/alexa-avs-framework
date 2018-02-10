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
#include "directive/builtin/speechrecognizemodul.hpp"

using namespace directive;

SpeechRecognizeModul::SpeechRecognizeModul(  AlexaEvent::RequestManager * request_manager )
    : DirectiveModulInterface( request_manager ) ,
      m_stopcapture( nullptr )  ,
      m_expectspeech( nullptr )
{
    DirectiveMaker maker;
    m_stopcapture  = maker.createDirectiveCallbackCommand( maker.createDirectiveType("SpeechRecognizer" , "StopCapture") , &SpeechRecognizeModul::onStopCaptureCallback , this );
    m_expectspeech = maker.createDirectiveCallbackCommand( maker.createDirectiveType("SpeechRecognizer" , "ExpectSpeech"), &SpeechRecognizeModul::onExpectSpeechCallback, this );

    m_directives.push_back( m_stopcapture );
    m_directives.push_back( m_expectspeech );
}

void SpeechRecognizeModul::onStopCaptureDirective( const Directive * directive )
{
    Logger::instance().debug("Active-Directive", "StopCapture");
}

void SpeechRecognizeModul::onExpectSpeechDirective( const Directive * directive )
{
    Logger::instance().debug("Active-Directive", "ExpectSpeech");

    std::string dialog_request_id;
    AlexaEvent::TransportInfo * json_info = directive->getJsonInfo();

    try
    {
        json json_object = json::parse( json_info->get() );
        dialog_request_id = json_object["directive"]["header"]["dialogRequestId"];
        getRequestManager()->sendRecognizeRequest( dialog_request_id );

    } catch( std::exception e )
    {
        Logger::instance().debug("onExpectSpeechDirective", "json-object has no dialogRequestId");
    }
}

void SpeechRecognizeModul::onStopCaptureCallback( void * instance )
{
    SpeechRecognizeModul * modul = ( SpeechRecognizeModul * ) instance;
    modul->onStopCaptureDirective( ( const Directive *) modul->getStopCaptureCommand() );
}

void SpeechRecognizeModul::onExpectSpeechCallback( void * instance )
{
    SpeechRecognizeModul * modul = ( SpeechRecognizeModul * ) instance;
    modul->onExpectSpeechDirective( ( const Directive *) modul->getExpectSpeechCommand() );
}

DirectiveCallbackCommand * SpeechRecognizeModul::getStopCaptureCommand(void)
{
    return m_stopcapture;
}

DirectiveCallbackCommand * SpeechRecognizeModul::getExpectSpeechCommand(void)
{
    return m_expectspeech;
}
