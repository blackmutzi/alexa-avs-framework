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
#ifndef HTTP2RESPONSEANALYSE_HPP
#define HTTP2RESPONSEANALYSE_HPP

#include "include/stdafx.hpp"
#include "include/http2/http2response.hpp"
#include "include/directive/directiveiterator.hpp"
#include "include/event/transportinfo.hpp"
#include "include/directive/directive.hpp"
#include "include/http2/http2headerinfo.hpp"
#include "include/utils/logger.hpp"

using namespace directive;
using namespace AlexaEvent;
using namespace AVS;

namespace http2
{
    class HTTP2ResponseAnalyse
    {
        public:
            HTTP2ResponseAnalyse();
            ~HTTP2ResponseAnalyse() = default;

            void setResponseHeaderInfo( SharedHeaderInfo info );
            void setResponseContentData( HTTP2Response * response );

            void collectInfo(void);

            SharedHeaderInfo getHeaderInfo(void);
            DirectiveIterator * getResult(void);
            void cleanUp( DirectiveIterator * iterator );

        protected:

            size_t nextEntryPoint( char * content , size_t offset , char delim );
            std::vector< size_t > getEntryPositions( char * content , size_t size , unsigned int amount , std::string needle , unsigned int * real_amount );
            size_t search( char * content , size_t offset , size_t size , std::string needle );

        private:

            SharedHeaderInfo m_response_header_info;
            HTTP2Response * m_response;
            TransportInfo * m_directive_bytes;
            TransportInfo * m_audio_bytes;
            TransportInfo * m_audio_content_id;
            size_t m_directive_allocate_count;
            size_t m_audio_allocate_count;
    };
    using SharedResponseAnalyse = boost::shared_ptr< HTTP2ResponseAnalyse >;
}

#endif // HTTP2RESPONSEANALYSE_HPP
