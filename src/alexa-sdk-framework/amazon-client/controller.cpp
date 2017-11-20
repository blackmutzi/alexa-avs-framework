/*
   Copyright (C) 2017-2018 Stefan Masuch

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "include/amazon-client/controller.hpp"

using namespace AVS;

Controller::Controller()
	: m_access_token(nullptr) ,
	  m_boundary("-----abcde12345789") ,
	  m_avs_url("avs-alexa-eu.amazon.com") ,
      m_request_manager( nullptr ) ,
      m_directive_manager( nullptr ) ,
      m_pipeline( nullptr ) ,
	  m_avs_connection( false )  ,
	  m_close(false)
{}

bool Controller::isConnected(void)
{
	return m_avs_connection;
}

void Controller::setConnectStatus(bool status)
{
	m_avs_connection = status;
}

void Controller::setAccessToken( const char * access_token)
{
	size_t size = strlen( access_token );
	char * mem_access_token = new char[ size + 1 ];
	memset( mem_access_token , 0 , size + 1);
	strncpy( mem_access_token , access_token , size );

	if( m_access_token != nullptr ) {
		delete[] m_access_token;
	}
	m_access_token = mem_access_token;
}

void Controller::setBoundary( const char *boundary)
{
	m_boundary = boundary;
}

void Controller::setUrl(const char *avs_url)
{
	m_avs_url = avs_url;
}

const char * Controller::getAccessToken(void)
{
	return m_access_token;
}

const char * Controller::getBoundary(void)
{
	return m_boundary;
}

const char * Controller::getUrl(void)
{
	return m_avs_url;
}

Pipeline * Controller::getPipeline(void)
{
    return m_pipeline;
}

RequestManager * Controller::getRequestManager(void)
{
    return m_request_manager;
}

DirectiveManager * Controller::getDirectiveManager(void)
{
    return m_directive_manager;
}

void Controller::initialize(void)
{
    Console::initialize();

    m_pipeline          = new Pipeline();
    m_request_manager   = new RequestManager( m_access_token , m_boundary );
    m_directive_manager = new DirectiveManager();

    EventModulManager * event_manager = new EventModulManager();
    event_manager->initialize();

    m_request_manager->setAlexaPipeline( m_pipeline );
    m_request_manager->setEventModulManager( event_manager );
    m_directive_manager->setRequestManager( m_request_manager );

    m_directive_manager->initialize();
}

void Controller::cleanUp(void)
{
	delete m_pipeline;

    delete m_request_manager;

    delete m_directive_manager;
}

void Controller::close(void)
{
	m_close = true;
	m_pipeline->disconnect();
}

void Controller::onConsoleInputEvent(char *input)
{
    if( strcmp( input , "start") == 0)
    {
        Logger::instance().info("starting recognize request in 5 seconds ...");
        boost::this_thread::sleep(boost::posix_time::seconds(5));

        boost::uuids::uuid message_id_uuid = boost::uuids::uuid( boost::uuids::random_generator()() );
        m_request_manager->sendRecognizeRequest( boost::lexical_cast<std::string>( message_id_uuid ) );
    }
}


void Controller::ConnectToAlexaVoiceService(void)
{
    EventModulManager * event_manager = m_request_manager->getEventModulManager();

    //Start Pipeline Thread ...
	boost::thread pipeline_start_thread( &Controller::PipelineStartThread , this );

    while( !m_pipeline->isPipelineReady() ){}

	// Build SynchronizeStateEvent - Stream
	// and push to pipeline
    m_request_manager->sendRequest( event_manager->getSystemModul()->createSynchronizeStateEvent() );
	// Build Settings Update - Stream
	// and push to pipeline
    m_request_manager->sendRequest( event_manager->getSettingsModul()->createSettingsUpdateEvent("locale","de-DE") );
}

bool Controller::MainLoop(void)
{
	bool status = true;
	while(true) {
		boost::this_thread::sleep(boost::posix_time::seconds(10));

		if( !isConnected() ) {
			status = false; // get new access token
			break;
		}
	}

	if( m_close )
		status = true; // close Application

	cleanUp();
	return status;
}

void Controller::PipelineStartThread( Controller * controller )
{
	TransportMaker maker;
	HTTP2TransportData downchannel_data;
	downchannel_data.setHTTP2Header( maker.createHTTP2HeaderGetInfo( controller->getAccessToken() , "/v20160207/directives" ) );

	controller->setConnectStatus( true );
	controller->getPipeline()->connectToServer( controller->getUrl() , &downchannel_data );
	controller->setConnectStatus( false );
}
