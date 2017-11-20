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
#ifndef HTTP2TRANSPORTQUEUE_H
#define HTTP2TRANSPORTQUEUE_H

#include "include/stdafx.hpp"
#include "include/http2/http2transportdata.hpp"
#include "include/http2/http2response.hpp"
#include "include/http2/http2pipelineinterface.hpp"


namespace http2
{
    using TransportQueue      =  std::queue< SharedTransportData >;
    using ResponseQueue       =  std::queue< SharedResponse >;
    using BoostTransportQueue =  boost::shared_ptr< TransportQueue >;
    using BoostResponseQueue  =  boost::shared_ptr< ResponseQueue  >;

    class HTTP2TransportQueue
    {
        public:
            HTTP2TransportQueue() = default;
            virtual ~HTTP2TransportQueue();

            void initialize(void);
            void cleanUp(void);

            bool queue_transport_processing( HTTP2PipelineInterface * pip );
            void queue_response_processsing( HTTP2PipelineInterface * pip );
            void push_transport( SharedTransportData transportdata );
            void push_response( SharedResponse response );
            void clear_transport_queue(void);
            void clear_response_queue(void);

        protected:

            BoostTransportQueue m_transport_queue;
            BoostResponseQueue m_response_queue;

        private:

            boost::mutex m_transport_mutex;
            boost::mutex m_response_mutex;
            boost::condition_variable m_transport_cv;
            boost::condition_variable m_response_cv;
    };

}

#endif // HTTP2TRANSPORTQUEUE_H
