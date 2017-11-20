#include "include/http2/http2headerinfo.hpp"

using namespace http2;

HTTP2HeaderInfo::HTTP2HeaderInfo()
    : m_status( false ) ,
      m_stream_id(0)
{}

void HTTP2HeaderInfo::setStreamId(int32_t stream_id)
{
    m_stream_id = stream_id;
}

void HTTP2HeaderInfo::setActivedState(bool status)
{
    m_status = status;
}

void HTTP2HeaderInfo::addHeaderLine(const char *name, const char *value )
{
    m_header[ name ] = value;
}

bool HTTP2HeaderInfo::isActive(void)
{
    return m_status;
}

int32_t HTTP2HeaderInfo::getStreamId(void)
{
    return m_stream_id;
}

json HTTP2HeaderInfo::getHeaderData(void)
{
    return m_header;
}
