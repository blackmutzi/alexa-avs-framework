#include "include/server/serverinterface.hpp"

using namespace Server;

ServerInterface::ServerInterface(){}
ServerInterface::~ServerInterface(){}

void ServerInterface::initialize(int port) throw( std::exception )
{
    struct sockaddr_in serv_addr;
    int opt = TRUE;
    int max_clients = 5;
    int activity,  valread , sd , max_sd , new_socket ;
    Client * clients = nullptr;
    char buffer[1025];

    //set of socket descriptors
    fd_set readfds;

    m_srv_port   = port;
    m_srv_socket = socket( AF_INET , SOCK_STREAM , 0);

    if( m_srv_socket < 0 )
            Logger::instance().exception("exception opening socket");

    //set master socket to allow multiple connections , this is just a good habit, it will work without this
    if( setsockopt( m_srv_socket , SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
            Logger::instance().exception("exception setsockopt");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( (uint16_t) m_srv_port );

    if (bind( m_srv_socket , (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
            Logger::instance().exception("exception on binding socket");

    //initialise clients
    clients = new Client[ max_clients ];
    listen( m_srv_socket , max_clients );

    while(true)
    {
            //clear the socket set
            FD_ZERO(&readfds);

            //add master socket to set
            FD_SET( m_srv_socket , &readfds);
            max_sd = m_srv_socket;

            //add child sockets to set
            for (int  i = 0 ; i < max_clients ; i++)
            {
                //socket descriptor
                sd = clients[i].getSocket();

                //if valid socket descriptor then add to read list
                if(sd > 0)
                    FD_SET( sd , &readfds );

                //highest file descriptor number, need it for the select function
                if(sd > max_sd)
                    max_sd = sd;
            }

            //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
            activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

            //If something happened on the master socket , then its an incoming connection
            if (FD_ISSET( m_srv_socket , &readfds))
            {
                if ((new_socket = accept( m_srv_socket , (struct sockaddr *)&serv_addr, (socklen_t*) sizeof(serv_addr) ))<0)
                            Logger::instance().exception("accept error ");

                //add new socket to array of sockets
                for (int i = 0; i < max_clients; i++)
                {
                    //if position is empty
                    if( clients[i].getSocket() == 0 )
                    {
                        clients[i].setSocket( new_socket );
                        Logger::instance().info("Add new Client");
                        onClientConnectEvent( &clients[i] );
                        break;
                    }
                }
            }

            //else its some IO operation on some other socket :)
            for (int i = 0; i < max_clients; i++)
            {
                    sd = clients[ i ].getSocket();

                    if (FD_ISSET( sd , &readfds))
                    {
                        //Check if it was for closing , and also read the incoming message
                        if ((valread = read( sd , buffer , 1024)) == 0)
                        {
                            Logger::instance().info("a Client is Disconected");
                            close( sd );
                            clients[ i ].setSocket( 0 );
                            onClientDisconnectEvent( &clients[ i ] );
                        }
                        else
                        {
                            buffer[valread] = '\0';
                            onReceiveEvent( &clients[i] , &buffer[0] , valread );
                        }
                    }
            }
     }
}

int ServerInterface::getSrvSocket(void)
{
    return m_srv_socket;
}

int ServerInterface::getSrvPort(void)
{
    return m_srv_port;
}

std::string ServerInterface::makeClientName(void)
{
    boost::uuids::uuid message_id_uuid = boost::uuids::uuid( boost::uuids::random_generator()() );
    return boost::lexical_cast<std::string>( message_id_uuid );
}

void ServerInterface::sendToClient(int socket, const char *data, size_t size)
{
    send( socket , data , size , 0 );
}

void ServerInterface::sendToClient(int socket, TransportInfo *data)
{
    sendToClient( socket , data->get() , data->getSize() );
}
