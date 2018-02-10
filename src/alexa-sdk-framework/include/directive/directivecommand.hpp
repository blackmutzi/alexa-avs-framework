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
#ifndef DIRECTIVECOMMAND_HPP
#define DIRECTIVECOMMAND_HPP

#include "stdafx.hpp"
#include "directive/directive.hpp"

namespace directive
{
    typedef void ( *DirectiveCallback )( void * custom_instance );

    /*!
     * \brief The DirectiveCommand class
     * is a directive extension with the virtual methode execute
     * @see directive description
     */
    class DirectiveCommand : public Directive
    {
        public:
            DirectiveCommand() = default;
            virtual ~DirectiveCommand() = default;
            virtual void execute( void ) = 0;
    };

    /*!
     * \brief The DirectiveCallbackCommand class
     * is the concrete class from directivecommand
     * @see DirectiveCommand
     */
    class DirectiveCallbackCommand : public DirectiveCommand
    {
        public:
            DirectiveCallbackCommand() = default;
            ~DirectiveCallbackCommand() = default;

            /*!
             * save a callback pointer
             * \brief setCallback
             * \param callback
             */
            void setCallback( DirectiveCallback callback );

            /*!
             * sava a (void*) custom parameter instance for the callback pointer
             * \brief setInstance
             * \param instance
             */
            void setInstance( void * instance );

            /*!
             * execute the callback pointer
             * \brief execute
             */
            void execute(void) final;

        private:

            DirectiveCallback m_callback;
            void * m_instance;
    };

    using DirectiveCallbackCommandList = std::list< DirectiveCallbackCommand * >;
}

#endif // DIRECTIVECOMMAND_HPP
