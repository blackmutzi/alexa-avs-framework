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
#ifndef HTTP2TRANSPORTDATA_H
#define HTTP2TRANSPORTDATA_H

#include "include/stdafx.hpp"
#include "include/event/transportinfo.hpp"
#include "include/event/transportheaderinfo.hpp"

namespace http2
{
    /*!
     * \brief The HTTP2TransportData class
     * saved http2 header and content
     */
    class HTTP2TransportData
    {
        public:
            HTTP2TransportData();
            ~HTTP2TransportData();

            /*!
             * save http2 multipart header info
             * \brief setHTTP2Header
             * \param http2_multipart_header | @see TransportMaker class
             */
            void setHTTP2Header ( AlexaEvent::TransportHeaderInfo * http2_multipart_header );

            /*!
             * save http2 multipart json object info
             * \brief setHTTP2Content
             * \param http2_multipart_json_object | @see TransportMaker class
             */
            void setHTTP2Content( AlexaEvent::TransportInfo  * http2_multipart_json_object );

            /*!
             * return saved http2 multipart header info instance
             * \brief getHTTP2HeaderInfo
             * \return
             */
            AlexaEvent::TransportHeaderInfo * getHTTP2HeaderInfo(void);

            /*!
             * return saved http2 multipart json object info instance
             * \brief getHTTP2ContentInfo
             * \return
             */
            AlexaEvent::TransportInfo * getHTTP2ContentInfo(void);

            bool hasHeader(void);
            bool hasContent(void);

        private:

            AlexaEvent::TransportHeaderInfo * m_http2_header_info;
            AlexaEvent::TransportInfo * m_http2_content_info;

            bool m_has_header;
            bool m_has_content;

    };


    using SharedTransportData = boost::shared_ptr< HTTP2TransportData >;
}

#endif // HTTP2TRANSPORTDATA_H
