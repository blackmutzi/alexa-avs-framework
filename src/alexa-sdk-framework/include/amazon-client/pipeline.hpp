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
#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include "include/stdafx.hpp"
#include "include/http2/http2pipeline.hpp"
#include "include/directive/directiveobserver.hpp"
#include "include/http2/http2responseanalyse.hpp"
#include "include/utils/logger.hpp"

using namespace http2;
using namespace directive;

namespace AVS
{
    class Pipeline : public HTTP2Pipeline
    {
        public:
            Pipeline();
            ~Pipeline();

            DirectiveObserver * getDirectiveObserver(void);

            void connectToServer( const char * avs_server , HTTP2TransportData * downchannel_data  );

            void onResponseProcessingEvent(HTTP2Response *response_data) override final;
            void onResponseHeaderProcessingEvent( SharedHeaderInfo info ) override final;

            bool getResponseThreadStatus(void);

        protected:

            void setResponseThreadStatus( bool status );
            static void onStartResponseProcessingThread( Pipeline * pip );
            void response_processing(void);

        private:

            DirectiveObserver * m_directive_observer;
            bool m_response_thread_status;

            std::list< SharedResponseAnalyse > m_response_analyse_list;

    };
}

#endif // PIPELINE_H
