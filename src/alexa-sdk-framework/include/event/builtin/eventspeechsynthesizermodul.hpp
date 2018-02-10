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
#ifndef EVENTSPEECHSYNTHESIZERMODUL_HPP
#define EVENTSPEECHSYNTHESIZERMODUL_HPP

#include "stdafx.hpp"
#include "event/transportinfo.hpp"
#include "event/builtin/eventcontextmodul.hpp"

namespace AlexaEvent
{
    class EventSpeechSynthesizerModul : public EventUpdateModulInterface
    {
        public:
            EventSpeechSynthesizerModul() = default;
            ~EventSpeechSynthesizerModul() = default;

            void setMessageId( std::string messageId );
            void setToken( std::string token );

            TransportInfo * createSpeechStartedEvent(void);
            TransportInfo * createSpeechFinishedEvent(void);

        protected:

            void update(StateInterface * state);

        private:

            std::string m_messageId;
            std::string m_token;

    };

}

#endif // EVENTSPEECHSYNTHESIZERMODUL_HPP
