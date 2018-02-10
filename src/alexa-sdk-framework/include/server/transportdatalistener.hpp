#ifndef TRANSPORTDATALISTENER_HPP
#define TRANSPORTDATALISTENER_HPP

#include "stdafx.hpp"
#include "event/transportinfo.hpp"

using namespace AlexaEvent;

namespace Server
{
    class TransportDataListener
    {
        public:
            TransportDataListener();
            virtual ~TransportDataListener();
            virtual void onTransportInfoEvent( TransportInfo * info )=0;
    };

}

#endif // TRANSPORTDATALISTENER_HPP
