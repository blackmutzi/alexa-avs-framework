#ifndef TRANSPORTDATAMANAGER_HPP
#define TRANSPORTDATAMANAGER_HPP

#include "include/stdafx.hpp"
#include "include/event/transportinfo.hpp"
#include "include/server/transportdataobserver.hpp"

using namespace AlexaEvent;

namespace Server
{
    class TransportDataManager : public TransportDataObserver
    {
        public:
            TransportDataManager();
            ~TransportDataManager();

            TransportInfo * createTransportData( char* data, size_t size );
    };
}

#endif // TRANSPORTDATAMANAGER_HPP
