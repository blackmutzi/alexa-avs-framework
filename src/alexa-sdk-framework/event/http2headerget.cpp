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
#include "event/http2headerget.hpp"

using namespace AlexaEvent;

HTTP2HeaderGet::HTTP2HeaderGet()
    : HTTP2HeaderBuilder( HTTP2HeaderFlag::FLAG_WITHOUT_CONTENT_TYPE) ,
      m_access_token( nullptr ) ,
      m_endpoint( nullptr )
{}

HTTP2HeaderGet::~HTTP2HeaderGet()
{
     delete m_access_token;
     delete m_endpoint;
}

void HTTP2HeaderGet::setAccessToken( const char * access_token)
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

void HTTP2HeaderGet::setEndpoint( const char * endpoint )
{
    size_t size = strlen( endpoint );
    char * lendpoint = new char[ size + 1];
    memset( lendpoint , 0 , size + 1 );
    strncpy( lendpoint , endpoint , size );

    m_endpoint = lendpoint;
}

TransportHeaderInfo * HTTP2HeaderGet::buildTransportHeaderInfo(void)
{ 
    setMethode("GET");
    setSheme("https");
    setPath( m_endpoint );
    setAuthorization( m_access_token );

    return HTTP2HeaderBuilder::buildTransportHeaderInfo();
}
