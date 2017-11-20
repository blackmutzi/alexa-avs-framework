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
#include "include/directive/builtin/alertmodul.hpp"

using namespace directive;

Alert::Alert(string token)
    : m_thread_flag( false ) ,
      m_started( false ) ,
      m_token( token ) ,
      m_scheduledTime( 0 ) ,
      m_audio_info( nullptr )
{}

void Alert::setToken(string token)
{
    m_token = token;
}

void Alert::setScheduledTime( std::string time )
{
    m_scheduledTime = time;
}

void Alert::setSoundSrc(TransportInfo *info)
{
    m_audio_info = info;
}

bool Alert::isAlreadyStarted(void)
{
    return m_started;
}

std::string Alert::getToken(void)
{
    return m_token;
}

std::string Alert::getScheduledTime(void)
{
    return m_scheduledTime;
}

TransportInfo * Alert::getSoundSrc(void)
{
    return m_audio_info;
}

void Alert::start(AlexaEvent::RequestManager * manager)
{
     m_started = true;
     m_thread_flag = true;
     boost::thread alert_thread_invoker( &Alert::onAlertThread , this , manager );
}

void Alert::stop(void)
{
     m_thread_flag = false;
}

void Alert::onAlertThread( Alert * alert , AlexaEvent::RequestManager * manager)
{
    alert->onAlert( manager );
}

void Alert::onAlert( AlexaEvent::RequestManager * manager )
{
    EventAlertModul * modul = manager->getEventModulManager()->getAlertModul( m_token );
    manager->sendRequest( modul->createAlertStartedEvent() );

    while( m_thread_flag )
    {
        // TODO
        // Play Alert Here ...
    }

    manager->sendRequest( modul->createAlertStoppedEvent() );
}

AlertModul::AlertModul( AlexaEvent::RequestManager * requestmanager )
    : DirectiveModulInterface( requestmanager ) ,
      m_setalert( nullptr )     ,
      m_deletealert( nullptr )
{
    m_alert_list.reset( new AlertList() );

    DirectiveMaker maker;
    m_setalert    = maker.createDirectiveCallbackCommand( maker.createDirectiveType("Alerts","SetAlert")    , &AlertModul::onSetAlertCallback    , this );
    m_deletealert = maker.createDirectiveCallbackCommand( maker.createDirectiveType("Alerts","DeleteAlert") , &AlertModul::onDeleteAlertCallback , this );
    m_directives.push_back( m_setalert );
    m_directives.push_back( m_deletealert );

    // start AlertThreadInvoker
    boost::thread alert_thread_invoker( &AlertModul::onAlertThreadInvoker , this );
}

DirectiveCallbackCommand * AlertModul::getSetAlert(void)
{
    return m_setalert;
}

DirectiveCallbackCommand * AlertModul::getDeleteAlert(void)
{
    return m_deletealert;
}

void AlertModul::pushAlert(Alert *alert)
{
    AlertList * list = m_alert_list.get();
    list->push_back( alert );
}

void AlertModul::removeAlert(Alert *alert)
{
    AlertList * list = m_alert_list.get();
    list->remove( alert );
}

void AlertModul::removeAlert( std::string token )
{
    for( Alert * alert : *m_alert_list.get() )
    {
        if( alert->getToken() == token )
             removeAlert( alert );
             break;
    }
}

AlertList * AlertModul::getAlertList(void)
{
    return m_alert_list.get();
}

void AlertModul::onSetAlertDirective(const Directive * directive )
{
    // TODO
    // Collect Alert Informations from Json Directive


    std::string token = "";
    std::string scheduledTime = "";
    char * sound_src  = nullptr;
    size_t sound_size = 0;

    try{

        Alert * alert = new Alert( token );
        alert->setScheduledTime( scheduledTime );
        alert->setSoundSrc( new TransportInfo( sound_src , sound_size ) );

        pushAlert( alert );

        EventAlertModul * modul = getRequestManager()->getEventModulManager()->getAlertModul( token );
        getRequestManager()->sendRequest( modul->createSetAlertSucceededEvent() );

    } catch ( std::exception e )
    {
        EventAlertModul * modul = getRequestManager()->getEventModulManager()->getAlertModul( token );
        getRequestManager()->sendRequest( modul->createSetAlertFailedEvent() );
    }
}

void AlertModul::onDeleteAlertDirective(const Directive *)
{
    // TODO
    // Collect Alert Informations

    std::string token = "";

    try{

        removeAlert( token );
        EventAlertModul * modul = getRequestManager()->getEventModulManager()->getAlertModul( token );
        getRequestManager()->sendRequest( modul->createDeleteAlertSucceededEvent() );

    } catch ( std::exception e )
    {
        EventAlertModul * modul = getRequestManager()->getEventModulManager()->getAlertModul( token );
        getRequestManager()->sendRequest( modul->createDeleteAlertFailedEvent() );
    }
}

void AlertModul::onSetAlertCallback( void * instance )
{
    AlertModul * modul = ( AlertModul * ) instance;
    modul->onSetAlertDirective( (const Directive * ) modul->getSetAlert() );
}

void AlertModul::onDeleteAlertCallback( void * instance )
{
    AlertModul * modul = ( AlertModul * ) instance;
    modul->onDeleteAlertDirective( (const Directive *) modul->getDeleteAlert() );
}

void AlertModul::onAlertThreadInvoker(AlertModul *modul)
{
    boost::posix_time::ptime now;
    boost::posix_time::ptime scheduledTime;

    while(true)
    {
        now = boost::posix_time::second_clock::local_time();
        if( modul->getAlertList()->empty() )
        {
            boost::this_thread::sleep(boost::posix_time::seconds(5));

        } else {

            for( Alert * alert : *modul->getAlertList() )
            {
                scheduledTime = boost::posix_time::time_from_string( alert->getScheduledTime() );

                if( scheduledTime >= now && !alert->isAlreadyStarted() )
                {
                    alert->start( modul->getRequestManager() );
                }
            }

        }
    }
}
