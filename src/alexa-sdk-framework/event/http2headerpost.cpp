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
#include "include/event/http2headerpost.hpp"

using namespace AlexaEvent;

HTTP2HeaderPost::HTTP2HeaderPost()
    : HTTP2HeaderBuilder( HTTP2HeaderFlag::FLAG_WITH_CONTENT_TYPE ) ,
      m_access_token( nullptr ) ,
      m_endpoint( nullptr ) ,
      m_boundary( nullptr )
{}

HTTP2HeaderPost::~HTTP2HeaderPost()
{
    delete m_access_token;
    delete m_endpoint;
    delete m_boundary;
}

void HTTP2HeaderPost::setAccessToken( const char * access_token )
{
    size_t b    = strlen("Bearer ");
    size_t size = b + strlen( access_token );
    char * bearer_token = new char[ size + 1];
    memset( bearer_token , 0 , size + 1);

    stringstream build_authorization;
    build_authorization << "Bearer " << access_token ;
    strncpy( bearer_token , build_authorization.str().c_str() , size );

    m_access_token = bearer_token;
}

void HTTP2HeaderPost::setEndpoint( const char * end_point)
{
    size_t size = strlen( end_point );
    char * lendpoint = new char[ size + 1];
    memset( lendpoint , 0 , size + 1 );
    strncpy( lendpoint , end_point , size );

    m_endpoint = lendpoint;
}

void HTTP2HeaderPost::setBoundary( const char * boundary)
{
    size_t b = strlen("multipart/form-data; boundary=");
    size_t size = b + strlen( boundary );

    char * content_type = new char[ size + 1 ];
    memset( content_type , 0 , size + 1 );

    stringstream build_content_type;
    build_content_type << "multipart/form-data;" << " boundary=" << boundary;
    strncpy( content_type , build_content_type.str().c_str() , size );

    m_boundary = content_type;
}

TransportHeaderInfo * HTTP2HeaderPost::buildTransportHeaderInfo(void)
{
    setMethode("POST");
    setSheme("https");
    setPath( m_endpoint );
    setAuthorization( m_access_token );
    setContentType( m_boundary );

    return HTTP2HeaderBuilder::buildTransportHeaderInfo();
}
