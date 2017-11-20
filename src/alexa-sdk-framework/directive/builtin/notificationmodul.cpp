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
#include "include/directive/builtin/notificationmodul.hpp"

using namespace directive;

NotificationModul::NotificationModul( AlexaEvent::RequestManager * request_manager )
    : DirectiveModulInterface( request_manager ) ,
      m_setindicator( nullptr ) ,
      m_clearindicator( nullptr )
{
    DirectiveMaker maker;
    m_setindicator   = maker.createDirectiveCallbackCommand( maker.createDirectiveType("Notifications", "SetIndicator")  , &NotificationModul::onSetIndicatorCallback , this );
    m_clearindicator = maker.createDirectiveCallbackCommand( maker.createDirectiveType("Notifications", "ClearIndicator"), &NotificationModul::onClearIndicatorCallback , this );

    m_directives.push_back( m_setindicator );
    m_directives.push_back( m_clearindicator );
}

DirectiveCallbackCommand * NotificationModul::getSetIndicator(void)
{
    return m_setindicator;
}

DirectiveCallbackCommand * NotificationModul::getClearIndicator(void)
{
    return m_clearindicator;
}

void NotificationModul::onSetIndicatorDirective(const Directive *)
{

}

void NotificationModul::onClearIndicatorDirective(const Directive *)
{

}

void NotificationModul::onSetIndicatorCallback( void * instance )
{
    NotificationModul * modul = ( NotificationModul * ) instance;
    modul->onSetIndicatorDirective( (const Directive * ) modul->getSetIndicator() );
}

void NotificationModul::onClearIndicatorCallback( void * instance )
{
    NotificationModul * modul = ( NotificationModul * ) instance;
    modul->onClearIndicatorDirective( (const Directive *) modul->getClearIndicator() );
}
