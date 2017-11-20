#ifndef TRANSPORTDATAOBSERVER_HPP
#define TRANSPORTDATAOBSERVER_HPP

#include "include/stdafx.hpp"
#include "include/event/transportinfo.hpp"
#include "include/server/transportdatalistener.hpp"

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
