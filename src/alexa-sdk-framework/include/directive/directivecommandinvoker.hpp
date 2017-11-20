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
#ifndef DIRECTIVESERVICE_HPP
#define DIRECTIVESERVICE_HPP

#include "include/stdafx.hpp"
#include "include/directive/directivelistenerinterface.hpp"
#include "include/directive/directivecommandproxy.hpp"
#include "include/utils/logger.hpp"

using namespace AVS;

namespace directive
{
    /*!
     * \brief The DirectiveCommandInvoker class
     * convert a directive to a directivecommand and execute it ...
     * @see DirectiveListenerInterface , DirectiveCommandProxy
     */
    class DirectiveCommandInvoker : public DirectiveListenerInterface , public DirectiveCommandProxy
    {
        public:
            DirectiveCommandInvoker() = default;
            ~DirectiveCommandInvoker() = default;

            void onDirectiveEvent( Directive * directive );
    };
}

#endif // DIRECTIVESERVICE_HPP
