#ifndef TRANSPORTDATAOBSERVER_HPP
#define TRANSPORTDATAOBSERVER_HPP

#include "stdafx.hpp"
#include "event/transportinfo.hpp"
#include "server/transportdatalistener.hpp"

using namespace AlexaEvent;

namespace Server
{
    class TransportDataObserver
    {
        public:

            using TransportList = std::list< TransportDataListener * >;

            TransportDataObserver();
            ~TransportDataObserver();

            void addTransportDataListener( TransportDataListener * listener );
            void removeTransportDataListener( TransportDataListener * listener );
            void createTransportDataEvent( TransportInfo * info );

        private:

            TransportList m_transport_list;
    };
}

#endif // TRANSPORTDATAOBSERVER_HPP
