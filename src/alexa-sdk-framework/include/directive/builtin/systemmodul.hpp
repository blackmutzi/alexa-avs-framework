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
#ifndef SYSTEMMODUL_HPP
#define SYSTEMMODUL_HPP

#include "include/stdafx.hpp"
#include "include/directive/directivemodulinterface.hpp"
#include "include/directive/directivemaker.hpp"
#include "include/event/requestmanager.hpp"

namespace directive
{
    class SystemModul : public DirectiveModulInterface
    {
        public:
            SystemModul( AlexaEvent::RequestManager * requestmanager );
            ~SystemModul() = default;

            DirectiveCallbackCommand * getResetUserInactivity();
            DirectiveCallbackCommand * getSetEndPoint();

            void onResetUserInactivityDirective( const Directive * );
            void onSetEndPointDirective( const Directive * );

        protected:

            static void onResetUserInactivityCallback( void * instance );
            static void onSetEndPointCallback( void * instance );

        private:

            DirectiveCallbackCommand * m_resetuserinactivity;
            DirectiveCallbackCommand * m_setendpoint;

    };
}

#endif // SYSTEMMODUL_HPP
