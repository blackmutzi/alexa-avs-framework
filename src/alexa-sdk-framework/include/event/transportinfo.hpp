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
#ifndef TRANSPORTINFO_H
#define TRANSPORTINFO_H

#include "include/stdafx.hpp"

namespace AlexaEvent
{
    /*!
     * \brief The TransportInfo class
     *  saved string data or binary data
     */
    class TransportInfo
    {
        public:
            TransportInfo();
            TransportInfo( const TransportInfo & info );
            TransportInfo( const char * str_info );
            TransportInfo( const char * binary_info , size_t size );
            ~TransportInfo();

            /*!
             * make a copy of data
             * \brief copy
             * \param data
             * \param size
             */
            void copy( const char * data , size_t size );

            /*!
             * save data
             * \brief set
             * \param data
             */
            void set( const char * data );

            /*!
             * save data size
             * \brief setSize
             * \param data_size
             */
            void setSize( size_t data_size );

            /*!
             * return save data
             * \brief get
             * \return
             */
            const char * get(void) const;

            /*!
             * return data size
             * \brief getSize
             * \return
             */
            size_t getSize(void) const;

        private:

            char * m_info;
            size_t m_size_info;
    };
}

#endif // TRANSPORTINFO_H
