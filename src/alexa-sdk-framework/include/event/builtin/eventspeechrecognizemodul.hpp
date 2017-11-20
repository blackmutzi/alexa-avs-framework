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
#ifndef EVENTSPEECHRECOGNIZEMODUL_HPP
#define EVENTSPEECHRECOGNIZEMODUL_HPP

#include "include/stdafx.hpp"
#include "include/event/transportinfo.hpp"
#include "include/event/builtin/eventcontextmodul.hpp"
#include "include/event/recorder.hpp"

namespace AlexaEvent
{
    class EventSpeechRecognizeModul : public EventContextModul
    {
        public:
            EventSpeechRecognizeModul() = default;
            EventSpeechRecognizeModul( SynchronizeStateEvent * event);
            ~EventSpeechRecognizeModul() = default;

            void setMessageId( std::string messageId );
            void setDialogRequestId( std::string dialog_req_id );

            TransportInfo * createSpeechRecognizeEvent(void);
            TransportInfo * createAudioInfo( Recorder * recorder );

        private:

            std::string m_messageId;
            std::string m_dialogrequest_id;
    };
}

#endif // EVENTSPEECHRECOGNIZEMODUL_HPP
