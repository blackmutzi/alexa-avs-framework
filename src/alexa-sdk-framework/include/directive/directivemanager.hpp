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

#include "stdafx.hpp"
#include "event/requestmanager.hpp"

#include "directive/directivecommandinvoker.hpp"
#include "directive/builtin/alertmodul.hpp"
#include "directive/builtin/audioplayermodul.hpp"
#include "directive/builtin/notificationmodul.hpp"
#include "directive/builtin/speakermodul.hpp"
#include "directive/builtin/speechrecognizemodul.hpp"
#include "directive/builtin/speechsynthesizermodul.hpp"
#include "directive/builtin/systemmodul.hpp"


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
