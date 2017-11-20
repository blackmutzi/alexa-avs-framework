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
#include "include/event/builtin/eventaudioplayermodul.hpp"

using namespace AlexaEvent;

EventAudioPlayerModul::EventAudioPlayerModul(const string messageId, const string token, long offset)
    : EventUpdateModulInterface() ,
      m_messageId( messageId ) ,
      m_token( token ) ,
      m_offset( offset )
{}

void EventAudioPlayerModul::setMessageId( std::string messageId )
{
    m_messageId = messageId;
}

void EventAudioPlayerModul::setToken( std::string token )
{
    m_token = token;
}

void EventAudioPlayerModul::setOffsetInMilliseconds( long offset )
{
    m_offset = offset;
}

void EventAudioPlayerModul::update( StateInterface * state )
{
    PlaybackState * _state = ( PlaybackState * ) state;

    m_token  = _state->p_token;
    m_offset = _state->p_offsetInMilliseconds;
}

TransportInfo * EventAudioPlayerModul::createPlaybackStartedEvent(void)
{
    return createPlaybackEvent("PlaybackStarted");
}

TransportInfo * EventAudioPlayerModul::createPlaybackNearlyFinishedEvent(void)
{
    return createPlaybackEvent("PlaybackNearlyFinished");
}

TransportInfo * EventAudioPlayerModul::createProgressReportDelayElapsedEvent(void)
{
    return createPlaybackEvent("ProgressReportDelayElapsed");
}

TransportInfo * EventAudioPlayerModul::createProgressReportIntervalElapsedEvent(void)
{
    return createPlaybackEvent("ProgressReportIntervalElapsed");
}

TransportInfo * EventAudioPlayerModul::createPlaybackStutterStartedEvent(void)
{
    return createPlaybackEvent("PlaybackStutterStarted");
}

TransportInfo * EventAudioPlayerModul::createPlaybackStutterFinishedEvent(void)
{
    return createPlaybackEvent("PlaybackStutterFinished");
}

TransportInfo * EventAudioPlayerModul::createPlaybackFinishedEvent(void)
{
    return createPlaybackEvent("PlaybackFinished");
}

TransportInfo * EventAudioPlayerModul::createPlaybackPausedEvent(void)
{
    return createPlaybackEvent("PlaybackPaused");
}

TransportInfo * EventAudioPlayerModul::createPlaybackResumedEvent(void)
{
    return createPlaybackEvent("PlaybackResumed");
}

TransportInfo * EventAudioPlayerModul::createPlaybackStoppedEvent(void)
{
    return createPlaybackEvent("PlaybackStopped");
}

TransportInfo * EventAudioPlayerModul::createPlaybackFailedEvent(const PayloadPlaybackFailedParam *param )
{
    TransportInfo * info = new TransportInfo();

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("PlaybackFailedEvent.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{MESSAGE_ID_STRING}}"    , m_messageId );
    loader.addReplaceData("{{PAYLOAD_TOKEN_STRING}}" , param->token );
    loader.addReplaceData("{{STATE_TOKEN_STRING}}"   , param->playbackState_token );
    loader.addReplaceData("{{OFFSET_MS}}"            , param->playbackState_offset);
    loader.addReplaceData("{{ACTIVITY_STRING}}"      , param->playbackState_activity);

    loader.addReplaceData("{{ERROR_TYPE_STRING}}"    , param->error_type   );
    loader.addReplaceData("{{ERROR_MSG_STRING}}"     , param->error_message);

    loader.load();

    info->copy( loader.getJsonObject().c_str() , strlen( loader.getJsonObject().c_str()) );
    return info;
}

TransportInfo * EventAudioPlayerModul::createPlaybackQueueClearedEvent(void)
{
    TransportInfo * info = new TransportInfo();

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("PlaybackQueueClearedEvent.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{MESSAGE_ID_STRING}}", m_messageId );
    loader.load();

    info->copy( loader.getJsonObject().c_str() , strlen( loader.getJsonObject().c_str()) );
    return info;
}

TransportInfo * EventAudioPlayerModul::createPlaybackEvent(const string event_name)
{
    TransportInfo * info = new TransportInfo();

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("PlaybackEvent.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{EVENT_NAME}}" , event_name );
    loader.addReplaceData("{{MESSAGE_ID_STRING}}", m_messageId );
    loader.addReplaceData("{{TOKEN_STRING}}" , m_token );
    loader.addReplaceData("{{OFFSET_MS}}" , loader.convertTo( m_offset ) );
    loader.load();

    info->copy( loader.getJsonObject().c_str() , strlen( loader.getJsonObject().c_str()) );
    return info;
}
