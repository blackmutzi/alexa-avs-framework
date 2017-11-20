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
#include "include/http2/http2transportqueue.hpp"

using namespace http2;

HTTP2TransportQueue::~HTTP2TransportQueue(){}

void HTTP2TransportQueue::initialize(void)
{
    m_transport_queue.reset( new TransportQueue() );
    m_response_queue.reset( new ResponseQueue() );
}

void HTTP2TransportQueue::cleanUp(void)
{
    clear_transport_queue();
    clear_response_queue();

    m_transport_cv.notify_all();
    m_response_cv.notify_all();

    m_transport_queue.reset();
    m_response_queue.reset();
}

bool HTTP2TransportQueue::queue_transport_processing(HTTP2PipelineInterface *pip)
{
    boost::unique_lock< boost::mutex > transport_mutex_lock( m_transport_mutex );
    TransportQueue * queue = m_transport_queue.get();

    if( queue->empty() )
            m_transport_cv.wait( transport_mutex_lock );

    if( queue->empty() )
             return false;

    SharedTransportData data = queue->front();
    HTTP2TransportData * transport_data = data.get();

    /*
     * Set Transport Data to Pipeline and
     * send to Server ...
     */
    pip->setTransportData( transport_data );
    pip->performStream();

    /*
     * pop last item in queue
     * delete transport_data
     */
    queue->pop();
    data.reset();
    return true;
}

void HTTP2TransportQueue::queue_response_processsing(HTTP2PipelineInterface *pip)
{
    boost::unique_lock< boost::mutex > response_mutex_lock( m_response_mutex );
    ResponseQueue * queue = m_response_queue.get();

    if( queue->empty() )
            m_response_cv.wait( response_mutex_lock );

    if( queue->empty() )
            return;

    SharedResponse data = queue->front();
    HTTP2Response * response_data = data.get();

    /*
     * Custom Response Processing ...
     */
     pip->onResponseProcessingEvent( response_data );

    /*
     * pop last item in queue
     * delete response_data
     *
     */
     queue->pop();
     data.reset();
}

void HTTP2TransportQueue::push_transport(SharedTransportData transport_data )
{
    TransportQueue * queue = m_transport_queue.get();
    queue->push( transport_data );
    m_transport_cv.notify_one();
}

void HTTP2TransportQueue::push_response( SharedResponse response_data )
{
    ResponseQueue * queue = m_response_queue.get();
    queue->push( response_data );
    m_response_cv.notify_one();
}

void HTTP2TransportQueue::clear_transport_queue(void)
{
    TransportQueue * queue = m_transport_queue.get();

    while( !queue->empty() )
    {
        queue->pop();
    }
}

void HTTP2TransportQueue::clear_response_queue(void)
{
    ResponseQueue * queue = m_response_queue.get();

    while( !queue->empty() )
    {
        queue->pop();
    }
}
