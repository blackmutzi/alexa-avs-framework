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
#ifndef EVENTCONTEXTMODUL_HPP
#define EVENTCONTEXTMODUL_HPP

#include "stdafx.hpp"
#include "event/jsonfileloader.hpp"

namespace AlexaEvent
{
    class StateInterface;
    class EventUpdateModulInterface
    {
        public:
            EventUpdateModulInterface() = default;
            ~EventUpdateModulInterface() = default;

            virtual void update( StateInterface * ) = 0;
    };

    using EventModulList = std::list< EventUpdateModulInterface * >;
    class StateViewer
    {
         public:
            StateViewer() = default;
            virtual ~StateViewer() = default;

            void addModul( EventUpdateModulInterface * modul );
            void rmModul( EventUpdateModulInterface * modul );

            virtual void update( StateInterface * state );

         protected:

            EventModulList m_eventmodule;
    };

    class StateInterface
    {
            public:
                StateInterface() = default;
                ~StateInterface() = default;

                void setViewer( StateViewer * viewer );

           protected:

                StateViewer * m_viewer;
    };

    class AlertsState : public StateInterface
    {
        public:
            AlertsState() = default;
            ~AlertsState() = default;

            void setToken( std::string token );
            void setType( std::string type );
            void setScheduledTime( std::string scheduledTime );

            std::string p_token;
            std::string p_type;
            std::string p_scheduledTime;
    };

    class VolumeState : public StateInterface
    {
        public:
            VolumeState() = default;
            ~VolumeState() = default;

            void setVolume( long );
            void setMuted( std::string );

            long p_volume;
            std::string p_muted;
    };

    class SpeechState : public StateInterface
    {
        public:
            SpeechState() = default;
            ~SpeechState() = default;

            void setToken( std::string );
            void setOffsetInMillisesonds( long );
            void setPlayerActivity( std::string );

            std::string p_token;
            long p_offsetInMilliseconds;
            std::string p_playerActivity;
    };

    class PlaybackState : public StateInterface
    {
        public:
            PlaybackState();
            ~PlaybackState() = default;

            void setToken( std::string );
            void setOffsetInMilliseconds( long );
            void setPlayerActivity( std::string );

            std::string p_token;
            long p_offsetInMilliseconds;
            std::string p_playerActivity;
    };

    class RecognizeState : public StateInterface
    {
        public:
            RecognizeState() = default;
            ~RecognizeState() = default;

            void setWakeword( std::string );

            std::string p_wakeword;
    };

    struct SynchronizeStateEvent
    {
        AlertsState    * alertsState;
        PlaybackState  * playbackState;
        VolumeState    * volumeState;
        SpeechState    * speechState;
        RecognizeState * recognizeState;

        std::string messageId;
    };

    struct PayloadPlaybackFailedParam
    {
        std::string token;

        std::string playbackState_token;
        std::string playbackState_offset;
        std::string playbackState_activity;

        std::string error_type;
        std::string error_message;
    };

    static std::string JSON_RESOURCE_ASSET_PATH = "/etc/alexa/asset/";

    class EventContextModul
    {
        public:
            EventContextModul() = default;
            EventContextModul( SynchronizeStateEvent * event );
            ~EventContextModul() = default;

            void setSynchronizeStateEvent( SynchronizeStateEvent * event );

            const std::string createAlertsContext();
            const std::string createPlaybackContext();
            const std::string createSpeakerContext();

            const std::string createSpeechSynthesizerContext();
            const std::string createSpeechRecognizerContext();

        protected:

            SynchronizeStateEvent * m_syncstate;
    };
}

#endif // EVENTCONTEXTMODUL_HPP
