#include "server/alexaserver.hpp"

using namespace Server;

AlexaServer::AlexaServer(){}
AlexaServer::~AlexaServer(){}

void AlexaServer::setTransportDataManager( TransportDataManager *manager)
{
    m_transport_data_manager = manager;
}

void AlexaServer::onClientConnectEvent(Client *client)
{
    client->setName( makeClientName() );
}

void AlexaServer::onClientDisconnectEvent(Client *client)
{
    if( client->getBuffer() != nullptr || client->getBufferSize() != 0 )
            delete[] client->getBuffer();

    client->setActivity( false );
    client->setBuffer( nullptr );
    client->setBufferSize(0);
    client->setContentSize(0);
}

void AlexaServer::onReceiveEvent(Client *client, char *data, size_t size)
{
    if( !client->isActive() )
    {
        if( size >= 512 )
        {
            /* capture 512 bytes header data */
            client->setContentSize( client->processingMagicHeader( data ) );
            client->setActivity( true );

        } else {

            char * signal      = client->getStringFromEnum( Client::SIG_DISCONNECT );
            size_t signal_size = client->getSizeFromEnum( Client::SIG_DISCONNECT );
            sendToClient( client->getSocket() , signal , signal_size );
        }

    } else {

        if( client->getBuffer() == nullptr )
        {
            char * buffer = new char[ client->getContentSize() + 1 ];
            memset( buffer , 0 , client->getContentSize() + 1 );
            memcpy( buffer , data , size );

            client->setBuffer( buffer );
            client->setBufferSize( size );

        } else {

            char * buffer = client->getBuffer();
            memcpy( buffer + client->getBufferSize() , data , size );
            client->setBuffer( buffer );
            client->setBufferSize( client->getBufferSize() + size );

            if( client->getBufferSize() == client->getContentSize() )
            {
                client->setActivity( false );
                onBufferedFinishEvent( client );
            }

        }
    }
}

void AlexaServer::onBufferedFinishEvent( Client * client )
{
    TransportInfo * info = m_transport_data_manager->createTransportData( client->getBuffer() , client->getBufferSize() );

    delete[] client->getBuffer();
    client->setBuffer( nullptr );
    client->setBufferSize(0);
    client->setContentSize(0);

    m_transport_data_manager->createTransportDataEvent( info );
}



