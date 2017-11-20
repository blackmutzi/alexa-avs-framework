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

#ifndef HTTP2DATA_HPP
#define HTTP2DATA_HPP

#include "include/stdafx.hpp"

namespace http2
{
    /*!
     * \brief The HTTP2Data class
     * saved http2 response data
     */
    class HTTP2Data
    {
        public:
            HTTP2Data();
            HTTP2Data( const HTTP2Data & instance );
            HTTP2Data( const char * data , size_t size );
            ~HTTP2Data();

            void set( const char * data );
            void setSize( size_t data_size );

            const char * get( void ) const;
            size_t getSize(void) const;

        protected:

            char * m_data;
            size_t m_data_size;
    };
}

#endif // HTTP2DATA_HPP
