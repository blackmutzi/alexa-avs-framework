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
#include "event/builtin/eventalertmodul.hpp"

using namespace AlexaEvent;

EventAlertModul::EventAlertModul( const std::string messageId , const std::string token )
    : m_messageId( messageId ) ,
      m_token( token )
{}

void EventAlertModul::setMessageId(const string messageId)
{
    m_messageId = messageId;
}

void EventAlertModul::setToken(const string token)
{
    m_token = token;
}

void EventAlertModul::update( StateInterface * state )
{
    AlertsState * _state = (AlertsState* ) state;
    setToken( _state->p_token );
}

TransportInfo * EventAlertModul::createSetAlertSucceededEvent(void)
{
    return createAlertEvent("SetAlertSucceeded");
}

TransportInfo * EventAlertModul::createSetAlertFailedEvent(void)
{
    return createAlertEvent("SetAlertFailed");
}

TransportInfo * EventAlertModul::createDeleteAlertFailedEvent(void)
{
    return createAlertEvent("DeleteAlertFailed");
}

TransportInfo * EventAlertModul::createDeleteAlertSucceededEvent(void)
{
    return createAlertEvent("DeleteAlertSucceeded");
}

TransportInfo * EventAlertModul::createAlertStartedEvent(void)
{
    return createAlertEvent("AlertStarted");
}

TransportInfo * EventAlertModul::createAlertStoppedEvent(void)
{
    return createAlertEvent("AlertStopped");
}

TransportInfo * EventAlertModul::createAlertEnteredForegroundEvent(void)
{
    return createAlertEvent("AlertEnteredForeground");
}

TransportInfo * EventAlertModul::createAlertEnteredBackgroundEvent(void)
{
    return createAlertEvent("AlertEnteredBackground");
}

TransportInfo * EventAlertModul::createAlertEvent(const string event_name)
{
    TransportInfo * info = new TransportInfo();

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("AlertEvent.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{EVENT_NAME}}" , event_name );
    loader.addReplaceData("{{MESSAGE_ID_STRING}}", m_messageId );
    loader.addReplaceData("{{TOKEN_STRING}}" , m_token );

    loader.load();

    info->copy( loader.getJsonObject().c_str() , strlen( loader.getJsonObject().c_str()) );
    return info;
}





