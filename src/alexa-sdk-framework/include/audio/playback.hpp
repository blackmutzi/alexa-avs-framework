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
#ifndef PLAYBACK_HPP
#define PLAYBACK_HPP

#include "include/stdafx.hpp"
#include "include/event/transportinfo.hpp"
#include "include/utils/logger.hpp"

using namespace AlexaEvent;

namespace AVS
{
    class PcmInfo
    {
        public:
            PcmInfo() = default;
            ~PcmInfo() = default;

            void setSampleRate( unsigned int rate );
            void setBitrate( unsigned int bitrate );
            void setChannels( unsigned int channels );
            void setPCMBuffer( char * );
            void setPCMFrames( unsigned int frames );

            unsigned int getBitsperSample(void);

            unsigned int p_sample_rate;
            unsigned int p_bitrate;
            unsigned int p_channels;
            unsigned int p_frames;
            char * p_pcm_buffer;
    };

    class Playback
    {
        public:
            using AUDIO_PCM_HANDLE         = snd_pcm_t;
            using AUDIO_PCM_FORMAT         = snd_pcm_format_t;
            using AUDIO_PCM_HW_PARAMS      = snd_pcm_hw_params_t;
            using AUDIO_PCM_FRAMES         = snd_pcm_uframes_t;
            using AUDIO_PCM_BUFFER         = char;

            Playback();
            ~Playback() = default;

            void setDevice( char * device );
            void setAudioInfo( TransportInfo * audio_info );
            void playNow( void );

        protected:

            PcmInfo * createPcmInfo( TransportInfo * audio_info );

            virtual void onPlaySound( PcmInfo * info );
            virtual void onOpenDevice( char * device );
            virtual void onCloseDevice(void);

        private:

            char                * m_device;
            AUDIO_PCM_HANDLE    * m_playback_handle;
            AUDIO_PCM_HW_PARAMS * m_hw_params;
            TransportInfo       * m_audio_info;

            unsigned int m_sample_rate;
            unsigned int m_channels;
            AUDIO_PCM_FORMAT m_pcm_format;

            lame_t m_lame_handler;
            hip_t  m_hip_handler;
            mp3data_struct * m_mp3_data;
    };
}

#endif // PLAYBACK_HPP
