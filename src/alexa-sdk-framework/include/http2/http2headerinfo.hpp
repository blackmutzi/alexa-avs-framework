#ifndef HTTP2HEADERINFO_HPP
#define HTTP2HEADERINFO_HPP

#include "include/stdafx.hpp"
#include "include/nlohmann_json.hpp"

namespace http2
{
    using json = nlohmann::json;
    class HTTP2HeaderInfo
    {
        public:
            HTTP2HeaderInfo();
            ~HTTP2HeaderInfo()= default;

            void setStreamId( int32_t stream_id );
            void setActivedState( bool status );
            void addHeaderLine( const char * name , const char * value );

            bool isActive(void);
            int32_t getStreamId(void);
            json getHeaderData(void);

        private:

            bool m_status;
            int32_t m_stream_id;
            json m_header;
    };
    using SharedHeaderInfo = boost::shared_ptr< HTTP2HeaderInfo >;
}

#endif // HTTP2HEADERINFO_HPP
