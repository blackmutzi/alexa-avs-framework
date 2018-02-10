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
#ifndef EVENTSTREAMREQUEST_HPP
#define EVENTSTREAMREQUEST_HPP

#include "stdafx.hpp"
#include "event/transportdatainterface.hpp"
#include "event/jsonobject.hpp"
#include "event/http2headerpost.hpp"

namespace AlexaEvent
{
    /*!
     * \brief The EventStreamRequest class
     *  build a custom http2transportdata only with alexa-json-events
     */
    class EventStreamRequest : public TransportDataInterface
    {
        public:
            EventStreamRequest() = default;
            ~EventStreamRequest() = default;

            /*!
             * set a access token
             * \brief setAccessToken
             * \param access_token
             */
            void setAccessToken( const char * access_token );

            /*!
             * set a boundary
             * \brief setBoundary
             * \param boundary
             */
            void setBoundary( const char * boundary );

            /*!
             * set a transportinfo
             * \brief setCustomJsonTransportInfo
             * \param json_content @see EventModulManager
             */
            void setCustomJsonTransportInfo( TransportInfo * json_content );

            /*!
             * final, build the http2transportdata
             * \brief buildTransportData
             * \return HTTP2TransportData instance
             */
            http2::SharedTransportData buildTransportData(void);

        private:

            const char * m_access_token;
            const char * m_boundary;
            TransportInfo * m_custom_json_info;
    };
}

#endif // EVENTSTREAMREQUEST_HPP

