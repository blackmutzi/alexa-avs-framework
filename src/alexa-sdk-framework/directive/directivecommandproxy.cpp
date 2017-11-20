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
#include "include/directive/directivecommandproxy.hpp"

using namespace directive;

void DirectiveCommandProxy::registerCommand(DirectiveCommand *command)
{
    m_directive_command_list.push_back( command );
}

void DirectiveCommandProxy::unregisterCommand(DirectiveCommand *command)
{
    m_directive_command_list.remove( command );
}

void DirectiveCommandProxy::registerCommandModul( DirectiveModulInterface * modul )
{
    for( DirectiveCallbackCommand * cb_command : modul->getDirectives() )
    {
        DirectiveCommand * origin_command = ( DirectiveCommand * ) cb_command;
        registerCommand( origin_command );

        stringstream debug_stream;
        debug_stream << origin_command->getDirectiveType()->getToken() << " ";
        debug_stream << origin_command->getDirectiveType()->getValue();
        Logger::instance().debug("Enable-Directive-Command", debug_stream.str() );
    }
}

void DirectiveCommandProxy::unregisterCommandModul(DirectiveModulInterface *modul)
{
    for( DirectiveCallbackCommand * cb_command : modul->getDirectives() )
    {
        DirectiveCommand * origin_command = (DirectiveCommand *) cb_command;
        unregisterCommand( origin_command);

        stringstream debug_stream;
        debug_stream << origin_command->getDirectiveType()->getToken() << " ";
        debug_stream << origin_command->getDirectiveType()->getValue();
        Logger::instance().debug("Disable-Directive-Command", debug_stream.str() );
    }
}

DirectiveCommand * DirectiveCommandProxy::selectCommand( Directive *directive ) throw( std::exception )
{
    for( DirectiveCommand * command : m_directive_command_list )
    {
        if( strcmp( command->getDirectiveType()->getToken() , directive->getDirectiveType()->getToken() ) == 0 )
        {
            if( strcmp( command->getDirectiveType()->getValue() , directive->getDirectiveType()->getValue() )  == 0 )
            {

                Logger::instance().debug("detect-directive-namespace:", directive->getDirectiveType()->getToken() );
                Logger::instance().debug("detect-directive-name:", directive->getDirectiveType()->getValue() );


                 command->setJsonInfo( directive->getJsonInfo() );

                 if( directive->hasAudioInfo() )
                 {
                     command->setAudioInfo( directive->getAudioInfo() );

                 }else
                 {
                     command->setAudioInfo( nullptr );
                     command->setAudioInfoStatus( false );
                 }

                 return command;
            }
        }
    }

    throw std::exception();
}
