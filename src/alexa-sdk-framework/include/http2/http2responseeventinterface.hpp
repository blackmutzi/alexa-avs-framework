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
#ifndef HTTP2RESPONSEEVENTINTERFACE_H
#define HTTP2RESPONSEEVENTINTERFACE_H

#include "include/stdafx.hpp"

namespace http2
{
    class HTTP2ResponseEventInterface
    {
        public:
            HTTP2ResponseEventInterface() = default;
            virtual ~HTTP2ResponseEventInterface() = default;

            virtual void onResponseHeaderEvent( const void * name , size_t name_size , const void * value , size_t value_size , int32_t stream_id )=0;
            virtual void onResponseEvent( void * content , size_t size , int32_t stream_id ) =0;
            virtual void onResponseHeaderBeginEvent( int32_t stream_id ) =0;
            virtual void onResponseHeaderEndEvent( int32_t stream_id ) =0;
    };
}

#endif // HTTP2RESPONSEEVENTINTERFACE_H
