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
#include "include/directive/directiveobserver.hpp"

using namespace directive;

void DirectiveObserver::regDirectiveListener(DirectiveListenerInterface *listener)
{
    m_directive_listener_list.push_back( listener );
}

void DirectiveObserver::remDirectiveListener(DirectiveListenerInterface *listener)
{
    m_directive_listener_list.remove( listener );
}

void DirectiveObserver::createDirectiveEvent(Directive *directive)
{
    for( DirectiveListenerInterface * listener : m_directive_listener_list )
    {
        listener->onDirectiveEvent( directive );
    }
}

void DirectiveObserver::createDirectiveEvents(DirectiveIterator *directive_iterator)
{
    for( Directive * directive : *directive_iterator )
    {
        createDirectiveEvent( directive );
    }
}

