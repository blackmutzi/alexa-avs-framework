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
#ifndef EVENTMODULMANAGER_HPP
#define EVENTMODULMANAGER_HPP

#include "stdafx.hpp"
#include "utils/logger.hpp"
#include "event/builtin/eventalertmodul.hpp"
#include "event/builtin/eventaudioplayermodul.hpp"
#include "event/builtin/eventplaybackcontrollermodul.hpp"
#include "event/builtin/eventsettingsmodul.hpp"
#include "event/builtin/eventspeakermodul.hpp"
#include "event/builtin/eventspeechrecognizemodul.hpp"
#include "event/builtin/eventspeechsynthesizermodul.hpp"
#include "event/builtin/eventsystemmodul.hpp"

namespace AlexaEvent
{
    class EventModulManager
    {
        public:
            using EventModulMap = std::map< std::string , void * >;

            EventModulManager();
            ~EventModulManager();

            void initialize(void);
            void addEventModul( std::string name , void * modul );
            void * getEventModulByName( std::string name ) throw( std::exception );

            std::string GenerateMessageId(void);
            std::string GenerateDialogRequestId(void);

            EventAlertModul * getAlertModul( std::string token );
            EventAudioPlayerModul * getAudioPlayerModul( std::string token , long offset );
            EventPlaybackControllerModul * getPlaybackControllerModul(void);
            EventSettingsModul * getSettingsModul(void);
            EventSpeakerModul * getSpeakerModul( bool muted , long volume );
            EventSpeechRecognizeModul * getSpeechRecognizeModul( std::string dialog_req_id );
            EventSpeechSynthesizerModul * getSpeechSynthesizerModul( std::string token );
            EventSystemModul * getSystemModul(void);
            SynchronizeStateEvent * getEventStates(void);


         private:

            EventModulMap m_event_modul_map;
            SynchronizeStateEvent * m_sync_event;
    };
}

#endif // EVENTMODULMEDIATOR_HPP
