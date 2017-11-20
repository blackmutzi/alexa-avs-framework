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
#include "include/http2/http2responseanalyse.hpp"

using namespace http2;

HTTP2ResponseAnalyse::HTTP2ResponseAnalyse()
    : m_response( nullptr )
{}

void HTTP2ResponseAnalyse::setResponseHeaderInfo(SharedHeaderInfo info)
{
   m_response_header_info = info;
}

void HTTP2ResponseAnalyse::setResponseContentData(HTTP2Response *response)
{
    m_response = response;
}

SharedHeaderInfo HTTP2ResponseAnalyse::getHeaderInfo(void)
{
    return m_response_header_info;
}

void HTTP2ResponseAnalyse::collectInfo(void)
{
   char * content = (char*) m_response->get();
   size_t size    = m_response->getSize();
   Logger::instance().debug("Response-Content", content );

   std::vector< size_t > application_json_positions;
   std::vector< size_t > application_octet_positions;
   std::vector< size_t > content_id_positions;

   size_t directive_begin_pos  = 0;
   size_t directive_end_pos    = 0;
   size_t directive_size       = 0;
   size_t content_id_begin_pos = 0;
   size_t content_id_end_pos   = 0;
   size_t content_id_size      = 0;
   size_t boundary_size        = 0;
   size_t audio_begin_pos      = 0;
   size_t audio_end_pos        = 0;
   size_t audio_size           = 0;
   size_t app_json_len         = strlen("Content-Type: application/json; charset=UTF-8");
   size_t app_octet_len        = strlen("Content-Type: application/octet-stream");
   size_t content_id_len       = strlen("Content-ID: ");
   size_t MAX_DIRECTIVE_COUNT  = 200;
   size_t MAX_AUDIO_COUNT      = 1;

   unsigned int REAL_DIRECTIVE_COUNT   = 0;
   unsigned int REAL_AUDIO_COUNT       = 0;
   unsigned int REAL_CONTENT_ID_COUNT  = 0;

   m_directive_bytes    = nullptr;
   m_audio_bytes        = nullptr;
   m_audio_content_id   = nullptr;
   m_directive_allocate_count = 0;
   m_audio_allocate_count     = 0;

   // Get Positions from Content-Type: application/json; charset=UTF-8 Positions ( MAXIMUM: 2 )
   application_json_positions  = getEntryPositions( content , size , MAX_DIRECTIVE_COUNT , "Content-Type: application/json; charset=UTF-8" , &REAL_DIRECTIVE_COUNT );

   // Get positions from Content-Type: application/octet-stream ( MAXIMUM: 1 )
   application_octet_positions = getEntryPositions( content , size , MAX_AUDIO_COUNT , "Content-Type: application/octet-stream" , &REAL_AUDIO_COUNT );
   content_id_positions = getEntryPositions( content , size , MAX_AUDIO_COUNT , "Content-ID: ", &REAL_CONTENT_ID_COUNT );

   // if this true then no DIRECTIVE found in content
   if( REAL_DIRECTIVE_COUNT == 0 )
               return;

   // allocate array DIRECTIVE_BYTES
   m_directive_bytes = new TransportInfo[ REAL_DIRECTIVE_COUNT ];
   m_directive_allocate_count = REAL_DIRECTIVE_COUNT;

   for( unsigned int directive_loop = 0; directive_loop < REAL_DIRECTIVE_COUNT ; directive_loop++ )
   {
       // content_type_begin_pos + length_of_content_type_application_json + 4 bytes ( \r\n\r\n )
       directive_begin_pos = application_json_positions[ directive_loop ] + app_json_len  + 4;
       // search for next (\n) byte and get position
       directive_end_pos   = directive_begin_pos + nextEntryPoint( content , directive_begin_pos , '\n' );
       // now we have directive begin & end positions
       directive_size  = directive_end_pos - directive_begin_pos;
       // now we have directive_size

       // allocate directive bytes
       char * allocate_directive_bytes = new char[ directive_size ];
       memset( allocate_directive_bytes  , 0 , directive_size );
       memcpy( allocate_directive_bytes  , content + directive_begin_pos , directive_size );
       (&m_directive_bytes[ directive_loop ])->set( allocate_directive_bytes );
       (&m_directive_bytes[ directive_loop ])->setSize( directive_size );
   }

   // if this true then no BINARY AUDIO BYTES found in content
   if( REAL_AUDIO_COUNT == 0 )
           return;

   // GET ALL Boundary Positions ( no needed )
   // boundary_positions = getEntryPositions( content , size , MAX_BOUNDARY_COUNT , real_boundary , &REAL_BOUNDARY_COUNT );

   // allocate array AUDIO_BYTES
   m_audio_bytes = new TransportInfo[ REAL_AUDIO_COUNT ];
   m_audio_content_id = new TransportInfo[ REAL_AUDIO_COUNT ];
   m_audio_allocate_count = REAL_AUDIO_COUNT;

   for( unsigned int audio_loop = 0; audio_loop < REAL_AUDIO_COUNT; audio_loop++ )
   {
       content_id_begin_pos = content_id_positions[ audio_loop ] + content_id_len + 1;
       content_id_end_pos   = content_id_begin_pos + nextEntryPoint( content , content_id_begin_pos , '\n' ) - 2;
       content_id_size      = content_id_end_pos - content_id_begin_pos;

       // content_type_application_octet_begin_pos + length_of_content_type_application_octet + 4 bytes ( \r\n\r\n )
       audio_begin_pos  = application_octet_positions[ audio_loop ] + app_octet_len + 4;
       // audio_end_pos = next_boundary_position - 1 byte (\n)
       audio_end_pos    = size - (boundary_size + 2) - 1;
       // now we have binary_audio_size
       audio_size = audio_end_pos - audio_begin_pos;


       // allocate audio bytes
       char * allocate_audio_bytes = new char[ audio_size ];
       memset( allocate_audio_bytes , 0 , audio_size );
       memcpy( allocate_audio_bytes , content + audio_begin_pos , audio_size );
       (&m_audio_bytes[audio_loop])->set( allocate_audio_bytes );
       (&m_audio_bytes[audio_loop])->setSize( audio_size );


       //allocate content_id bytes
       char * allocate_content_id_bytes = new char[ content_id_size + 1 ];
       memset( allocate_content_id_bytes , 0 , content_id_size + 1);
       memcpy( allocate_content_id_bytes , content + content_id_begin_pos , content_id_size );
       (&m_audio_content_id[audio_loop])->set( allocate_content_id_bytes );
       (&m_audio_content_id[audio_loop])->setSize( content_id_size );
   }

   return;
}

