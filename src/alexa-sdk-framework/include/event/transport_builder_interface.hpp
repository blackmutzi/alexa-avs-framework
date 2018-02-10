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
#ifndef TRANSPORT_BUILDER_INTERFACE_HPP
#define TRANSPORT_BUILDER_INTERFACE_HPP

#include "event/transportinfo.hpp"
#include "event/transportheaderinfo.hpp"

namespace AlexaEvent
{
    class TransportBuilderInterface
    {
        public:
            TransportBuilderInterface() = default;
            virtual ~TransportBuilderInterface() = default;

            virtual TransportInfo * buildTransportInfo() = 0;
            virtual TransportHeaderInfo * buildTransportHeaderInfo() = 0;
    };

}

#endif // TRANSPORT_BUILDER_INTERFACE_HPP
