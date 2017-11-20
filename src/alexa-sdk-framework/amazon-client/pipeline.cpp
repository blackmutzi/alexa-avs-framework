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
#include "include/amazon-client/pipeline.hpp"

using namespace AVS;

Pipeline::Pipeline()
    : HTTP2Pipeline() ,
      m_directive_observer( new DirectiveObserver() )
{}

Pipeline::~Pipeline()
{
    delete m_directive_observer;
}

DirectiveObserver * Pipeline::getDirectiveObserver(void)
{
    return m_directive_observer;
}

void Pipeline::connectToServer(const char *avs_server , HTTP2TransportData * downchannel_data )
{
    auto connect_info = std::unique_ptr< PipelineConnectInfo >( new PipelineConnectInfo() );
    PipelineConnectInfo * info = connect_info.get();

    info->setConnectionLoop( true );
    info->setHost( avs_server );
    info->setPort( 443 );
    info->setResponseTimer(4);
    info->setTransportData( downchannel_data );

    HTTP2Pipeline::initialize();

    setResponseThreadStatus( true );
    boost::thread response_processing_thread( &Pipeline::onStartResponseProcessingThread , this );

    HTTP2Pipeline::connect( info );
    setResponseThreadStatus( false );  // close response thread
    connect_info.reset();
}

void Pipeline::response_processing(void)
{
    HTTP2TransportQueue::queue_response_processsing( this );
}

void Pipeline::onStartResponseProcessingThread( Pipeline * pip )
{
    while( pip->getResponseThreadStatus() )
    {
        pip->response_processing();
        boost::this_thread::sleep(boost::posix_time::millisec(200));
    }
}

void Pipeline::onResponseProcessingEvent( HTTP2Response *response_data )
{
    Logger::instance().info("onResponseProcessingEvent started ...");

    for( SharedResponseAnalyse shared_analyse : m_response_analyse_list )
    {
        HTTP2ResponseAnalyse * analyse   = shared_analyse.get();
        SharedHeaderInfo shared_header   = analyse->getHeaderInfo();
        HTTP2HeaderInfo * header_info    = shared_header.get();
        DirectiveIterator * directive_it;

        if( header_info->getStreamId() == response_data->getStreamId() )
        {
            analyse->setResponseContentData( response_data );
            analyse->collectInfo();
            directive_it = analyse->getResult();

            m_directive_observer->createDirectiveEvents( directive_it );

            m_response_analyse_list.remove( shared_analyse );
            analyse->cleanUp( directive_it );
            shared_header.reset();
            shared_analyse.reset();

            break;
        }
    }

    Logger::instance().info("onResponseProcessingEvent finish ...");
}

void Pipeline::onResponseHeaderProcessingEvent(SharedHeaderInfo info)
{
    HTTP2HeaderInfo * data = info.get();
    stringstream debug_stream;
    debug_stream << data->getHeaderData();
    Logger::instance().debug("onResponseHeaderProccessingEvent", debug_stream.str() );

    std::string status = data->getHeaderData()[":status"];
    if( strcmp("200", status.c_str() ) == 0)
    {
        if( data->getStreamId() == 1 )
        {
            info.reset();

        }else{

            SharedResponseAnalyse shared_analyse( new HTTP2ResponseAnalyse() );
            HTTP2ResponseAnalyse * analyse = shared_analyse.get();
            analyse->setResponseHeaderInfo( info );
            m_response_analyse_list.push_back( shared_analyse );
        }
    }
}

void Pipeline::setResponseThreadStatus(bool status)
{
    m_response_thread_status = status;
}

bool Pipeline::getResponseThreadStatus(void)
{
    return m_response_thread_status;
}