DirectiveIterator * HTTP2ResponseAnalyse::getResult(void)
{
    DirectiveIterator * directives = new DirectiveIterator();
    Directive * current  = nullptr;
    DirectiveType * type = nullptr;

    for( unsigned int directive_count = 0; directive_count < m_directive_allocate_count; directive_count++ )
    {
        current = new Directive();
        TransportInfo * copy_directive_data = new TransportInfo( *(&m_directive_bytes[ directive_count ]) );
        current->setJsonInfo( copy_directive_data );

        try
        {

            json jsonobj = json::parse( copy_directive_data->get() );

            std::string directive_namespace = jsonobj["directive"]["header"]["namespace"];
            std::string directive_name = jsonobj["directive"]["header"]["name"];
			
            type = new DirectiveType();
            type->setToken( directive_namespace.c_str() );
            type->setValue( directive_name.c_str() );

            current->setDirectiveType( type );
            directives->push_back( current );

        } catch ( std::exception e )
        {
            stringstream debug;
            debug << "json object is corrupt";
            Logger::instance().debug( "HTTP2ResponseAnalyse::getResult", debug.str() );
        }
    }

    for( unsigned int audio_count = 0; audio_count < m_audio_allocate_count; audio_count++ )
    {
        TransportInfo * copy_audio_data = new TransportInfo( *(&m_audio_bytes[ audio_count ]) );

        const char * content_id_string = (&m_audio_content_id[audio_count])->get();
        stringstream content_stream;
        content_stream << "cid:" << content_id_string;

        for( Directive * dir : *directives )
        {
            try
            {

                json jsonobj;
                std::string url_id;

                try{

                    jsonobj = json::parse( dir->getJsonInfo()->get() );
                    url_id = jsonobj["directive"]["payload"]["url"];

                }catch( std::exception e )
                {
                    stringstream debug;
                    debug << "json object has no payload url";
                    Logger::instance().debug( "HTTP2ResponseAnalyse::getResult", debug.str() );
                    continue;
                }

                Logger::instance().debug("directive_url_id", url_id );
                Logger::instance().debug("audio_url_id", content_stream.str() );

                if( strcmp( content_stream.str().c_str() , url_id.c_str() ) == 0 )
                {
                    Logger::instance().debug("audio-data-set:", url_id );
                    dir->setAudioInfo( copy_audio_data );
                    break;
                }

            }catch( std::exception e )
            {
                stringstream debug;
                debug << "unknown error ";
                Logger::instance().debug( "HTTP2ResponseAnalyse::getResult", debug.str() );
            }

        }

    }

    if( m_directive_allocate_count != 0 )
    {
           delete[] m_directive_bytes;
           m_directive_bytes = nullptr;
           m_directive_allocate_count = 0;
    }

    if( m_audio_allocate_count != 0 )
    {
           delete[] m_audio_bytes;
           m_audio_bytes = nullptr;
           m_audio_allocate_count = 0;

           delete[] m_audio_content_id;
           m_audio_content_id = nullptr;
    }

    return directives;
}


