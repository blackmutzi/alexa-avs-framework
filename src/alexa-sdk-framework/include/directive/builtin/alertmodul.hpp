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
#ifndef ALERTMODUL_HPP
#define ALERTMODUL_HPP

#include "include/stdafx.hpp"
#include "include/utils/logger.hpp"
#include "include/directive/directivemodulinterface.hpp"
#include "include/directive/directivemaker.hpp"
#include "include/event/transportinfo.hpp"
#include "include/event/requestmanager.hpp"

namespace directive
{
    class Alert
    {
        public:
            Alert( std::string token );
            ~Alert() = default;

            void setToken( std::string token );
            void setScheduledTime( std::string scheduledTime );
            void setSoundSrc( TransportInfo * info );

            bool isAlreadyStarted(void);
            std::string getToken(void);
            std::string getScheduledTime(void);
            TransportInfo * getSoundSrc(void);

            void start( AlexaEvent::RequestManager * manager );
            void stop();

            void onAlert( AlexaEvent::RequestManager * manager );

        protected:

            static void onAlertThread( Alert * alert , AlexaEvent::RequestManager * manager );

        private:

            bool m_thread_flag;
            bool m_started;
            std::string m_token;
            std::string m_scheduledTime;
            TransportInfo * m_audio_info;
    };

    using AlertList = std::list< Alert * >;
    using BoostAlertList = boost::shared_ptr< AlertList >;

    class AlertModul : public DirectiveModulInterface
    {
        public:
            AlertModul( AlexaEvent::RequestManager * requestmanager );
            ~AlertModul() = default;

            DirectiveCallbackCommand * getSetAlert(void);
            DirectiveCallbackCommand * getDeleteAlert(void);

            void pushAlert( Alert * alert );
            void removeAlert( Alert * alert );
            void removeAlert( std::string token );

            AlertList * getAlertList(void);

            void onSetAlertDirective( const Directive * );
            void onDeleteAlertDirective( const Directive * );

        protected:

            static void onSetAlertCallback( void * instance );
            static void onDeleteAlertCallback( void * instance );
            static void onAlertThreadInvoker( AlertModul * modul );

        private:

            DirectiveCallbackCommand * m_setalert;
            DirectiveCallbackCommand * m_deletealert;
            BoostAlertList m_alert_list;
            boost::mutex m_alert_mutex;
            boost::condition_variable m_alert_cv;
    };
}

#endif // ALERTMODUL_HPP
