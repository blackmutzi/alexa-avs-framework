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

#ifndef HTTP2RESPONSE_H
#define HTTP2RESPONSE_H

#include "stdafx.hpp"
#include "http2/http2data.hpp"

namespace http2
{

    class HTTP2Response : public HTTP2Data
    {
        public:
            HTTP2Response() = default;
            ~HTTP2Response() = default;

            void setStreamId( int32_t streamid );
            int32_t getStreamId(void);

        private:

            int32_t m_stream_id;
    };

    using SharedResponse = boost::shared_ptr< HTTP2Response >;
}

#endif // HTTP2RESPONSE_H
