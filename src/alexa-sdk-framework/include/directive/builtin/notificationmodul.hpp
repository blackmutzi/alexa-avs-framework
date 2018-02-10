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
#ifndef NOTIFICATIONMODUL_HPP
#define NOTIFICATIONMODUL_HPP

#include "stdafx.hpp"
#include "directive/directivemodulinterface.hpp"
#include "directive/directivemaker.hpp"
#include "event/requestmanager.hpp"

namespace directive
{
    class NotificationModul : public DirectiveModulInterface
    {
        public:
            NotificationModul( AlexaEvent::RequestManager * requestmanager );
            ~NotificationModul() = default;

            DirectiveCallbackCommand * getSetIndicator(void);
            DirectiveCallbackCommand * getClearIndicator(void);

            void onSetIndicatorDirective( const Directive * );
            void onClearIndicatorDirective( const Directive * );

        protected:

            static void onSetIndicatorCallback( void * instance );
            static void onClearIndicatorCallback( void * instance );

        private:

            DirectiveCallbackCommand * m_setindicator;
            DirectiveCallbackCommand * m_clearindicator;
    };

}

#endif // NOTIFICATIONMODUL_HPP
