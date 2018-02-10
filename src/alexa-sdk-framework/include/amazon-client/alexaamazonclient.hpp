#ifndef ALEXAAMAZONCLIENT_HPP
#define ALEXAAMAZONCLIENT_HPP

#include "stdafx.hpp"
#include "amazon-client/controller.hpp"
#include "auth/authenticator.hpp"

using namespace Auth;

namespace AVS
{
    class AlexaAmazonClient
    {
        public:
            AlexaAmazonClient( int argc , char * argv[] );
            ~AlexaAmazonClient();

            void setConfigFile( std::string config_file );
            void connect(void);
            void disconnect(void);

            Controller * getClientController(void);

        private:

            int m_argc;
            char ** m_argv;
            Controller * m_controller;
            std::string m_config_file;
            bool m_connect_status;
    };
}

#endif // ALEXAAMAZONCLIENT_HPP
