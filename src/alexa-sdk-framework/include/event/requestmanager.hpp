#ifndef REQUESTMANAGER_HPP
#define REQUESTMANAGER_HPP

#include "stdafx.hpp"
#include "utils/logger.hpp"
#include "amazon-client/pipeline.hpp"

#include "event/recorder.hpp"
#include "event/eventstreamrequest.hpp"
#include "event/recognizestreamrequest.hpp"
#include "event/eventmodulmanger.hpp"

namespace AVS
{
    class Pipeline;
}

namespace AlexaEvent
{
    class RequestManager
    {
        public:
            RequestManager( const char * access_token , const char * boundary );
            ~RequestManager();

            void setEventModulManager( EventModulManager * manager );
            void setAlexaPipeline( AVS::Pipeline * pipeline );

            void sendRequest( TransportInfo * info );
            void sendRecognizeRequest( std::string dialog_request_id );
            void sendRecognizeRequest( std::string dialog_request_id , TransportInfo * audio_info );

            EventModulManager * getEventModulManager(void);
            AVS::Pipeline * getPipeline(void);

        private:

            EventModulManager * m_event_manager;
            AVS::Pipeline * m_pipeline;
            const char * m_access_token;
            const char * m_boundary;
    };
}
#endif // REQUESTMANAGER_HPP
