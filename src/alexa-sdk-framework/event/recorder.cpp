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
#include "include/event/recorder.hpp"

using namespace AlexaEvent;

Recorder::Recorder()
    : m_capture_handle( nullptr ) ,
      m_hw_params( nullptr )      ,
      m_buffer( nullptr )         ,
      m_device("default")         ,
      m_audio_bytes( nullptr )    ,
      m_record_timer(5)           ,
      m_rate(16000)               ,
      m_channels(1)               ,
      m_pcm_format( SND_PCM_FORMAT_S16_LE )
{}

void Recorder::setRate(unsigned int rate)
{
    m_rate = rate;
}

void Recorder::setChannels(unsigned int channels)
{
    m_channels = channels;
}

void Recorder::setFormat(AUDIO_PCM_FORMAT format)
{
    m_pcm_format = format;
}

void Recorder::setDevice(char *device)
{
    m_device = device;
}

void Recorder::setRecordTime(long time)
{
    m_record_timer = time;
}

long Recorder::getRecordTime(void)
{
    return m_record_timer;
}

TransportInfo * Recorder::recordNow(void)
{
    TransportInfo * transport_info = new TransportInfo();

    openDevice( m_device );

    CaptureInfo cap_info;
    cap_info.audio_data = NULL;
    cap_info.audio_data_size = 0;
    cap_info.bit_width  = snd_pcm_format_width( SND_PCM_FORMAT_S16_LE );
    cap_info.channels   = m_channels;

    captureNow( &cap_info );    
	transport_info->copy( cap_info.audio_data , cap_info.audio_data_size );
    free( cap_info.audio_data );

    closeDevice();

    return transport_info;
}

void Recorder::onRecordThreadTimer(Recorder *rc, unsigned int *flags)
{
    boost::this_thread::sleep(boost::posix_time::seconds( rc->getRecordTime() ));
    *flags = 0;
}

void Recorder::captureNow( CaptureInfo * info )
{
    unsigned int flags = 1 , while_counter = 1 , offset = 0;
    snd_pcm_uframes_t buffer_frames = 1024 , pcmreturn = 0;
    size_t buffer_size = 0;
    char * audio_stream = NULL;
    char * audio_test   = NULL;

    /* Buffer Size Algo. */
    buffer_size = buffer_frames * ( info->bit_width / ( 8 * info->channels ) );

    /* -- allocate buffers --*/
    info->audio_data = (char*) malloc(buffer_size);
    audio_stream     = (char*) malloc(buffer_size);

    if( info->audio_data == NULL || audio_stream == NULL )
    {
        Logger::instance().error("unknown memory error");
    }

    boost::thread recordthreadtimer( &Recorder::onRecordThreadTimer , this , &flags );

    while( flags )
    {
        /* read from device */
        memset( audio_stream , 0 , buffer_size );
        pcmreturn = snd_pcm_readi( m_capture_handle , audio_stream , buffer_frames );

        /* if overrun throw */
        if (pcmreturn == (snd_pcm_uframes_t) -EPIPE )
            snd_pcm_prepare( m_capture_handle );

        /* save audio bytes */
        if( pcmreturn == buffer_frames )
        {
            info->audio_data_size = buffer_size * while_counter;
            offset = info->audio_data_size - buffer_size;

            if( offset != 0 ) 
		    {
                audio_test = (char*) realloc( info->audio_data , info->audio_data_size );
                if( audio_test != NULL )
                {
                    info->audio_data = audio_test;
                    memset( info->audio_data + offset , 0 , buffer_size );
                    memcpy( info->audio_data + offset , audio_stream , buffer_size );
                    while_counter++;

                } else {
                    Logger::instance().error("zu wenig speicherplatz ...");
                }


            } else {

                memset( info->audio_data , 0 , buffer_size );
                memcpy( info->audio_data , audio_stream , buffer_size );
                while_counter++;
            }
        }
    }

    // free resources
    free( audio_stream );
}

void Recorder::openDevice( const char *device )
{
    int error = 0;
    if( (error = snd_pcm_open( &m_capture_handle , device , SND_PCM_STREAM_CAPTURE, 0)) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot open audio device: " << device << std::endl;
        error_stream << "PCM Error: " << snd_strerror( error );
        Logger::instance().error( error_stream.str() );
    }
    if( (error = snd_pcm_hw_params_malloc( &m_hw_params)) < 0 )
    {
        stringstream error_stream;
        error_stream << "Cannot allocate hardware parameter structure " << std::endl;
        error_stream << "PCM Error: " << snd_strerror( error );
        Logger::instance().error( error_stream.str() );
    }
    if( (error = snd_pcm_hw_params_any ( m_capture_handle , m_hw_params)) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot initialize hardware parameter structure: "<< std::endl;
        error_stream << "PCM Error: " << snd_strerror(error );
        Logger::instance().error( error_stream.str() );
    }
    if ((error = snd_pcm_hw_params_set_access (m_capture_handle, m_hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot set access type : " << SND_PCM_ACCESS_RW_INTERLEAVED << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error );
        Logger::instance().error( error_stream.str() );
    }
    if( (error = snd_pcm_hw_params_set_format (m_capture_handle, m_hw_params, SND_PCM_FORMAT_S16_LE )) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot set sample format: " << m_pcm_format << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error );
        Logger::instance().error( error_stream.str() );
    }
    if( (error = snd_pcm_hw_params_set_rate_near (m_capture_handle, m_hw_params, &m_rate, 0)) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot set sample rate: " << m_rate << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error );
        Logger::instance().error( error_stream.str() );
    }
    if ((error = snd_pcm_hw_params_set_channels (m_capture_handle, m_hw_params, m_channels )) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot set channels: " << m_channels << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error );
        Logger::instance().error( error_stream.str() );
    }

    /* Set period size to 1024 frames. */
    snd_pcm_uframes_t frames = 1024;
    int dir;
    snd_pcm_hw_params_set_period_size_near( m_capture_handle, m_hw_params, &frames, &dir);
    if ((error = snd_pcm_hw_params (m_capture_handle, m_hw_params)) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot set hw_params: " << std::endl;
        error_stream << "PCM Error: " << snd_strerror( error );
        Logger::instance().error( error_stream.str() );
    }
    snd_pcm_hw_params_free (m_hw_params);

    if ((error = snd_pcm_prepare (m_capture_handle)) < 0) {

        stringstream error_stream;
        error_stream << "Cannot prepare audio interface for use: " << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error );
        Logger::instance().error( error_stream.str() );
    }

    Logger::instance().debug("recorder","device is now ready");
}

void Recorder::closeDevice(void)
{
    snd_pcm_drain(m_capture_handle);
    snd_pcm_close(m_capture_handle);

    Logger::instance().debug("recorder","device is closed");
}


