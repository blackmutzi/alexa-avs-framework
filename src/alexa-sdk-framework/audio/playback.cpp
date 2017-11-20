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
#include "include/audio/playback.hpp"

using namespace AVS;

void PcmInfo::setSampleRate(unsigned int rate)
{
    p_sample_rate = rate;
}

void PcmInfo::setBitrate(unsigned int bitrate)
{
    p_bitrate = bitrate;
}

void PcmInfo::setChannels(unsigned int channels)
{
    p_channels = channels;
}

void PcmInfo::setPCMBuffer(char * buffer)
{
    p_pcm_buffer = buffer;
}

void PcmInfo::setPCMFrames(unsigned int frames)
{
    p_frames;
}

unsigned int PcmInfo::getBitsperSample(void)
{
    return p_bitrate / ( p_sample_rate * p_channels );
}

Playback::Playback()
    : m_device("default") ,
      m_audio_info( nullptr )
{}

void Playback::setDevice(char *device)
{
    m_device = device;
}

void Playback::setAudioInfo(TransportInfo *audio_info)
{
    m_audio_info;
}

void Playback::playNow(void)
{
    PcmInfo * pcm_info = createPcmInfo( m_audio_info );
    onPlaySound( pcm_info );

    free( pcm_info->p_pcm_buffer );
    delete pcm_info;
}

PcmInfo * Playback::createPcmInfo(TransportInfo *audio_info)
{
    PcmInfo * pcm_info = new PcmInfo();

    int num_samples = 0;
    int current_samples = 0;
    int sample_rate = 0;
    int bitrate     = 0;
    int totalframes = 0;
    int framenum    = 0;
    int framesize   = 0;
    int channels    = 0;
    int samplecount = 0;
    int bits_per_sample = 0;
    size_t read_bytes = 128;
    size_t offset   = 0;
    size_t pcm_buffer_size = 0;
    bool header_parse = false;
    const int PCM_SIZE = 8192;
    char pcm_buffer_l[ PCM_SIZE * sizeof(short int) ];
    char pcm_buffer_r[ PCM_SIZE * sizeof(short int) ];
    char * pcm_buffer;

    // create lame handler
    m_lame_handler = lame_init();
    m_hip_handler  = hip_decode_init();
    m_mp3_data     = new mp3data_struct();

    // set lame parameter
    lame_set_decode_only( m_lame_handler , 1);

    // init lame parameters
    lame_init_params( m_lame_handler );

    num_samples = hip_decode1_headers( m_hip_handler , (unsigned char * ) audio_info->get() , audio_info->getSize() , nullptr , nullptr , m_mp3_data );
    while( read_bytes < audio_info->getSize() )
    {
            if( m_mp3_data->header_parsed == 1 && !header_parse )
            {
                    // collect MP3 Header Infos

                    sample_rate = m_mp3_data->samplerate;
                    bitrate     = m_mp3_data->bitrate * 1000 ;
                    totalframes = m_mp3_data->totalframes;
                    framenum    = m_mp3_data->framenum;
                    framesize   = m_mp3_data->framesize;
                    channels    = m_mp3_data->stereo;


                    bits_per_sample = bitrate / ( sample_rate * channels );
                    pcm_buffer_size = num_samples * bits_per_sample ;
                    pcm_buffer = (char*) malloc( sizeof( char )  * pcm_buffer_size );
                    memset( pcm_buffer , 0 , pcm_buffer_size );
                    header_parse = true;
           }

            current_samples = hip_decode1( m_hip_handler , (unsigned char *) audio_info->get() , read_bytes , reinterpret_cast<short int*>( &pcm_buffer_l[0] ) , reinterpret_cast<short int*>( &pcm_buffer_r[0] ));
            num_samples += current_samples;

            if( current_samples == 0 )
                    break;

            memcpy( pcm_buffer + offset , &pcm_buffer_l[0] , current_samples * bits_per_sample );
            offset += current_samples * bits_per_sample ;
            pcm_buffer = (char*) realloc( pcm_buffer , sizeof( char) * ( offset * 2 ) );
            read_bytes += 128;
    }

    // set pcm info
    pcm_info->setSampleRate( sample_rate );
    pcm_info->setBitrate( bitrate );
    pcm_info->setChannels( channels );
    pcm_info->setPCMBuffer( pcm_buffer );
    pcm_info->setPCMFrames( num_samples );

    // close lame handler
    delete m_mp3_data;
    lame_close( m_lame_handler );
    hip_decode_exit( m_hip_handler );

    return pcm_info;
}

