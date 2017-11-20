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
#ifndef DIRECTIVEMANAGER_HPP
#define DIRECTIVEMANAGER_HPP

#include "include/stdafx.hpp"
#include "include/event/requestmanager.hpp"

#include "include/directive/directivecommandinvoker.hpp"
#include "include/directive/builtin/alertmodul.hpp"
#include "include/directive/builtin/audioplayermodul.hpp"
#include "include/directive/builtin/notificationmodul.hpp"
#include "include/directive/builtin/speakermodul.hpp"
#include "include/directive/builtin/speechrecognizemodul.hpp"
#include "include/directive/builtin/speechsynthesizermodul.hpp"
#include "include/directive/builtin/systemmodul.hpp"


namespace directive
{
    class DirectiveManager
    {
        public:
             DirectiveManager();
            ~DirectiveManager() = default;

            void setRequestManager( AlexaEvent::RequestManager * manager );
            void initialize(void);

            void addDirectiveCommands( DirectiveModulInterface * directive_modul );
            void addDirectiveCommand( DirectiveCommand * cmd );

        private:

            AlexaEvent::RequestManager * m_request_manager;
            DirectiveCommandInvoker * m_invoker;
    };
}

#endif // DIRECTIVEMEDIATOR_HPP
