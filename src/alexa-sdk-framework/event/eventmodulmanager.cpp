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
#include "event/eventmodulmanger.hpp"

using namespace AlexaEvent;

EventModulManager::EventModulManager() {}

EventModulManager::~EventModulManager()
{
    delete m_sync_event->volumeState;
    delete m_sync_event->speechState;
    delete m_sync_event->recognizeState;
    delete m_sync_event->playbackState;
    delete m_sync_event->alertsState;
    delete m_sync_event;
}

void EventModulManager::initialize(void)
{
    m_sync_event = new SynchronizeStateEvent();
    m_sync_event->alertsState    = new AlertsState();
    m_sync_event->playbackState  = new PlaybackState();
    m_sync_event->recognizeState = new RecognizeState();
    m_sync_event->speechState    = new SpeechState();
    m_sync_event->volumeState    = new VolumeState();

    addEventModul("AlertModul" , new EventAlertModul() );
    addEventModul("AudioPlayerModul", new EventAudioPlayerModul() );
    addEventModul("PlaybackControllerModul", new EventPlaybackControllerModul() );
    addEventModul("SettingsModul", new EventSettingsModul() );
    addEventModul("SpeakerModul" , new EventSpeakerModul() );
    addEventModul("SpeechRecognizeModul", new EventSpeechRecognizeModul() );
    addEventModul("SpeechSynthesizerModul", new EventSpeechSynthesizerModul() );
    addEventModul("SystemModul", new EventSystemModul() );
}

SynchronizeStateEvent * EventModulManager::getEventStates(void)
{
    return m_sync_event;
}

void EventModulManager::addEventModul(string name, void * modul )
{
    m_event_modul_map.insert ( std::pair< std::string , void *>( name , modul ) );
}

void * EventModulManager::getEventModulByName(string name) throw( std::exception )
{
    auto search = m_event_modul_map.find( name );

    if( search != m_event_modul_map.end() )
    {
        return search->second;

    } else {
        stringstream exception_info;
        exception_info << "Modul " << name << "not found!";
        Logger::instance().exception( exception_info.str() );
    }

    return nullptr;
}

std::string EventModulManager::GenerateMessageId(void)
{
    boost::uuids::uuid message_id_uuid = boost::uuids::uuid( boost::uuids::random_generator()() );
    return boost::lexical_cast<std::string>( message_id_uuid );
}

std::string EventModulManager::GenerateDialogRequestId( void )
{
    stringstream dialog;
    dialog << "dialog-id-";
    dialog << GenerateMessageId();
    return dialog.str();
}

EventAlertModul * EventModulManager::getAlertModul( std::string token )
{
    EventAlertModul * modul = (EventAlertModul *) getEventModulByName("AlertModul");
    modul->setMessageId( GenerateMessageId() );
    modul->setToken( token );
    return modul;
}

EventAudioPlayerModul * EventModulManager::getAudioPlayerModul( std::string token , long offset )
{
    EventAudioPlayerModul * modul = ( EventAudioPlayerModul *) getEventModulByName("AudioPlayerModul");
    modul->setMessageId( GenerateMessageId() );
    modul->setToken( token );
    modul->setOffsetInMilliseconds( offset );
    return modul;
}

EventPlaybackControllerModul * EventModulManager::getPlaybackControllerModul(void)
{
    EventPlaybackControllerModul * modul = ( EventPlaybackControllerModul * ) getEventModulByName("PlaybackControllerModul");
    modul->setMessageId( GenerateMessageId() );
    modul->setSynchronizeStateEvent( m_sync_event );
    return modul;
}

EventSettingsModul * EventModulManager::getSettingsModul(void)
{
    EventSettingsModul * modul = (EventSettingsModul * ) getEventModulByName("SettingsModul");
    modul->setMessageId( GenerateMessageId() );
    return modul;
}

EventSpeakerModul * EventModulManager::getSpeakerModul( bool muted , long volume )
{
    EventSpeakerModul * modul = ( EventSpeakerModul * ) getEventModulByName("SpeakerModul");
    modul->setMessageId( GenerateMessageId() );
    modul->setMuted( muted );
    modul->setVolume( volume );
    return modul;
}

EventSpeechRecognizeModul * EventModulManager::getSpeechRecognizeModul( std::string dialog_req_id )
{
    EventSpeechRecognizeModul * modul = ( EventSpeechRecognizeModul *) getEventModulByName("SpeechRecognizeModul");
    modul->setMessageId( GenerateMessageId() );
    modul->setDialogRequestId( dialog_req_id );
    modul->setSynchronizeStateEvent( m_sync_event );
    return modul;
}

EventSpeechSynthesizerModul * EventModulManager::getSpeechSynthesizerModul( std::string token )
{
    EventSpeechSynthesizerModul * modul = ( EventSpeechSynthesizerModul *) getEventModulByName("SpeechSynthesizerModul");
    modul->setMessageId( GenerateMessageId() );
    modul->setToken( token );
    return modul;
}

EventSystemModul * EventModulManager::getSystemModul(void)
{
    EventSystemModul * modul = (EventSystemModul *) getEventModulByName("SystemModul");
    modul->setMessageId( GenerateMessageId() );
    modul->setSynchronizeStateEvent( m_sync_event );
    return modul;
}
