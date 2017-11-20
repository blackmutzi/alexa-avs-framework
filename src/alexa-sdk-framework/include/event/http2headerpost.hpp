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
#ifndef HTTP2HEADERPOST_HPP
#define HTTP2HEADERPOST_HPP

#include "include/event/http2headerbuilder.hpp"

namespace AlexaEvent
{
    class HTTP2HeaderPost : public HTTP2HeaderBuilder
    {
        public:
            HTTP2HeaderPost();
            ~HTTP2HeaderPost();

            void setAccessToken( const char * access_token );
            void setEndpoint( const char * endpoint );
            void setBoundary( const char * boundary );

            TransportHeaderInfo * buildTransportHeaderInfo() override final;

        private:

            char * m_access_token;
            char * m_endpoint;
            char * m_boundary;
    };
}

#endif // HTTP2HEADERPOST_HPP
