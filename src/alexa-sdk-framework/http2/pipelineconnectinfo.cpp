#include "include/http2/pipelineconnectinfo.hpp"

using namespace http2;


void PipelineConnectInfo::setHost(const char *host)
{
    p_host = host;
}

void PipelineConnectInfo::setPort(long port)
{
    p_port = port;
}

void PipelineConnectInfo::setTransportData(HTTP2TransportData *data)
{
    p_data = data;
}

void PipelineConnectInfo::setConnectionLoop(bool status)
{
    p_connection_loop = status;
}

void PipelineConnectInfo::setResponseTimer(long seconds)
{
    p_response_timer = seconds;
}
