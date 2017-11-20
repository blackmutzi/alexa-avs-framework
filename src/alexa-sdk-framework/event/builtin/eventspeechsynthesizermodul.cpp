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
#include "include/event/builtin/eventspeechsynthesizermodul.hpp"

using namespace AlexaEvent;

void EventSpeechSynthesizerModul::update(StateInterface *state)
{
    SpeechState * _state = ( SpeechState * ) state;
    m_token = _state->p_token;
}

void EventSpeechSynthesizerModul::setMessageId(string messageId)
{
    m_messageId = messageId;
}

void EventSpeechSynthesizerModul::setToken(string token)
{
    m_token = token;
}

TransportInfo * EventSpeechSynthesizerModul::createSpeechStartedEvent(void)
{
    TransportInfo * info = new TransportInfo();

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("SpeechStartedEvent.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{MESSAGE_ID_STRING}}", m_messageId );
    loader.addReplaceData("{{TOKEN_STRING}}" , m_token );
    loader.load();

    info->copy( loader.getJsonObject().c_str() , strlen( loader.getJsonObject().c_str()) );
    return info;
}

TransportInfo * EventSpeechSynthesizerModul::createSpeechFinishedEvent(void)
{
    TransportInfo * info = new TransportInfo();

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("SpeechFinishedEvent.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{MESSAGE_ID_STRING}}", m_messageId );
    loader.addReplaceData("{{TOKEN_STRING}}" , m_token );
    loader.load();

    info->copy( loader.getJsonObject().c_str() , strlen( loader.getJsonObject().c_str()) );
    return info;
}
