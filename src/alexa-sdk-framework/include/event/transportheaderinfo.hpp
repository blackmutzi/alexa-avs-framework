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
#ifndef TRANSPORTHEADERINFO_HPP
#define TRANSPORTHEADERINFO_HPP

#include "stdafx.hpp"

namespace AlexaEvent
{
    /*!
     * \brief The TransportHeaderInfo class
     *  saved HTTP2 header data
     */
    class TransportHeaderInfo
    {
        public:
            TransportHeaderInfo() = default;
            TransportHeaderInfo( nghttp2_nv * info );
            ~TransportHeaderInfo() = default;

            void set( nghttp2_nv * info );
            void setSize( size_t );

            nghttp2_nv * get(void);
            size_t getSize(void);

         private:
            nghttp2_nv * m_info;
            size_t m_size_info;
    };

}

#endif // TRANSPORTHEADERINFO_HPP