void Playback::onPlaySound(PcmInfo *info)
{
    m_sample_rate = info->p_sample_rate;
    m_pcm_format  = SND_PCM_FORMAT_S16_LE;
    m_channels    = info->p_channels;

    char * audio_bytes              = info->p_pcm_buffer;
    snd_pcm_uframes_t  audio_frames = info->p_frames;
    unsigned int bits_per_sample    = info->getBitsperSample();

    int error = 0 , rc = 0 , loop_count = 0;
    unsigned int frame_rythmus   = 576;
    unsigned int pcm_buffer_size = frame_rythmus * bits_per_sample ;
    unsigned int offset          = 0;

    onOpenDevice( m_device );

    try{

        for( snd_pcm_uframes_t frames = frame_rythmus ; frames <= audio_frames; frames += frame_rythmus )
        {
            offset = pcm_buffer_size * loop_count;
            rc = snd_pcm_writei(m_playback_handle, audio_bytes + offset , frame_rythmus );

            if( rc == -EPIPE )
            {
                if ((error = snd_pcm_prepare(m_playback_handle) ) < 0)
                {
                    stringstream exception;
                    exception << "prepare capture handle error: " << snd_strerror( error );
                    Logger::instance().exception( exception.str() );
                }

            }else if( rc < 0 )
            {
                stringstream exception;
                exception << "write to device failed: " << snd_strerror( rc );
                Logger::instance().exception( exception.str() );
            }

            loop_count += 1;
        }

    }catch( std::exception e )
    {
        // any exception here ..
    }

    onCloseDevice();
}

void Playback::onOpenDevice(char *device)
{
    int error = 0;
    if( (error = snd_pcm_open( &m_playback_handle , device , SND_PCM_STREAM_PLAYBACK , 0)) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot open audio device: " << device << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error);
        Logger::instance().error( error_stream.str() );
    }
    if( (error = snd_pcm_hw_params_malloc( &m_hw_params)) < 0 )
    {
        stringstream error_stream;
        error_stream << "Cannot allocate hardware parameter structure " << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error);
        Logger::instance().error( error_stream.str() );
    }
    if( (error = snd_pcm_hw_params_any ( m_playback_handle , m_hw_params)) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot initialize hardware parameter structure: "<< std::endl;
        error_stream << "PCM Error: " << snd_strerror(error);
        Logger::instance().error( error_stream.str() );
    }
    if ((error = snd_pcm_hw_params_set_access ( m_playback_handle , m_hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot set access type : " << SND_PCM_ACCESS_RW_INTERLEAVED << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error);
        Logger::instance().error( error_stream.str() );
    }
    if( (error = snd_pcm_hw_params_set_format ( m_playback_handle , m_hw_params, m_pcm_format)) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot set sample format: " << m_pcm_format << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error);
        Logger::instance().error( error_stream.str() );
    }
    if( (error = snd_pcm_hw_params_set_rate_near ( m_playback_handle , m_hw_params, &m_sample_rate, 0)) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot set sample rate: " << m_sample_rate << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error);
        Logger::instance().error( error_stream.str() );
    }
    if ((error = snd_pcm_hw_params_set_channels ( m_playback_handle , m_hw_params, m_channels )) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot set channels: " << m_channels << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error);
        Logger::instance().error( error_stream.str() );
    }

    /* Set period size to 1024 frames. */
    snd_pcm_uframes_t frames = 1024;
    int dir;
    snd_pcm_hw_params_set_period_size_near( m_playback_handle , m_hw_params, &frames, &dir);
    if ((error = snd_pcm_hw_params ( m_playback_handle , m_hw_params)) < 0)
    {
        stringstream error_stream;
        error_stream << "Cannot set hw_params: " << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error);
        Logger::instance().error( error_stream.str() );
    }
    snd_pcm_hw_params_free (m_hw_params);

    if ((error = snd_pcm_prepare (m_playback_handle )) < 0) {

        stringstream error_stream;
        error_stream << "Cannot prepare audio interface for use: " << std::endl;
        error_stream << "PCM Error: " << snd_strerror(error);
        Logger::instance().error( error_stream.str() );
    }

    Logger::instance().debug("playback","device is now ready");
}

void Playback::onCloseDevice(void)
{
    snd_pcm_drain(m_playback_handle);
    snd_pcm_close(m_playback_handle);

    Logger::instance().debug("playback","device is closed");
}
