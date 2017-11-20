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
#include "include/event/transportmaker.hpp"

using namespace AlexaEvent;

TransportInfo * TransportMaker::createTransportInfo( TransportBuilderInterface * maker )
{
    return maker->buildTransportInfo();
}

TransportInfo * TransportMaker::createJsonHeaderInfo( const char * boundary )
{
    JsonHeaderBuilder builder( JsonHeaderFlag::FLAG_JSON_HEADER );
    builder.setBoundary( boundary );
    return createTransportInfo( &builder );
}

TransportInfo * TransportMaker::createAudioHeaderInfo( const char * boundary )
{
    JsonHeaderBuilder builder( JsonHeaderFlag::FLAG_AUDIO_HEADER );
    builder.setBoundary( boundary );
    return createTransportInfo( &builder );
}

TransportInfo * TransportMaker::createJsonBodyContentFinished( TransportInfo * json_info , const char * boundary )
{
    JsonBodyBuilder builder( JsonBodyFlag::FLAG_CONTENT_FINISHED );
    builder.setBody( json_info );
    builder.setBoundary( createBoundaryInfo( boundary ) );

    return createTransportInfo( &builder );
}

TransportInfo * TransportMaker::createJsonBodyContentNotFinished( TransportInfo * json_info , const char * boundary )
{
    JsonBodyBuilder builder( JsonBodyFlag::FLAG_CONTENT_NOT_FINISHED );
    builder.setBody( json_info );
    builder.setBoundary( createBoundaryInfo( boundary ) );

    return createTransportInfo( &builder );
}

TransportInfo * TransportMaker::createJsonObjectInfo( TransportInfo * json_info , const char * boundary )
{
    TransportInfo * json_header = createJsonHeaderInfo( boundary );
    TransportInfo * json_body   = createJsonBodyContentFinished( json_info , boundary );

    JsonObject json_object (JsonObjectFlag::FLAG_JSON_CONTENT_ONLY );
    json_object.setJsonContent( json_object.merge( json_header , json_body ) );

    return createTransportInfo( &json_object );
}

TransportInfo * TransportMaker::createJsonObjectInfo( TransportInfo * json_info , TransportInfo * audio_info , const char *boundary )
{
    TransportInfo * json_header  = createJsonHeaderInfo( boundary );
    TransportInfo * json_body    = createJsonBodyContentNotFinished( json_info , boundary );
    TransportInfo * audio_header = createAudioHeaderInfo( boundary );
    TransportInfo * audio_body   = createJsonBodyContentFinished( audio_info , boundary );

    JsonObject json_object_with_audio_content(JsonObjectFlag::FLAG_JSON_CONTENT_WITH_AUDIO );
    json_object_with_audio_content.setJsonContent ( json_object_with_audio_content.merge( json_header , json_body  ) );
    json_object_with_audio_content.setAudioContent( json_object_with_audio_content.merge( audio_header, audio_body ) );

    return createTransportInfo( &json_object_with_audio_content );
}

TransportInfo * TransportMaker::createBoundaryInfo( const char * boundary )
{
    TransportInfo * transport_info = new TransportInfo();
    transport_info->copy( boundary , strlen( boundary ) );
    return transport_info;
}

TransportHeaderInfo * TransportMaker::createTransportHeaderInfo(TransportBuilderInterface *maker)
{
    return maker->buildTransportHeaderInfo();
}

TransportHeaderInfo * TransportMaker::createHTTP2HeaderGetInfo(const char *access_token, const char *endpoint)
{
    HTTP2HeaderGet http2_header_get;
    http2_header_get.setAccessToken( access_token );
    http2_header_get.setEndpoint( endpoint );

    return createTransportHeaderInfo( &http2_header_get );
}

TransportHeaderInfo * TransportMaker::createHTTP2HeaderPostInfo(const char *access_token, const char *endpoint, const char *boundary)
{
    HTTP2HeaderPost http2_header_post;
    http2_header_post.setAccessToken( access_token );
    http2_header_post.setEndpoint( endpoint );
    http2_header_post.setBoundary( boundary );

    return createTransportHeaderInfo( &http2_header_post );
}
