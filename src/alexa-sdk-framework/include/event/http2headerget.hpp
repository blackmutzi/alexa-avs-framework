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
#ifndef HTTPHEADERGET_HPP
#define HTTPHEADERGET_HPP

#include "event/http2headerbuilder.hpp"

namespace AlexaEvent
{
    class HTTP2HeaderGet : public HTTP2HeaderBuilder
    {
        public:
            HTTP2HeaderGet();
            ~HTTP2HeaderGet();

            void setAccessToken( const char * access_token );
            void setEndpoint( const char * endpoint );

            TransportHeaderInfo * buildTransportHeaderInfo(void) override final;

        private:

            char * m_access_token;
            char * m_endpoint;
    };
}

#endif // HTTPHEADERGET_HPP
