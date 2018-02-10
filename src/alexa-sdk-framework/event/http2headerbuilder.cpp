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
#include "event/http2headerbuilder.hpp"

using namespace AlexaEvent;

HTTP2HeaderBuilder::HTTP2HeaderBuilder(HTTP2HeaderFlag flag)
    : TransportBuilderInterface() , m_flag( flag )
{}

void HTTP2HeaderBuilder::setMethode( const char * methode)
{
    m_methode = (char*) methode;
}

void HTTP2HeaderBuilder::setSheme( const char * sheme)
{
    m_sheme = (char*) sheme;
}

void HTTP2HeaderBuilder::setPath( const char * path)
{
    m_path = (char*) path;
}

void HTTP2HeaderBuilder::setAuthorization( const char * auth)
{
    m_authorization = (char*) auth;
}

void HTTP2HeaderBuilder::setContentType( const char * content_type )
{
    m_content_type = (char*) content_type;
}

TransportInfo * HTTP2HeaderBuilder::buildTransportInfo(void)
{
    return nullptr;
}

TransportHeaderInfo * HTTP2HeaderBuilder::buildTransportHeaderInfo(void)
{
    TransportHeaderInfo * header_info = new TransportHeaderInfo();
    unsigned int head_count = 4;

    size_t methode_len = strlen( m_methode );
    char * methode = new char[ methode_len + 1];
    memset( methode , 0 , methode_len + 1 );
    memcpy( methode , m_methode , methode_len );

    size_t scheme_len = strlen( m_sheme );
    char * scheme = new char[ scheme_len + 1 ];
    memset( scheme , 0 , scheme_len + 1 );
    memcpy( scheme , m_sheme , scheme_len );

    size_t path_len = strlen( m_path );
    char * path = new char[ path_len + 1 ];
    memset( path , 0 , path_len + 1 );
    memcpy( path , m_path , path_len );

    size_t auth_len = strlen( m_authorization );
    char * auth = new char[ auth_len + 1 ];
    memset( auth , 0 , auth_len + 1);
    memcpy( auth , m_authorization , auth_len );

    size_t ct_len;
    char * ct;
    if( m_flag == HTTP2HeaderFlag::FLAG_WITH_CONTENT_TYPE )
    {
        ct_len = strlen( m_content_type );
        ct = new char[ ct_len + 1 ];
        memset( ct , 0 , ct_len + 1 );
        memcpy( ct , m_content_type , ct_len );
        head_count++;
    }

    nghttp2_nv * header = new nghttp2_nv[ head_count ];
    uint8_t flag = NGHTTP2_NV_FLAG_NONE;

    header[0].flags    = flag;
    header[0].name     = (uint8_t*) ":method";
    header[0].namelen  = 7;
    header[0].value    = (uint8_t*) methode;
    header[0].valuelen = methode_len;

    header[1].flags    = flag;
    header[1].name     = (uint8_t*) ":scheme";
    header[1].namelen  = 7;
    header[1].value    = (uint8_t*) scheme;
    header[1].valuelen = scheme_len;

    header[2].flags    = flag;
    header[2].name     = (uint8_t*) ":path";
    header[2].namelen  = 5;
    header[2].value    = (uint8_t*) path;
    header[2].valuelen = path_len;

    header[3].flags    = flag;
    header[3].name     = (uint8_t*) "authorization";
    header[3].namelen  = 13;
    header[3].value    = (uint8_t*) auth;
    header[3].valuelen = auth_len;

    if( m_flag == HTTP2HeaderFlag::FLAG_WITH_CONTENT_TYPE )
    {
        header[4].flags    = flag;
        header[4].name     = (uint8_t*) "content-type";
        header[4].namelen  = 12;
        header[4].value    = (uint8_t*) ct;
        header[4].valuelen = ct_len;
    }

    header_info->set( header );
    header_info->setSize( head_count );

    return header_info;
}


