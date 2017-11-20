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
#ifndef EVENTALERTMODUL_HPP
#define EVENTALERTMODUL_HPP

#include "include/stdafx.hpp"
#include "include/event/transportinfo.hpp"
#include "include/event/builtin/eventcontextmodul.hpp"

namespace AlexaEvent
{
    class EventAlertModul : public EventUpdateModulInterface
    {
        public:
            EventAlertModul() = default;
            EventAlertModul( const std::string messageId , const std::string token );
            ~EventAlertModul() = default;

            void setMessageId( const std::string messageId );
            void setToken( const std::string token );
            void update( StateInterface * );

            TransportInfo * createSetAlertSucceededEvent(void);
            TransportInfo * createSetAlertFailedEvent(void);
            TransportInfo * createDeleteAlertFailedEvent(void);
            TransportInfo * createDeleteAlertSucceededEvent(void);
            TransportInfo * createAlertStartedEvent(void);
            TransportInfo * createAlertStoppedEvent(void);
            TransportInfo * createAlertEnteredForegroundEvent(void);
            TransportInfo * createAlertEnteredBackgroundEvent(void);

        protected:

            TransportInfo * createAlertEvent( const std::string event_name );

        private:

            std::string m_messageId;
            std::string m_token;
    };
}

#endif // EVENTALERTMODUL_HPP
