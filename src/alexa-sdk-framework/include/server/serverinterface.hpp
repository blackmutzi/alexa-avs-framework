#ifndef SERVERINTERFACE_HPP
#define SERVERINTERFACE_HPP

#include "stdafx.hpp"
#include "event/transportinfo.hpp"
#include "utils/logger.hpp"
#include "server/client.hpp"

using namespace AlexaEvent;
using namespace AVS;

namespace Server
{
    class ServerInterface
    {
        public:
            ServerInterface();
            virtual ~ServerInterface();

            void initialize( int port ) throw( std::exception );

            void sendToClient( int socket , TransportInfo * data );
            void sendToClient(int socket , const char *data , size_t size );

            std::string makeClientName(void);

            virtual void onClientConnectEvent( Client * client )=0;
            virtual void onClientDisconnectEvent( Client * client )=0;
            virtual void onReceiveEvent( Client * client , char * data , size_t size )=0;

            int getSrvSocket(void);
            int getSrvPort(void);

        private:

            int m_srv_socket;
            int m_srv_port;

    };
}

#endif // SERVERINTERFACE_HPP
