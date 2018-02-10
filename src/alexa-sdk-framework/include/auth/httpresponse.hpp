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
#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include "stdafx.hpp"
#include "http2/http2data.hpp"

namespace Auth
{
    /*!
     * \brief The HTTPResponse class
     * contain http response data
     */
    class HTTPResponse : public http2::HTTP2Data
    {
        public:
            HTTPResponse() = default;
            ~HTTPResponse() = default;
    };
}

#endif // HTTPRESPONSE_HPP
