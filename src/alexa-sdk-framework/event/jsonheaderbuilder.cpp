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
#include "event/jsonheaderbuilder.hpp"

using namespace AlexaEvent;

JsonHeaderBuilder::JsonHeaderBuilder(JsonHeaderFlag flag)
    : TransportBuilderInterface() , m_flag( flag )
{}

void JsonHeaderBuilder::setBoundary( const char * boundary)
{
    m_boundary = (char*)boundary;
}

TransportInfo * JsonHeaderBuilder::buildTransportInfo(void)
{
    TransportInfo * transport_info = new TransportInfo();
    size_t size = 0;
    stringstream info;
    info << "--" << m_boundary << std::endl;

    if( m_flag == JsonHeaderFlag::FLAG_JSON_HEADER )
    {
        info << "Content-Disposition: " << "form-data; name=\"metadata\"" << std::endl;
        info << "Content-Type: " << "application/json; charset=UTF-8" << std::endl;
    }

    if( m_flag == JsonHeaderFlag::FLAG_AUDIO_HEADER )
    {
        info << "Content-Disposition: " << "form-data; name=\"audio\"" << std::endl;
        info << "Content-Type: " << "application/octet-stream" << std::endl;
    }

    size = strlen( info.str().c_str() );
    transport_info->copy( info.str().c_str() , size );

    return transport_info;
}

TransportHeaderInfo * JsonHeaderBuilder::buildTransportHeaderInfo(void)
{
    return nullptr;
}
