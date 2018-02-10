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
#include "event/builtin/eventsystemmodul.hpp"

using namespace AlexaEvent;

EventSystemModul::EventSystemModul(SynchronizeStateEvent *event, string messageId)
    : EventContextModul( event ) ,
      m_messageId( messageId )
{}

void EventSystemModul::setMessageId(string messageId)
{
    m_messageId = messageId;
}

TransportInfo * EventSystemModul::createSynchronizeStateEvent(void)
{
    TransportInfo * info = new TransportInfo();

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("SystemSynchronize.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{Alerts.AlertsState}}"               ,  createAlertsContext() );
    loader.addReplaceData("{{AudioPlayer.PlaybackState}}"        ,  createPlaybackContext());
    loader.addReplaceData("{{Speaker.VolumeState}}"              ,  createSpeakerContext());
    loader.addReplaceData("{{SpeechSynthesizer.SpeechState}}"    ,  createSpeechSynthesizerContext() );
    loader.addReplaceData("{{SpeechRecognizer.RecognizerState}}" ,  createSpeechRecognizerContext());
    loader.addReplaceData("{{MESSAGE_ID_STRING}}" , m_messageId );
    loader.load();

    info->copy( loader.getJsonObject().c_str() , strlen( loader.getJsonObject().c_str()) );
    return info;
}

