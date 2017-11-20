#ifndef CLIENTS_HPP
#define CLIENTS_HPP

#include "include/stdafx.hpp"
#include "include/server/transferstate.hpp"

namespace Server
{
    class Client : public TransferState
    {
        public:
            Client();
            ~Client();

            void setSocket( int socket );
            void setName( std::string name );
            void setBuffer( char * buffer );
            void setBufferSize( size_t size );

            int getSocket(void) const;
            std::string getName(void) const;
            char * getBuffer(void) const;
            size_t getBufferSize(void) const;

        private:

            int m_socket;
            std::string m_name;
            char * m_buffer;
            size_t m_buffer_size;
    };
}

#endif // CLIENTS_HPP
