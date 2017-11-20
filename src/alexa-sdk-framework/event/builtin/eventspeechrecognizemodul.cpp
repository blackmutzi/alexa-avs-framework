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
#include "include/event/builtin/eventspeechrecognizemodul.hpp"

using namespace AlexaEvent;

EventSpeechRecognizeModul::EventSpeechRecognizeModul( SynchronizeStateEvent *event)
    : EventContextModul( event )
{}

void EventSpeechRecognizeModul::setMessageId(string messageId)
{
    m_messageId = messageId;
}

void EventSpeechRecognizeModul::setDialogRequestId(string dialog_req_id)
{
    m_dialogrequest_id = dialog_req_id;
}

TransportInfo * EventSpeechRecognizeModul::createSpeechRecognizeEvent(void)
{
    TransportInfo * info = new TransportInfo();

    std::string json_file;
    json_file.append( AlexaEvent::JSON_RESOURCE_ASSET_PATH );
    json_file.append("SpeechRecognizeEvent.json");

    JsonFileLoader loader( json_file );

    loader.addReplaceData("{{Alerts.AlertsState}}"               ,  createAlertsContext()  );
    loader.addReplaceData("{{AudioPlayer.PlaybackState}}"        ,  createPlaybackContext() );
    loader.addReplaceData("{{Speaker.VolumeState}}"              ,  createSpeakerContext());
    loader.addReplaceData("{{SpeechSynthesizer.SpeechState}}"    ,  createSpeechSynthesizerContext() );
    loader.addReplaceData("{{SpeechRecognizer.RecognizerState}}" ,  createSpeechRecognizerContext());

    loader.addReplaceData("{{MESSAGE_ID_STRING}}" , m_messageId  );
    loader.addReplaceData("{{DIALOG_STRING}}"     , m_dialogrequest_id );

    loader.addReplaceData("{{PROFILE_STRING}}" , "NEAR_FIELD");
    loader.addReplaceData("{{FORMAT_STRING}}"  , "AUDIO_L16_RATE_16000_CHANNELS_1" );

    //@TODO - AVS has was changed here ...
    loader.addReplaceData("{{TYPE_STRING}}", "TAP" );
    loader.addReplaceData("{{LONG}}", loader.convertTo( (long) 0));
    loader.load();

    info->copy( loader.getJsonObject().c_str() , strlen( loader.getJsonObject().c_str()) );
    return info;
}

TransportInfo * EventSpeechRecognizeModul::createAudioInfo(Recorder *recorder)
{
    return recorder->recordNow();
}

