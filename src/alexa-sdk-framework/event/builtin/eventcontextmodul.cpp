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
#include "include/event/builtin/eventcontextmodul.hpp"

using namespace AlexaEvent;

void StateViewer::addModul(EventUpdateModulInterface *modul)
{
    m_eventmodule.push_back( modul );
}

void StateViewer::rmModul(EventUpdateModulInterface *modul)
{
    m_eventmodule.remove( modul );
}

void StateViewer::update(StateInterface *state)
{
    for( EventUpdateModulInterface * modul : m_eventmodule )
    {
        modul->update( state );
    }
}

void StateInterface::setViewer(StateViewer *viewer)
{
    m_viewer = viewer;
}

void AlertsState::setToken(string token)
{
    p_token = token;
}

void AlertsState::setType(string type)
{
    p_type = type;
}

void AlertsState::setScheduledTime(string scheduledTime)
{
    p_scheduledTime = scheduledTime;
}

void VolumeState::setMuted(string muted )
{
    p_muted = muted;
}

void VolumeState::setVolume(long volume )
{
    p_volume = volume;
}

void SpeechState::setToken(string token )
{
    p_token = token;
}

void SpeechState::setOffsetInMillisesonds(long offset)
{
    p_offsetInMilliseconds = offset;
}

void SpeechState::setPlayerActivity(string playeractivity )
{
    p_playerActivity = playeractivity;
}

PlaybackState::PlaybackState()
    : p_token("") ,
      p_offsetInMilliseconds(0) ,
      p_playerActivity("IDLE")
{}

void PlaybackState::setToken(string token )
{
    p_token = token;
}

void PlaybackState::setOffsetInMilliseconds(long offset )
{
    p_offsetInMilliseconds = offset;
}

void PlaybackState::setPlayerActivity(string player_activity )
{
    p_playerActivity = player_activity;
}

void RecognizeState::setWakeword(string wakeword)
{
    p_wakeword = wakeword;
}

EventContextModul::EventContextModul(SynchronizeStateEvent *event)
    : m_syncstate( event )
{}

void EventContextModul::setSynchronizeStateEvent(SynchronizeStateEvent *event)
{
    m_syncstate = event;
}

const std::string EventContextModul::createAlertsContext( void )
{
    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("AlertContext.json");

    JsonFileLoader loader( json_file );

    loader.load();

    return loader.getJsonObject();
}

const std::string EventContextModul::createPlaybackContext( void )
{
    PlaybackState * state = m_syncstate->playbackState;

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("PlaybackContext.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{TOKEN_STRING}}", state->p_token );
    loader.addReplaceData("{{MS}}", loader.convertTo( state->p_offsetInMilliseconds ) );
    loader.addReplaceData("{{ACTIVITY_STRING}}", state->p_playerActivity );

    loader.load();

    return loader.getJsonObject();
}

const std::string EventContextModul::createSpeakerContext( void )
{
    VolumeState * state = m_syncstate->volumeState;

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("SpeakerContext.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{VOLUME}}", loader.convertTo( state->p_volume ) );
    loader.addReplaceData("{{MUTED}}" , state->p_muted );;

    loader.load();

    return loader.getJsonObject();
}

const std::string EventContextModul::createSpeechRecognizerContext( void )
{
    RecognizeState * state = m_syncstate->recognizeState;

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("SpeechRecognizeContext.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{WAKEWORD_STRING}}", state->p_wakeword );

    loader.load();

    return loader.getJsonObject();
}

const std::string EventContextModul::createSpeechSynthesizerContext( void )
{
    SpeechState * state = m_syncstate->speechState;

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("SpeechSynthesizerContext.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{TOKEN_STRING}}", state->p_token );
    loader.addReplaceData("{{MS}}", loader.convertTo( state->p_offsetInMilliseconds ) );
    loader.addReplaceData("{{ACTIVITY_STRING}}" , state->p_playerActivity );;

    loader.load();

    return loader.getJsonObject();
}


