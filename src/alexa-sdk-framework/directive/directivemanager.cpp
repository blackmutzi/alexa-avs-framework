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
#include "directive/directivemanager.hpp"

using namespace directive;

DirectiveManager::DirectiveManager()
    : m_request_manager( nullptr ) ,
      m_invoker( new DirectiveCommandInvoker() )
{}

void DirectiveManager::setRequestManager(RequestManager *manager)
{
    m_request_manager = manager;
}

void DirectiveManager::initialize(void)
{
    m_request_manager->getPipeline()->getDirectiveObserver()->regDirectiveListener( m_invoker );

    addDirectiveCommands( new AlertModul( m_request_manager ) );
    addDirectiveCommands( new AudioPlayerModul( m_request_manager )  );
    addDirectiveCommands( new NotificationModul( m_request_manager ) );
    addDirectiveCommands( new SpeakerModul( m_request_manager ) );
    addDirectiveCommands( new SpeechRecognizeModul( m_request_manager ) );
    addDirectiveCommands( new SpeechSynthesizerModul( m_request_manager ) );
    addDirectiveCommands( new SystemModul( m_request_manager ) );
}

void DirectiveManager::addDirectiveCommands(DirectiveModulInterface *directive_modul)
{
    m_invoker->registerCommandModul( directive_modul );
}

void DirectiveManager::addDirectiveCommand(DirectiveCommand *cmd)
{
    m_invoker->registerCommand( cmd );
}
