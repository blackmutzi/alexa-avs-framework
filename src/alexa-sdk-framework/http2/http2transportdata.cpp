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
#include "include/http2/http2transportdata.hpp"

using namespace http2;

HTTP2TransportData::HTTP2TransportData()
    : m_http2_header_info( nullptr ) ,
      m_http2_content_info( nullptr ),
      m_has_header( false ) ,
      m_has_content( false )
{}

HTTP2TransportData::~HTTP2TransportData()
{
    if( hasHeader() )
            delete m_http2_header_info;

    if( hasContent() )
            delete m_http2_content_info;
}

void HTTP2TransportData::setHTTP2Content(AlexaEvent::TransportInfo * http2_header_info )
{
    m_http2_content_info = http2_header_info;
    m_has_content = true;
}

void HTTP2TransportData::setHTTP2Header(AlexaEvent::TransportHeaderInfo * http2_content_info )
{
    m_http2_header_info = http2_content_info;
    m_has_header = true;
}

AlexaEvent::TransportHeaderInfo * HTTP2TransportData::getHTTP2HeaderInfo(void)
{
    return m_http2_header_info;
}

AlexaEvent::TransportInfo * HTTP2TransportData::getHTTP2ContentInfo(void)
{
    return m_http2_content_info;
}

bool HTTP2TransportData::hasHeader(void)
{
    return m_has_header;
}

bool HTTP2TransportData::hasContent(void)
{
    return m_has_content;
}

