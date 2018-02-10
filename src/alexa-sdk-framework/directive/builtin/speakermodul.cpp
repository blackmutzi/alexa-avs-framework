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
#include "directive/builtin/speakermodul.hpp"

using namespace directive;

SpeakerModul::SpeakerModul( AlexaEvent::RequestManager * request_manager )
    : DirectiveModulInterface( request_manager ) ,
      m_setvolume( nullptr ) ,
      m_adjustvolume( nullptr ) ,
      m_setmute( nullptr )
{
    DirectiveMaker maker;
    m_setvolume    =  maker.createDirectiveCallbackCommand( maker.createDirectiveType("Speaker" , "SetVolume") , &SpeakerModul::onSetVolumeCallback  , this );
    m_adjustvolume =  maker.createDirectiveCallbackCommand( maker.createDirectiveType("Speaker" , "AdjustVolume") , &SpeakerModul::onAdjustVolumeCallback , this );
    m_setmute      =  maker.createDirectiveCallbackCommand( maker.createDirectiveType("Speaker" , "SetMute") , &SpeakerModul::onSetMuteCallback , this );

    m_directives.push_back( m_setvolume );
    m_directives.push_back( m_adjustvolume );
    m_directives.push_back( m_setmute );
}

DirectiveCallbackCommand * SpeakerModul::getSetVolume(void)
{
    return m_setvolume;
}

DirectiveCallbackCommand * SpeakerModul::getAdjustVolume(void)
{
    return m_adjustvolume;
}

DirectiveCallbackCommand * SpeakerModul::getSetMute(void)
{
    return m_setmute;
}

void SpeakerModul::onSetVolumeDirective(const Directive * directive )
{
    Logger::instance().debug("Active-Directive", "SetVolume");
    AlexaEvent::TransportInfo * json_info = directive->getJsonInfo();

    try
    {
        json json_object = json::parse( json_info->get() );
        auto volume = json_object["directive"]["payload"]["volume"];

    }catch( std::exception e )
    {
        Logger::instance().debug("onSetVolumeDirective", "json-object has no volume ");
    }
}

void SpeakerModul::onAdjustVolumeDirective(const Directive * directive )
{
    Logger::instance().debug("Active-Directive", "AdjustVolume");
    AlexaEvent::TransportInfo * json_info = directive->getJsonInfo();

    try
    {
        json json_object = json::parse( json_info->get() );
        auto adjust = json_object["directive"]["payload"]["volume"];

    }catch( std::exception e )
    {
        Logger::instance().debug("onAdjustVolumeDirective", "json-object has no volume ");
    }
}

void SpeakerModul::onSetMuteDirective(const Directive * directive )
{
    Logger::instance().debug("Active-Directive", "SetMute");
    AlexaEvent::TransportInfo * json_info = directive->getJsonInfo();

    try
    {
        json json_object = json::parse( json_info->get() );
        auto mute = json_object["directive"]["payload"]["mute"];

    }catch( std::exception e )
    {
        Logger::instance().debug("onSetMuteDirective", "json-object has no mute ");
    }

}

void SpeakerModul::onSetVolumeCallback( void * instance )
{
    SpeakerModul * modul = ( SpeakerModul * ) instance;
    modul->onSetVolumeDirective( (const Directive *) modul->getSetVolume() );
}

void SpeakerModul::onAdjustVolumeCallback(void * instance)
{
    SpeakerModul * modul = ( SpeakerModul * ) instance;
    modul->onAdjustVolumeDirective( (const Directive *) modul->getAdjustVolume() );
}

void SpeakerModul::onSetMuteCallback( void * instance )
{
    SpeakerModul * modul = ( SpeakerModul * ) instance;
    modul->onSetMuteDirective( (const Directive *) modul->getSetMute() );
}
