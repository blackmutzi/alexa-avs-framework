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
#ifndef EVENTPLAYBACKCONTROLLERMODUL_HPP
#define EVENTPLAYBACKCONTROLLERMODUL_HPP

#include "stdafx.hpp"
#include "event/transportinfo.hpp"
#include "event/builtin/eventcontextmodul.hpp"

namespace AlexaEvent
{
    class EventPlaybackControllerModul : public EventContextModul
    {
        public:
            EventPlaybackControllerModul() = default;
            EventPlaybackControllerModul( SynchronizeStateEvent * event);
            ~EventPlaybackControllerModul() = default;

            void setMessageId( std::string messageid );

            TransportInfo * createPlayCommandIssuedEvent(void);
            TransportInfo * createPauseCommandIssuedEvent(void);
            TransportInfo * createNextCommandIssuedEvent(void);
            TransportInfo * createPreviousCommandIssuedEvent(void);

        protected:

            TransportInfo * createCommandEvent( const std::string event_name );

        private:

            std::string m_messageId;

    };
}

#endif // EVENTPLAYBACKCONTROLLERMODUL_HPP
