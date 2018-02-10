#include "server/client.hpp"

using namespace Server;

Client::Client()
    : m_socket( 0 ) ,
      m_name("unknown") ,
      m_buffer( nullptr ) ,
      m_buffer_size(0)
{}

Client::~Client()
{
    if( m_buffer != nullptr )
            delete[] m_buffer;
}

void Client::setSocket(int socket)
{
    m_socket = socket;
}

void Client::setName(string name)
{
    m_name = name;
}

void Client::setBuffer(char *buffer)
{
    m_buffer = buffer;
}

void Client::setBufferSize(size_t size)
{
    m_buffer_size = size;
}

char * Client::getBuffer(void) const
{
    return m_buffer;
}

size_t Client::getBufferSize(void) const
{
    return m_buffer_size;
}

int Client::getSocket(void) const
{
    return m_socket;
}

std::string Client::getName(void) const
{
    return m_name;
}
