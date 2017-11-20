#include "include/server/transportdataobserver.hpp"

using namespace Server;

TransportDataObserver::TransportDataObserver(){}
TransportDataObserver::~TransportDataObserver(){}

void TransportDataObserver::addTransportDataListener(TransportDataListener *listener)
{
    m_transport_list.push_back( listener );
}

void TransportDataObserver::removeTransportDataListener(TransportDataListener *listener)
{
    m_transport_list.remove( listener );
}

void TransportDataObserver::createTransportDataEvent(TransportInfo *info)
{
    for( TransportDataListener * listener : m_transport_list )
    {
        listener->onTransportInfoEvent( info );
    }
}

