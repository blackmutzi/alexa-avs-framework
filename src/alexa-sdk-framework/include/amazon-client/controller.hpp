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
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "include/stdafx.hpp"
#include "include/amazon-client/pipeline.hpp"
#include "include/utils/console.hpp"
#include "include/event/requestmanager.hpp"
#include "include/directive/directivemanager.hpp"

using namespace AlexaEvent;
namespace AVS
{
    class Controller : public Console
    {
        public:
            Controller();
            ~Controller() = default;

            void initialize(void);
            void cleanUp(void);
            void close(void);

            void ConnectToAlexaVoiceService( void );
            bool MainLoop(void);

            bool isConnected(void);
            void setConnectStatus( bool status );
            void setAccessToken( const char * access_token );
            void setBoundary( const char * boundary );
            void setUrl( const char * avs_url );

            const char * getAccessToken(void);
            const char * getBoundary(void);
            const char * getUrl(void);

            Pipeline * getPipeline(void);
            RequestManager * getRequestManager(void);
            DirectiveManager * getDirectiveManager(void);

        private:

            void onConsoleInputEvent(char *input) final;

            static void PipelineStartThread( Controller * controller );

            const char * m_access_token;
            const char * m_boundary;
            const char * m_avs_url;

            RequestManager * m_request_manager;
            DirectiveManager * m_directive_manager;
            Pipeline * m_pipeline;

            bool m_avs_connection;
            bool m_close;
    };
}

#endif // CONTROLLER_HPP
