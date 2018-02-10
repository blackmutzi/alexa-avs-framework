#include "server/transferstate.hpp"

using namespace Server;

TransferState::TransferState()
    : m_activity( false )
{}

TransferState::~TransferState(){}

void TransferState::setActivity(bool status)
{
    m_activity = status;
}

bool TransferState::isActive(void)
{
    return m_activity;
}

void TransferState::setContentSize(size_t size)
{
    m_content_size = size;
}

size_t TransferState::getContentSize(void)
{
    return m_content_size;
}

size_t TransferState::processingMagicHeader(char *data)
{
    return 0;
}

char * TransferState::getStringFromEnum(SIG signal)
{
    switch( signal )
    {
        case SIG_DISCONNECT:
                return "SIGNAL_DISCONNECT";
        break;
    }

    return nullptr;
}

size_t TransferState::getSizeFromEnum(SIG signal)
{
    switch( signal )
    {
        case SIG_DISCONNECT:
                return strlen( getStringFromEnum( SIG_DISCONNECT ) );
        break;
    }
    return 0;
}
