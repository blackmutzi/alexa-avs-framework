#include "amazon-client/alexaamazonclient.hpp"

using namespace AVS;

AlexaAmazonClient::AlexaAmazonClient( int argc , char * argv[] )
    : m_argc( argc ) , m_argv( argv ) , m_controller( new Controller() ) ,
      m_config_file("/etc/alexa/config.json") ,
      m_connect_status( true )

{}

AlexaAmazonClient::~AlexaAmazonClient()
{
    delete m_controller;
}

void AlexaAmazonClient::setConfigFile(string config_file)
{
    m_config_file = config_file;
}

void AlexaAmazonClient::connect(void)
{
    Logger::instance().verboseMode(true);
    Authenticator auth;
    AuthInfo auth_info;

    while( m_connect_status )
    {
        try{

            auth.createAuthInfo( &auth_info ,m_config_file );

            if( auth.validateAuthInfo( &auth_info ) )
            {
                m_controller->setAccessToken( auth.getAccessToken( &auth_info ).c_str() );

                m_controller->initialize();

                m_controller->ConnectToAlexaVoiceService();

                // if true then close application
                // if false then get new access_token
                if( m_controller->MainLoop() )
                            break;
            } else {

                Logger::instance().info("pause mode now ...");
                cin.get();
            }

        } catch ( std::exception e )
        {
           // getAccessToken Exception
           // jump to begin loop
        }
   }
}

void AlexaAmazonClient::disconnect(void)
{
    m_controller->close();
    m_connect_status = false;
}

Controller * AlexaAmazonClient::getClientController(void)
{
    return m_controller;
}
