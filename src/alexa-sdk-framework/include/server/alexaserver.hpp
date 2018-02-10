#ifndef ALEXASERVER_HPP
#define ALEXASERVER_HPP

#include "stdafx.hpp"
#include "server/serverinterface.hpp"
#include "server/transportdatamanager.hpp"

namespace Server
{
    class AlexaServer : public ServerInterface
    {
        public:
            AlexaServer();
            ~AlexaServer();

            void setTransportDataManager( TransportDataManager * manager );
            void onClientConnectEvent(Client *client);
            void onClientDisconnectEvent(Client *client);

            /*!
             * buffer incoming data from client
             * \brief onReceiveEvent
             * \param client
             * \param data
             * \param size
             */
            void onReceiveEvent(Client *client, char *data, size_t size);

            /*!
             * \brief onBufferedFinishEvent
             * \param client
             */
            void onBufferedFinishEvent( Client * client );

        private:

            TransportDataManager * m_transport_data_manager;

    };
}

#endif // ALEXASERVER_HPP
