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
#ifndef EVENTAUDIOPLAYERMODUL_HPP
#define EVENTAUDIOPLAYERMODUL_HPP

#include "stdafx.hpp"
#include "event/transportinfo.hpp"
#include "event/builtin/eventcontextmodul.hpp"

namespace AlexaEvent
{
    class EventAudioPlayerModul : public EventUpdateModulInterface
    {
        public:
            EventAudioPlayerModul() = default;
            EventAudioPlayerModul( const std::string messageId , const std::string token , long offset );
            ~EventAudioPlayerModul() = default;

            void setMessageId( std::string messageId );
            void setToken( std::string token );
            void setOffsetInMilliseconds( long offset );

            TransportInfo * createPlaybackStartedEvent(void);
            TransportInfo * createPlaybackNearlyFinishedEvent(void);
            TransportInfo * createProgressReportDelayElapsedEvent(void);
            TransportInfo * createProgressReportIntervalElapsedEvent(void);
            TransportInfo * createPlaybackStutterStartedEvent(void);
            TransportInfo * createPlaybackStutterFinishedEvent(void);
            TransportInfo * createPlaybackFinishedEvent(void);
            TransportInfo * createPlaybackPausedEvent(void);
            TransportInfo * createPlaybackResumedEvent(void);
            TransportInfo * createPlaybackStoppedEvent(void);
            TransportInfo * createPlaybackFailedEvent(const PayloadPlaybackFailedParam *param);
            TransportInfo * createPlaybackQueueClearedEvent(void);

        protected:

            void update(StateInterface *state);
            TransportInfo * createPlaybackEvent( const std::string event_name );

        private:

            std::string m_messageId;
            std::string m_token;
            long m_offset;
    };
}

#endif // EVENTAUDIOPLAYERMODUL_HPP