void HTTP2ResponseAnalyse::cleanUp(DirectiveIterator * iterator )
{
    for( Directive * dir : *iterator )
    {
            delete dir->getJsonInfo();

            if( dir->hasAudioInfo() )
            {
                delete dir->getAudioInfo();
            }

            delete dir;
    }
}

size_t HTTP2ResponseAnalyse::nextEntryPoint(char *content, size_t offset, char delim)
{
    char * next = content + offset;
    size_t pos  = 0;

    for( next; next != NULL; next++ )
    {
        if( *next == delim )
               break;
        pos++;
    }
    return pos;
}

std::vector < size_t > HTTP2ResponseAnalyse::getEntryPositions(char *content, size_t size, unsigned int amount, string needle, unsigned int *real_amount)
{
    char * next = content;
    size_t pos  = 0;
    size_t real_number = 0;
    unsigned int while_counter = 0;
    std::vector< size_t > list_of_positions;

    while( while_counter < amount )
    {
        if( while_counter == 0 )
        {
           if( pos >= size )
                 break;

           pos = search( next , pos , size - pos , needle );

           if( pos == (unsigned long) -1 )
                  break;

           *real_amount += 1;
           list_of_positions.push_back( pos );
           while_counter++;
           continue;
        }

        // Offset
        pos = pos + strlen( needle.c_str() );

        if( pos >= size )
             break;

        // Next Search
        real_number = search( next , pos , size - pos , needle );
        pos += real_number;

        if( real_number == (unsigned long) -1 )
               break;

        *real_amount += 1;
        list_of_positions.push_back( pos );
        while_counter++;
    }

    return list_of_positions;
}

size_t HTTP2ResponseAnalyse::search(char *content, size_t offset, size_t size, string needle)
{
    std::string content_data;
    content_data.resize( size );
    size_t return_pos = 0;
    memcpy( (char*) content_data.data() , content + offset , size );
    return_pos = content_data.find( needle );
    return return_pos;
}
