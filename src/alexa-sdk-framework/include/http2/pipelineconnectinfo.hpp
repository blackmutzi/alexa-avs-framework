#ifndef PIPELINECONNECTINFO_HPP
#define PIPELINECONNECTINFO_HPP

#include "stdafx.hpp"
#include "http2/http2transportdata.hpp"

namespace http2
{
    class PipelineConnectInfo
    {
        public:
            PipelineConnectInfo() = default;
            ~PipelineConnectInfo() = default;

            void setHost( const char * host );
            void setPort( long port );
            void setTransportData( HTTP2TransportData * data );
            void setConnectionLoop( bool status );
            void setResponseTimer( long seconds );

            const char * p_host;
            long p_port;
            HTTP2TransportData * p_data;
            long p_response_timer;
            bool p_connection_loop;

    };
}

#endif // PIPELINECONNECTINFO_HPP
