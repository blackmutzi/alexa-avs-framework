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
#ifndef DIRECTIVECOMMANDPROXY_HPP
#define DIRECTIVECOMMANDPROXY_HPP

#include "stdafx.hpp"
#include "utils/logger.hpp"
#include "directive/directivemodulinterface.hpp"

namespace directive
{
    using DirectiveCommandList = std::list< DirectiveCommand * >;

    /*!
     * \brief The DirectiveCommandProxy class
     *  contains all directivecommand instances and
     *  convert a directive to a directivecommand
     */
    class DirectiveCommandProxy
    {
        public:
            DirectiveCommandProxy() = default;
            ~DirectiveCommandProxy() = default;

            /*!
             * add a new directivecommand instance
             * \brief registerCommand
             * \param command
             */
            void registerCommand( DirectiveCommand * command );

            /*!
             * remove a directivecommand instance
             * \brief unregisterCommand
             * \param command
             */
            void unregisterCommand( DirectiveCommand * command );

            /*!
             * look into the DirectiveModulInterface instance and
             * added all directivecommand which include it
             *
             * used this.registerCommand method
             *
             * \brief registerCommandModul
             * \param modul
             */
            void registerCommandModul( DirectiveModulInterface * modul );
            void unregisterCommandModul( DirectiveModulInterface * modul );

            /*!
             * equal a directive with all directivecommand instances
             * if any equal then return this driectivecommand instance
             * \brief selectCommand
             * \param directive
             * \return
             */
            DirectiveCommand * selectCommand( Directive * directive ) throw( std::exception );

         private:

            DirectiveCommandList m_directive_command_list;
    };
}

#endif // DIRECTIVECOMMANDPROXY_HPP
