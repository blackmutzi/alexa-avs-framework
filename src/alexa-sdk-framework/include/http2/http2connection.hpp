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
#ifndef HTTP2CONNECTION_H
#define HTTP2CONNECTION_H

#include "include/http2/http2response.hpp"
#include "include/http2/http2responseeventinterface.hpp"
#include "include/http2/http2transportdata.hpp"
#include "include/http2/pipelineconnectinfo.hpp"

namespace http2
{
    class HTTP2Connection : public HTTP2ResponseEventInterface
    {
        public:
            HTTP2Connection() = default;
            virtual ~ HTTP2Connection() = default;

            virtual void connect( PipelineConnectInfo * info ) = 0;
            virtual void connectionLoop( void ) = 0;
            virtual void disconnect(void) = 0;

        protected:

            HTTP2Response * m_http2_response;
    };
}

#endif // HTTP2CONNECTION_H
