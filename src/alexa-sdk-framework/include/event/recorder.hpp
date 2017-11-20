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
#ifndef RECORDER_HPP
#define RECORDER_HPP

#include "include/stdafx.hpp"
#include "include/event/transportinfo.hpp"
#include "include/utils/logger.hpp"

using namespace AVS;

namespace AlexaEvent
{
    struct CaptureInfo
    {
        char * audio_data;
        size_t audio_data_size;
        int    channels;
        int    bit_width;
    };

    class Recorder
    {
        public:

            using AUDIO_PCM_HANDLE    = snd_pcm_t;
            using AUDIO_PCM_FORMAT    = snd_pcm_format_t;
            using AUDIO_PCM_HW_PARAMS = snd_pcm_hw_params_t;
            using AUDIO_PCM_FRAMES    = snd_pcm_uframes_t;
            using AUDIO_PCM_BUFFER    = char;

            Recorder();
            ~Recorder() = default;

            void setRate( unsigned int rate );
            void setChannels( unsigned int channels );
            void setFormat( AUDIO_PCM_FORMAT format );
            void setDevice( char * device );
            void setRecordTime( long time );

            TransportInfo * recordNow(void);
            long getRecordTime(void);

        protected:

            void captureNow( CaptureInfo * info );
            void openDevice( const char * device );
            void closeDevice(void);

            static void onRecordThreadTimer( Recorder * rc , unsigned int * flags );

        private:

            AUDIO_PCM_HANDLE    * m_capture_handle;
            AUDIO_PCM_HW_PARAMS * m_hw_params;
            AUDIO_PCM_BUFFER    * m_buffer;

            char * m_device;
            char * m_audio_bytes;
            long m_record_timer;
            unsigned int m_rate;
            unsigned int m_channels;
            AUDIO_PCM_FORMAT m_pcm_format;
    };
}
#endif // RECORDER_HPP
