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
#include "include/event/recognizestreamrequest.hpp"

using namespace AlexaEvent;

void RecognizeStreamRequest::setAccessToken( const char *access_token)
{
    m_access_token = (char*)access_token;
}

void RecognizeStreamRequest::setBoundary( const char *boundary)
{
    m_boundary = (char*)boundary;
}

void RecognizeStreamRequest::setRecognizeJson( TransportInfo * recognize_info )
{
    m_recognize_json = recognize_info;
}

void RecognizeStreamRequest::setAudioInfo( TransportInfo * audio_info )
{
    m_audio_info = audio_info;
}

http2::SharedTransportData RecognizeStreamRequest::buildTransportData(void)
{
    TransportMaker maker;
    http2::SharedTransportData data( new http2::HTTP2TransportData() );
    http2::HTTP2TransportData * transport_data = data.get();

    transport_data->setHTTP2Header ( maker.createHTTP2HeaderPostInfo( m_access_token , "/v20160207/events" , m_boundary ) );
    transport_data->setHTTP2Content( maker.createJsonObjectInfo( m_recognize_json , m_audio_info , m_boundary ) );

    return data;
}
