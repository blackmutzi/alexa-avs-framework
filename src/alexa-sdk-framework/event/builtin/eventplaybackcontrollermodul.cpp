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
#include "event/builtin/eventplaybackcontrollermodul.hpp"

using namespace AlexaEvent;

EventPlaybackControllerModul::EventPlaybackControllerModul(SynchronizeStateEvent *event)
    : EventContextModul( event )
{}

void EventPlaybackControllerModul::setMessageId(string messageid)
{
    m_messageId = messageid;
}

TransportInfo * EventPlaybackControllerModul::createPlayCommandIssuedEvent(void)
{
    return createCommandEvent("PlayCommandIssued");
}

TransportInfo * EventPlaybackControllerModul::createPauseCommandIssuedEvent(void)
{
    return createCommandEvent("PauseCommandIssued");
}

TransportInfo * EventPlaybackControllerModul::createNextCommandIssuedEvent(void)
{
    return createCommandEvent("NextCommandIssued");
}

TransportInfo * EventPlaybackControllerModul::createPreviousCommandIssuedEvent(void)
{
    return createCommandEvent("PreviousCommandIssued");
}

TransportInfo * EventPlaybackControllerModul::createCommandEvent(const string event_name)
{
    TransportInfo * info = new TransportInfo();

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("PlaybackControllerEvent.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{Alerts.AlertsState}}"               ,  createAlertsContext()   );
    loader.addReplaceData("{{AudioPlayer.PlaybackState}}"        ,  createPlaybackContext() );
    loader.addReplaceData("{{Speaker.VolumeState}}"              ,  createSpeakerContext()  );
    loader.addReplaceData("{{SpeechSynthesizer.SpeechState}}"    ,  createSpeechSynthesizerContext() );
    loader.addReplaceData("{{SpeechRecognizer.RecognizerState}}" ,  createSpeechRecognizerContext() );

    loader.addReplaceData("{{MESSAGE_ID_STRING}}" , m_messageId );
    loader.addReplaceData("{{EVENT_NAME}}" , event_name );

    loader.load();

    info->copy( loader.getJsonObject().c_str() , strlen( loader.getJsonObject().c_str()) );
    return info;
}
