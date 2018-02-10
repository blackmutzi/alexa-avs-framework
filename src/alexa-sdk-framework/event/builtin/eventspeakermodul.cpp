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
#include "event/builtin/eventspeakermodul.hpp"

using namespace AlexaEvent;

EventSpeakerModul::EventSpeakerModul(string messageId, long volume, bool muted)
    : m_messageId( messageId ) ,
      m_volume( volume ) ,
      m_muted( muted )
{}

void EventSpeakerModul::update(StateInterface *state)
{
    VolumeState * _state = ( VolumeState * ) state;

    m_volume = _state->p_volume;

    if( strcmp( _state->p_muted.c_str() , "true") == 0 )
    {
       m_muted = true;
    } else {
       m_muted = false;
    }
}

void EventSpeakerModul::setMessageId(string messageId)
{
    m_messageId = messageId;
}

void EventSpeakerModul::setVolume(long volume)
{
    m_volume = volume;
}

void EventSpeakerModul::setMuted(bool muted)
{
    m_muted = muted;
}

TransportInfo * EventSpeakerModul::createVolumeChangedEvent(void)
{
    return createSpeakerEvent("VolumeChanged");
}

TransportInfo * EventSpeakerModul::createMuteChangedEvent(void)
{
    return createSpeakerEvent("MuteChanged");
}

TransportInfo * EventSpeakerModul::createSpeakerEvent(string event_name)
{
    TransportInfo * info = new TransportInfo();

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("SpeakerEvent.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{EVENT_NAME}}" , event_name );
    loader.addReplaceData("{{MESSAGE_ID_STRING}}", m_messageId );
    loader.addReplaceData("{{VOLUME}}" , loader.convertTo( m_volume ) );
    loader.addReplaceData("{{MUTED}}"  , loader.convertTo( m_muted  ) );

    loader.load();

    info->copy( loader.getJsonObject().c_str() , strlen( loader.getJsonObject().c_str()) );
    return info;
}

