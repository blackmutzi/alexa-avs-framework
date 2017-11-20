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
#ifndef HTTP2PIPELINEINTERFACE_HPP
#define HTTP2PIPELINEINTERFACE_HPP

#include "include/stdafx.hpp"
#include "include/http2/http2transportdata.hpp"
#include "include/http2/http2response.hpp"

namespace http2
{
    class HTTP2PipelineInterface
    {
        public:
            HTTP2PipelineInterface() = default;
            virtual ~HTTP2PipelineInterface() = default;

            virtual void setTransportData( HTTP2TransportData * transport_data) =0;
            virtual void performStream( void ) = 0;
            virtual void onResponseProcessingEvent( HTTP2Response * response ) = 0;
    };
}

#endif // HTTP2PIPELINEINTERFACE_HPP
