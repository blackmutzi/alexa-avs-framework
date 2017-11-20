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
#ifndef EVENTSPEAKERMODUL_HPP
#define EVENTSPEAKERMODUL_HPP

#include "include/stdafx.hpp"
#include "include/event/transportinfo.hpp"
#include "include/event/builtin/eventcontextmodul.hpp"

namespace AlexaEvent
{
    class EventSpeakerModul : public EventUpdateModulInterface
    {
        public:
            EventSpeakerModul() = default;
            EventSpeakerModul( std::string messageId , long volume , bool muted );
            ~EventSpeakerModul() = default;

            void setMessageId( std::string messageId );
            void setVolume( long volume );
            void setMuted( bool muted );

            TransportInfo * createVolumeChangedEvent(void);
            TransportInfo * createMuteChangedEvent(void);

        protected:

            void update(StateInterface * state );
            TransportInfo * createSpeakerEvent( std::string event_name );

        private:

            std::string m_messageId;
            long m_volume;
            bool m_muted;
    };
}

#endif // EVENTSPEAKERMODUL_HPP
