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
#ifndef DIRECTIVENEVENTMAKER_HPP
#define DIRECTIVENEVENTMAKER_HPP

#include "include/stdafx.hpp"
#include "include/directive/directive.hpp"
#include "include/directive/directiveiterator.hpp"
#include "include/directive/directivelistenerinterface.hpp"

namespace directive
{
    using DirectiveListenerList = std::list< DirectiveListenerInterface * >;

    class DirectiveObserver
    {
        public:
            DirectiveObserver() = default;
            ~DirectiveObserver() = default;

            /*!
             * add a new directivelistenerinterface instance
             * \brief regDirectiveListener
             * \param listener
             */
            void regDirectiveListener( DirectiveListenerInterface * listener );

            /*!
             * remove a directivelistenerinterface instance
             * \brief remDirectiveListener
             * \param listener
             */
            void remDirectiveListener( DirectiveListenerInterface * listener );

            /*!
             * make a new directive event
             * \brief createDirectiveEvent
             * \param directive
             */
            void createDirectiveEvent( Directive * directive );

            /*!
             * make more directive events
             * \brief createDirectiveEvents
             * \param directive_iterator contain directive instances
             */
            void createDirectiveEvents( DirectiveIterator * directive_iterator );

        private:

            DirectiveListenerList m_directive_listener_list;
    };
}

#endif // DIRECTIVENEVENTMAKER_HPP
