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
#include "include/directive/builtin/systemmodul.hpp"

using namespace directive;

SystemModul::SystemModul(  AlexaEvent::RequestManager * request_manager )
    : DirectiveModulInterface( request_manager ) ,
      m_resetuserinactivity( nullptr ) ,
      m_setendpoint( nullptr )
{
    DirectiveMaker maker;
    m_resetuserinactivity = maker.createDirectiveCallbackCommand( maker.createDirectiveType("System", "ResetUserInactivity") , &SystemModul::onResetUserInactivityCallback  , this );
    m_setendpoint = maker.createDirectiveCallbackCommand( maker.createDirectiveType("System", "SetEndpoint") , &SystemModul::onSetEndPointCallback , this );

    m_directives.push_back( m_resetuserinactivity );
    m_directives.push_back( m_setendpoint );
}

DirectiveCallbackCommand * SystemModul::getResetUserInactivity(void)
{
    return m_resetuserinactivity;
}

DirectiveCallbackCommand * SystemModul::getSetEndPoint(void)
{
    return m_setendpoint;
}

void SystemModul::onResetUserInactivityDirective(const Directive *)
{

}

void SystemModul::onSetEndPointDirective(const Directive *)
{

}

void SystemModul::onResetUserInactivityCallback( void * instance )
{
    SystemModul * modul = (SystemModul * ) instance;
    modul->onResetUserInactivityDirective( (const Directive *) modul->getResetUserInactivity() );
}

void SystemModul::onSetEndPointCallback( void * instance )
{
    SystemModul * modul = (SystemModul * ) instance;
    modul->onSetEndPointDirective( (const Directive *) modul->getSetEndPoint() );
}







